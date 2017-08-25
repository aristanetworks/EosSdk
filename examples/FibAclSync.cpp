// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.
#include <eos/acl.h>
#include <eos/sdk.h>
#include <eos/fib.h>
#include <eos/timer.h>
#include <eos/tracing.h>
#include <sstream>
#include <set>

/* FibAclSync monitors the routes in a VRF and makes sure that a permit rule
 * with the destination qualifier matching each monitored route exists in a
 * V4/V6 ACL. For simplicity, when an ACL update is triggered by a route change
 * all the existing rules in the ACL are purged from the ACL config and a new
 * config is created by iterating the FIB. The new config is then committed
 * to reprogram the ACL in hardware.
 *
 * ACL commit operation is expensive since it involves reprogramming all the
 * rules in hardware. In order to minimize the number of ACL commits
 * a timer "acl_update_timer" is used to defer ACL update processing so that
 * the updates for multiple route changes can be combined. If there are too
 * many route changes in the VRF "acl_update_timer" backs off exponentially.
 *
 * User can configure the VRF and the type of routes to monitor using the
 * config options mentioned below. If no VRF is specified 'default' VRF is
 * assumed. Similarly if the route type is not configured 'static' route
 * type is assumed.
 *
 * Config options supported:
 *
 * 1. ipv4_access_list       : V4 ACL name
 * 2. ipv6_access_list       : V6 ACL name
 * 3. vrf                    : Vrf to monitor
 * 4. route_types            : Route types to monitor
 * 5. acl_update_timer_min   : acl_update_timer minimum delay
 * 6. acl_update_timer_max   : acl_update_timer maximum delay
 *
 * Status data:
 *
 * 1. update_fail_counter    : Number of failed ACL updates
 * 2. update_success_counter : Number of succeeded ACL updates
 * 3. last ACL update status : Status of last ACL update
 * 4. ipv4-access-list       : V4 ACL name
 * 5. ipv6-access-list       : V6 ACL name
 * 6. route_types            : Route types to monitor
 * 7. acl-update-timer       : Deferred processing timer
 * 8. vrf                    : Vrf being monitored
 */

static const std::string VRF_DEFAULT = "default";
static const std::string ROUTE_TYPE_STATIC_CONFIG = "static";
static const float ACL_UPDATE_TIMER_MIN = 1;
static const float ACL_UPDATE_TIMER_MAX = 8;

static const std::string AGENT_NAME = "FibAclSync";
static const uint32_t ACL_SEQ_INCR = 10;
static const std::string ROUTE_TYPE_BGP = "bgp";
static const std::string ROUTE_TYPE_IBGP = "ibgp";
static const std::string ROUTE_TYPE_EBGP = "ebgp";
static const std::string ROUTE_TYPE_BGP_AGGREGATE = "bgp_aggregate";

// Config options
static const std::string CONFIG_IPV4_ACCESS_LIST= "ipv4_access_list";
static const std::string CONFIG_IPV6_ACCESS_LIST= "ipv6_access_list";
static const std::string CONFIG_VRF= "vrf";
static const std::string CONFIG_ROUTE_TYPES = "route_types";
static const std::string CONFIG_ACL_UPDATE_TIMER_MIN = "acl_update_timer_min";
static const std::string CONFIG_ACL_UPDATE_TIMER_MAX = "acl_update_timer_max";

// Status data
static const std::string STATUS_VRF = "VRF being monitored";
static const std::string STATUS_ROUTE_TYPES = "Route types to monitor";
static const std::string STATUS_ACL_UPDATE_TIMER_MIN = "ACL update timer[ min ]";
static const std::string STATUS_ACL_UPDATE_TIMER_MAX = "ACL update timer[ max ]";
static const std::string STATUS_ACL_UPDATE_TIMER = "ACL update timer";
static const std::string STATUS_UPDATE_SUCCESS_COUNTER=
                                      "Number of succeeded ACL updates";
static const std::string STATUS_UPDATE_FAIL_COUNTER= "Number of failed ACL updates";
static const std::string STATUS_LAST_UPDATE_STATUS = "Status of last ACL update";
static const std::string STATUS_IPV4_ACCESS_LIST = "V4 ACL name";
static const std::string STATUS_IPV6_ACCESS_LIST = "V6 ACL name";

// Size of the buffer allocated to copy configured route_types.
#define ROUTE_TYPES_OPTIONS_VALUE_MAX 1024

class fib_acl_sync : public eos::agent_handler,
                     public eos::acl_handler,
                     public eos::fib_handler,
                     public eos::timeout_handler {
 public:
   eos::agent_mgr * agentMgr;
   explicit fib_acl_sync(eos::sdk & sdk)
         : eos::agent_handler(sdk.get_agent_mgr()),
           eos::acl_handler(sdk.get_acl_mgr()),
           eos::fib_handler(sdk.get_fib_mgr(eos::MODE_TYPE_READ_NOTIFYING)),
           eos::timeout_handler(sdk.get_timeout_mgr()),
           agentMgr(sdk.get_agent_mgr()),
           t(AGENT_NAME.c_str()) {
      initialized = false;
      vrf = VRF_DEFAULT;
      route_types.insert(eos::ROUTE_TYPE_STATIC_CONFIG);
      acl_update_timer_min = ACL_UPDATE_TIMER_MIN;
      acl_update_timer_max = ACL_UPDATE_TIMER_MAX;
      acl_update_timer = acl_update_timer_min;
      update_success_counter = 0;
      update_fail_counter = 0;
      pending_updates = false;
      acl4_seq = ACL_SEQ_INCR;
      acl6_seq = ACL_SEQ_INCR;
      last_update_time = 0;
      t.trace0("Agent constructed");
   }

   void on_initialized() {
      t.trace0("%s: Initializing", __FUNCTION__);
      update_status(STATUS_IPV4_ACCESS_LIST, ipv4_access_list_name);
      update_status(STATUS_IPV6_ACCESS_LIST, ipv6_access_list_name);
      update_status(STATUS_VRF, vrf);
      update_status(STATUS_ROUTE_TYPES, convert(route_types));
      update_status(STATUS_ACL_UPDATE_TIMER_MIN, acl_update_timer_min);
      update_status(STATUS_ACL_UPDATE_TIMER_MAX, acl_update_timer_max);
      update_status(STATUS_ACL_UPDATE_TIMER, acl_update_timer);
      update_status(STATUS_UPDATE_SUCCESS_COUNTER, update_success_counter);
      update_status(STATUS_UPDATE_FAIL_COUNTER, update_fail_counter);
      update_status(STATUS_LAST_UPDATE_STATUS, "");

      for (auto option = agentMgr->agent_option_iter(); option; ++option) {
         handle_agent_option(*option, agentMgr->agent_option(*option));
      }

      // Register for all ACL updates.
      watch_all_acls(true);
      initialized = true;
      schedule_acl_update();
      t.trace0("%s: Agent Initialized", __FUNCTION__);
   }

   void on_agent_option(std::string const & option_name,
                        std::string const & value) {
      // One of the user configurable option has changed.
      t.trace0("%s:", __FUNCTION__);
      handle_agent_option(option_name, value);
   }

   void on_route_set(eos::fib_route_t const& route) {
      // New route added. Schedule ACL update.
      t.trace3("%s: %s", __FUNCTION__, route.to_string().c_str());
      if (route_types.find(route.route_type()) == route_types.end()) {
         t.trace3("%s: Did not match route_type. Ignored.", __FUNCTION__);
      } else {
         t.trace3("%s: Matched route_type.", __FUNCTION__);
         schedule_acl_update();
      }
   }

   void on_route_del(eos::fib_route_key_t const& route_key) {
      // Route removed. Schedule ACL update.
      t.trace3("%s: %s", __FUNCTION__, route_key.to_string().c_str());
      schedule_acl_update();
   }

   void on_acl_sync() {
      // ACL Commit succeeded. Update the status.
      t.trace3("%s: ACL update succeeded", __FUNCTION__);
      update_success_counter++;
      update_status(STATUS_UPDATE_SUCCESS_COUNTER, update_success_counter);
      update_status(STATUS_LAST_UPDATE_STATUS, "Sync succeeded");
   }

   void on_acl_sync_fail(std::string const & linecard,
                         std::string const & message) {
      // ACL Commit failed. Update the status.
      t.trace0("%s: ACL update failed: %s", __FUNCTION__, message.c_str());
      update_fail_counter++;
      update_status(STATUS_UPDATE_FAIL_COUNTER, update_fail_counter);
      update_status(STATUS_LAST_UPDATE_STATUS, "Sync failed");
   }

   void on_timeout() {
      // Start deferred ACL update.
      t.trace3("%s:", __FUNCTION__);
      update_acls();
   }

   void handle_agent_option(std::string const & option_name,
                            std::string const & value) {
      bool update_acl = false;
      t.trace3("%s:", __FUNCTION__);

      if (option_name == CONFIG_ACL_UPDATE_TIMER_MIN) {
         // acl_update_timer_min has changed. No need to schedule ACL update.
         // This will be effective when we schedule the next ACL update.

         if (value.empty()) {
            acl_update_timer_min = ACL_UPDATE_TIMER_MIN;
         } else {
            acl_update_timer_min = strtof(value.c_str(), NULL);
            if (acl_update_timer_min == 0) {
               // User has set an incorrect value.
               // Reset to default value.
               t.trace0("%s: Option %s set to an incorrect value. "
                        "Assuming default value.",
                        __FUNCTION__, CONFIG_ACL_UPDATE_TIMER_MIN.c_str());
               acl_update_timer_min = ACL_UPDATE_TIMER_MIN;
            }
         }

         acl_update_timer = acl_update_timer_min;
         update_status(STATUS_ACL_UPDATE_TIMER_MIN, acl_update_timer_min);

      } else if (option_name == CONFIG_ACL_UPDATE_TIMER_MAX) {
         // acl_update_timer_max has changed. No need to schedule ACL update.
         // This will be effective when we schedule the next ACL update.

         if (value.empty()) {
            acl_update_timer_max = ACL_UPDATE_TIMER_MAX;
         } else {
            acl_update_timer_max = strtof(value.c_str(), NULL);
            if (acl_update_timer_max == 0) {
               // User has set an incorrect value.
               // Reset to default value.
               t.trace0("%s: Option %s set to an incorrect value. "
                        "Assuming default value.",
                        __FUNCTION__, CONFIG_ACL_UPDATE_TIMER_MIN.c_str());
               acl_update_timer_max = ACL_UPDATE_TIMER_MAX;
            }
         }

         acl_update_timer = acl_update_timer_min;
         update_status(STATUS_ACL_UPDATE_TIMER_MAX, acl_update_timer_max);

      } else if (option_name == CONFIG_IPV4_ACCESS_LIST) {
         // V4 ACL name has changed. Remove the ACL first if exists
         // and then schedule an update.

         remove_v4_acl();
         if (value.empty()) {
            t.trace0("%s: Removed option %s", __FUNCTION__,
                     CONFIG_IPV4_ACCESS_LIST.c_str());
            ipv4_access_list_name.clear();
         } else {
            t.trace0("%s: Option %s set to %s", __FUNCTION__,
                     CONFIG_IPV4_ACCESS_LIST.c_str(), value.c_str());
            ipv4_access_list_name = value;
         }

         update_status(STATUS_IPV4_ACCESS_LIST, ipv4_access_list_name);
         update_acl = true;

      } else if (option_name == CONFIG_IPV6_ACCESS_LIST) {
         // V6 ACL name has changed. Remove the ACL first if exists
         // and then schedule an update.

         remove_v6_acl();
         if (value.empty()) {
            t.trace0("%s: Removed option %s", __FUNCTION__,
                     CONFIG_IPV6_ACCESS_LIST.c_str());
            ipv6_access_list_name.clear();
         } else {
            t.trace0("%s: Option %s set to %s", __FUNCTION__,
                     CONFIG_IPV4_ACCESS_LIST.c_str(), value.c_str());
            ipv6_access_list_name = value;
         }

         update_status(STATUS_IPV6_ACCESS_LIST, ipv6_access_list_name);
         update_acl = true;

      } else if (option_name == CONFIG_VRF) {
         // VRF changed. Schedule ACL update

         if (value.empty()) {
            t.trace0("%s: Removed option %s", __FUNCTION__,
                     CONFIG_VRF.c_str());
            vrf = VRF_DEFAULT;
         } else {
            t.trace0("%s: Option %s set to %s", __FUNCTION__,
                     CONFIG_VRF.c_str(), value.c_str());
            vrf = value;
         }

         get_fib_mgr()->register_vrf(vrf, true);
         update_status(STATUS_VRF, vrf);
         update_acl = true;

      } else if (option_name == CONFIG_ROUTE_TYPES) {

         if (value.empty()) {
            // Removed route_types config. Assume static type.
            t.trace0("%s: Removed option %s", __FUNCTION__,
                     CONFIG_ROUTE_TYPES.c_str());
            route_types.clear();
            route_types.insert(eos::ROUTE_TYPE_STATIC_CONFIG);
         } else {
            // Clear existing route_types configuration.
            route_types.clear();

            // Need to make a copy since strtok() expects a
            // writable string.
            char rtypes[ROUTE_TYPES_OPTIONS_VALUE_MAX];
            strncpy( rtypes, value.c_str(), sizeof( rtypes));

            // Make sure rtypes is NULL terminated
            rtypes[ROUTE_TYPES_OPTIONS_VALUE_MAX-1] = '\0';

            // Process all the route types configured.
            char *rtype = strtok(rtypes, ", \t");
            while(rtype) {
               t.trace0("%s: rtype=%s", __FUNCTION__, rtype);
               if (rtype == ROUTE_TYPE_BGP) {
                  route_types.insert(eos::ROUTE_TYPE_BGP);
               } else if (rtype == ROUTE_TYPE_IBGP) {
                  route_types.insert(eos::ROUTE_TYPE_IBGP);
               } else if (rtype == ROUTE_TYPE_EBGP) {
                  route_types.insert(eos::ROUTE_TYPE_EBGP);
               } else if (rtype == ROUTE_TYPE_BGP_AGGREGATE) {
                  route_types.insert(eos::ROUTE_TYPE_BGP_AGGREGATE);
               } else if (rtype == ROUTE_TYPE_STATIC_CONFIG ) {
                  route_types.insert(eos::ROUTE_TYPE_STATIC_CONFIG);
               }
               rtype = strtok(NULL, ", \t");
            }

            // If no valid route type is found assume static type.
            if (route_types.empty()) {
               t.trace3("%s: No valid route type found. Assume static type.",
                        __FUNCTION__);
               route_types.insert(eos::ROUTE_TYPE_STATIC_CONFIG);
            }
            t.trace0("%s: Option %s set to %s.",
                     __FUNCTION__,
                     CONFIG_ROUTE_TYPES.c_str(),
                     convert(route_types).c_str());
         }

         update_status(STATUS_ROUTE_TYPES, convert(route_types));
         update_acl = true;

      }

      if (initialized and update_acl) {
         schedule_acl_update(true);
      }
   }

   void schedule_acl_update(bool nodelay=false) {
      // Schedule deferred ACL update. An exponential back-off timer is
      // used to defer update processing so that we can combine ACL updates
      // for multiple route changes. The following variables determine the
      // timeout value when the timer is started.
      //
      // acl_update_timer_min : User configurable default minimum timeout
      // acl_update_timer_max : User configurable default maximum timeout
      // acl_update_timer     : Current timeout value
      //
      // We use this simple algorithm:
      // 1. If the last ACL update was within acl_update_timer seconds set
      //    acl_update_timer to 2 * acl_update_timer.
      // 2. If not, reset acl_update_timer to acl_update_timer_min.
      // 3. If acl_update_timer > acl_update_timer_max set acl_update_timer
      //    to acl_update_timer_max.
      // 4. Schedule the timer with acl_update_timer seconds timeout.

      t.trace3("%s: nodelay=%s", __FUNCTION__, nodelay? "true" : "false");

      if (acl_update_timer_max < acl_update_timer_min) {
         t.trace0("Invalid configuration: "
                  "acl_update_timer_max < acl_update_timer_min");
      }

      if (nodelay) {
         // Most likely a config change has occurred. Schedule immediate ACL
         // update and reset the timeout to acl_update_timer_min.

         timeout_time_is(eos::now());
         acl_update_timer = acl_update_timer_min;
         update_status(STATUS_ACL_UPDATE_TIMER, acl_update_timer);
         pending_updates = true;
         t.trace3("%s: ACL update scheduled[ %f %f ]", __FUNCTION__,
                  eos::now(), 0.0);

      } else if (!pending_updates) {
         // Timer not active. Start now.
         if (last_update_time + acl_update_timer > eos::now()) {
            acl_update_timer = acl_update_timer * 2;
            if (acl_update_timer > acl_update_timer_max) {
               acl_update_timer = acl_update_timer_max;
            }
         } else {
            acl_update_timer = acl_update_timer_min;
         }

         timeout_time_is(eos::now() + acl_update_timer);
         t.trace3("%s: ACL update scheduled[ %f %f ]", __FUNCTION__,
                  eos::now(), acl_update_timer);
         update_status(STATUS_ACL_UPDATE_TIMER, acl_update_timer);
         pending_updates = true;

      } else {
         t.trace3("%s: ACL update pending.", __FUNCTION__);
      }

      update_status(STATUS_LAST_UPDATE_STATUS, "Waiting for ACL update");
   }

   void flush_all_rules_in_acls() {
      // Flush the existing rules in both V4 and V6 ACLs.
      t.trace3("%s: ", __FUNCTION__);
      uint32_t seq = 0;
      bool v4_acl_configured = !ipv4_access_list_name.empty();
      bool v6_acl_configured = !ipv6_access_list_name.empty();

      seq = ACL_SEQ_INCR;
      if (v4_acl_configured && (acl4_seq >= ACL_SEQ_INCR)) {
         t.trace3("%s: Removing rules %d to %d from %s",
                  __FUNCTION__, ACL_SEQ_INCR, (acl4_seq - ACL_SEQ_INCR),
                  ipv4_access_list_name.c_str());
         auto acl4 = eos::acl_key_t(ipv4_access_list_name, eos::ACL_TYPE_IPV4);
         while (seq < acl4_seq) {
            get_acl_mgr()->acl_rule_del(acl4, seq);
            seq += ACL_SEQ_INCR;
         }
      }

      seq = ACL_SEQ_INCR;
      if (v6_acl_configured && (acl6_seq >= ACL_SEQ_INCR)) {
         t.trace3("%s: Removing rules %d to %d from %s",
                  __FUNCTION__, ACL_SEQ_INCR, (acl6_seq - ACL_SEQ_INCR),
                  ipv6_access_list_name.c_str());
         auto acl6 = eos::acl_key_t(ipv6_access_list_name, eos::ACL_TYPE_IPV6);
         while (seq < acl6_seq) {
            get_acl_mgr()->acl_rule_del(acl6, seq);
            seq += ACL_SEQ_INCR;
         }
      }

      acl4_seq = ACL_SEQ_INCR;
      acl6_seq = ACL_SEQ_INCR;
   }

   void update_acls() {
      t.trace3( "%s: Processing pending ACL update", __FUNCTION__);
      // Iterate over the fib routes and add permit rules for the routes
      // matching route_type configured.
      bool v4_acl_configured = !ipv4_access_list_name.empty();
      bool v6_acl_configured = !ipv6_access_list_name.empty();

      if (!v4_acl_configured && !v6_acl_configured){
         t.trace3("%s: V4 and V6 ACLs not configured.", __FUNCTION__);
         update_status(STATUS_LAST_UPDATE_STATUS, "V4 and V6 ACLs not configured");
         pending_updates = false;
         return;
      }

      // Remove all existing rules in both V4 and V6 ACLs
      flush_all_rules_in_acls();

      auto acl4 = eos::acl_key_t(ipv4_access_list_name, eos::ACL_TYPE_IPV4);
      auto acl6 = eos::acl_key_t(ipv6_access_list_name, eos::ACL_TYPE_IPV6);
      acl4_seq = ACL_SEQ_INCR;
      acl6_seq = ACL_SEQ_INCR;

      for (auto i = get_fib_mgr()->fib_route_iter(); i; ++i) {
         if (route_types.find(i->route_type()) != route_types.end()) {
            auto route_key = i->route_key();
            auto prefix = route_key.prefix();
            auto rule = eos::acl_rule_ip_t();
            eos::ip_addr_mask_t destination_addr(prefix.network(),
                                            prefix.prefix_length());

            // Create an ACL rule with the destination matching route prefix.
            rule.action_is(eos::ACL_PERMIT);
            rule.destination_addr_is(destination_addr);

            if ((prefix.af() == eos::AF_IPV4) && (v4_acl_configured)) {
               t.trace3("%s: Adding rule %u", __FUNCTION__, acl4_seq);
               get_acl_mgr()->acl_rule_set(acl4, acl4_seq, rule);
               acl4_seq += ACL_SEQ_INCR;
            } else if ((prefix.af() == eos::AF_IPV6) && (v6_acl_configured)) {
               t.trace3("%s: Adding rule %u", __FUNCTION__, acl4_seq);
               get_acl_mgr()->acl_rule_set(acl6, acl6_seq, rule);
               acl6_seq += ACL_SEQ_INCR;
            }
         }
      }

      // Commit the changes.
      get_acl_mgr()->acl_commit();
      t.trace3("%s: Processed pending ACL config update", __FUNCTION__);

      // Until we receive the commit confirmation ACL commit is
      // not guaranteed to succeed.
      update_status(STATUS_LAST_UPDATE_STATUS,
                    "Waiting for ACL commit confirmation");
      last_update_time = eos::now();
      pending_updates = false;
   }

   void remove_v4_acl() {
      if (initialized && !ipv4_access_list_name.empty()) {
         auto acl4 = eos::acl_key_t(ipv4_access_list_name, eos::ACL_TYPE_IPV4);
         get_acl_mgr()->acl_del(acl4);
      }
   }

   void remove_v6_acl() {
      if (initialized && !ipv6_access_list_name.empty()) {
         auto acl6 = eos::acl_key_t(ipv6_access_list_name, eos::ACL_TYPE_IPV6);
         get_acl_mgr()->acl_del(acl6);
      }
   }

   template<typename T>
   void update_status(std::string const &status, T value) {
      std::ostringstream s;
      s << value;
      agentMgr->status_set(status.c_str(), s.str());
   }

   std::string convert(std::set<eos::fib_route_type_t> & type) {
      bool start = true;
      std::string route_types_str;
      for (std::set<eos::fib_route_type_t>::iterator itr=type.begin();
           itr!=type.end(); ++itr) {

         if (start) {
            start = false;
         } else {
            route_types_str.append(", ");
         }

         switch(*itr) {
            case eos::ROUTE_TYPE_BGP:
               route_types_str.append(ROUTE_TYPE_BGP);
               break;
            case eos::ROUTE_TYPE_IBGP:
               route_types_str.append(ROUTE_TYPE_IBGP);
               break;
            case eos::ROUTE_TYPE_EBGP:
               route_types_str.append(ROUTE_TYPE_EBGP);
               break;
            case eos::ROUTE_TYPE_BGP_AGGREGATE:
               route_types_str.append(ROUTE_TYPE_BGP_AGGREGATE);
               break;
            case eos::ROUTE_TYPE_STATIC_CONFIG:
               route_types_str.append(ROUTE_TYPE_STATIC_CONFIG);
               break;
            default:
               route_types_str.append("unknown");
         }
      }
      return route_types_str;
   }

 private:
   eos::tracer t;
   bool pending_updates;
   uint64_t update_success_counter;
   uint64_t update_fail_counter;
   double last_update_time;
   float acl_update_timer_min;
   float acl_update_timer_max;
   float acl_update_timer;
   std::string vrf;
   std::string ipv4_access_list_name;
   std::string ipv6_access_list_name;
   std::set<eos::fib_route_type_t>route_types;
   uint32_t acl4_seq;
   uint32_t acl6_seq;
   bool initialized;
};

int
main(int argc, char ** argv) {
   eos::sdk sdk;
   fib_acl_sync fib_acl_sync(sdk);
   sdk.main_loop(argc, argv);
}
