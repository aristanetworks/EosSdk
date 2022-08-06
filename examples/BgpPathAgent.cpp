// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/bgp_path.h>
#include <eos/sdk.h>
#include <eos/tracing.h>
#include <eos/timer.h>
#include <unordered_map>

uint32_t DUMP_INTERVAL = 60;

/**
 * This example agent reacts to the post-policy path change from IPv4 and IPv6
 * Unicast Adj-RIB-In and maintains a local copy of it.
 * It dumps the post-policy IPv4 and IPv6 Unicast Adj-RIB-In every minute into
 * the agent log file after BGP is converged. The nexthop and community list
 * fields are enabled in the options.
 *
 * To enable tracing, add the following configuration:
 *   switch(config)# trace <agent>-<daemon> setting BgpPathTestAgent
 *
 */
namespace std {
   template <>
   struct hash<eos::bgp_path_key_t> {
       size_t operator() ( const eos::bgp_path_key_t & path_key) const {
           uint32_t prefix_hash = path_key.prefix().hash();
           uint32_t peer_hash  = path_key.peer_addr().hash(); 
           uint32_t vrf_hash = std::hash<std::string>()(path_key.vrf_name());
           return prefix_hash ^ peer_hash ^ vrf_hash;
       }
   };
}

class BgpPathTestAgent : public eos::agent_handler,
                         public eos::bgp_path_handler,
                         public eos::timeout_handler {
 public:
   eos::tracer t;
   eos::bgp_path_mgr *bgp_path_mgr_;

   explicit BgpPathTestAgent(eos::sdk & sdk)
      : eos::agent_handler(sdk.get_agent_mgr()),
        eos::bgp_path_handler(sdk.get_bgp_path_mgr()),
        eos::timeout_handler(sdk.get_timeout_mgr()),
        t("BgpPathTestAgent"),
        bgp_path_mgr_(sdk.get_bgp_path_mgr()) {
      t.trace0("Constructed");
      watch_all_paths(true);
   }

   void take_ipv4_unicast_paths_snap_shot() {
      eos::bgp_path_attr_fields_t path_attr_fields(true);
      path_attr_fields.community_list_is(true);
      eos::bgp_path_options_t options(eos::BGP_PATH_POST_POLICY);
      options.path_attr_fields_is(path_attr_fields);

      for (auto iter = bgp_path_mgr_->ipv4_unicast_path_iter(options); iter;
           ++iter) {
         ipv4_unicast_paths[iter->path_key()] = *iter;
      }
   }

   void take_ipv6_unicast_paths_snap_shot() {
      eos::bgp_path_attr_fields_t path_attr_fields(true);
      path_attr_fields.community_list_is(true);
      eos::bgp_path_options_t options(eos::BGP_PATH_POST_POLICY);
      options.path_attr_fields_is(path_attr_fields);

      for (auto iter = bgp_path_mgr_->ipv6_unicast_path_iter(options); iter;
           ++iter) {
         ipv6_unicast_paths[iter->path_key()] = *iter;
      }
   }

   void on_initialized() {
      t.trace0("Initialized");
      bool dump_paths = false;
      if(bgp_path_mgr_->ipv4_unicast_bgp_convergence()) {
          t.trace0("BGP has converged on IPv4 Unicast");
          take_ipv4_unicast_paths_snap_shot();
          dump_paths = true;
      }
      if(bgp_path_mgr_->ipv6_unicast_bgp_convergence()) {
          t.trace0("BGP has converged on IPv6 Unicast");
          take_ipv6_unicast_paths_snap_shot();
          dump_paths = true;
      }
      if(dump_paths) {
         timeout_time_is(eos::now() + 1);
      }
   }

   void on_timeout() {
      t.trace0("Timeout");
      dump_bgp_paths();
      timeout_time_is(eos::now() + DUMP_INTERVAL);
   }

   void dump_bgp_paths() {
      t.trace0("Dumping paths");
      for(auto & iter : ipv4_unicast_paths) {
         t.trace2(iter.second.to_string().c_str());
      }
      for(auto & iter : ipv6_unicast_paths) {
         t.trace2(iter.second.to_string().c_str());
      }
   }

   void on_ipv4_unicast_bgp_converged(bool converged) {
      if(converged) {
         t.trace0("BGP has converged on IPv4 Unicast");
         take_ipv4_unicast_paths_snap_shot();
         timeout_time_is(eos::now() + 1);
      } else {
         ipv4_unicast_paths.clear();
         timeout_time_is(eos::never);
      }
   }

   void on_ipv6_unicast_bgp_converged(bool converged) {
      if(converged) {
         t.trace0("BGP has converged on IPv6 Unicast");
         take_ipv6_unicast_paths_snap_shot();
         timeout_time_is(eos::now() + 1);
      } else {
         ipv6_unicast_paths.clear();
         timeout_time_is(eos::never);
      }
   }

   void on_ipv4_unicast_path(eos::bgp_path_key_t const & path_key) {
      eos::bgp_path_attr_fields_t path_attr_fields(true);
      path_attr_fields.community_list_is(true);
      eos::bgp_path_options_t options(eos::BGP_PATH_POST_POLICY);
      options.path_attr_fields_is(path_attr_fields);

      eos::bgp_path_t path = bgp_path_mgr_->ipv4_unicast_path(path_key, 
                                                              options);
      if(path == eos::bgp_path_t()) {
         
         // path delete
         ipv4_unicast_paths.erase(path_key);
      } else if(ipv4_unicast_paths.count(path_key)){
         
         // path update
         ipv4_unicast_paths[path_key] = path;
      } else {
         
         // new path
         ipv4_unicast_paths[path_key] = path;
      }
   }

   void on_ipv6_unicast_path(eos::bgp_path_key_t const & path_key) {
      eos::bgp_path_attr_fields_t path_attr_fields(true);
      path_attr_fields.community_list_is(true);
      eos::bgp_path_options_t options(eos::BGP_PATH_POST_POLICY);
      options.path_attr_fields_is(path_attr_fields);

      eos::bgp_path_t path = bgp_path_mgr_->ipv6_unicast_path(path_key, 
                                                              options);
      if(path == eos::bgp_path_t()) {
         
         // path delete
         ipv6_unicast_paths.erase(path_key);
      } else if(ipv6_unicast_paths.count(path_key)){
         
         // path update
         ipv6_unicast_paths[path_key] = path;
      } else {
         
         // new path
         ipv6_unicast_paths[path_key] = path;
      }
   }

   void on_agent_enabled(bool enabled) {
      if (!enabled) {
         t.trace0("Shutting down");
         get_agent_mgr()->agent_shutdown_complete_is(true);
      }
   }

 private:
   std::unordered_map<eos::bgp_path_key_t, eos::bgp_path_t> ipv4_unicast_paths;
   std::unordered_map<eos::bgp_path_key_t, eos::bgp_path_t> ipv6_unicast_paths;
};

int main(int argc, char** argv) {
   eos::sdk sdk;
   BgpPathTestAgent agent(sdk);
   sdk.main_loop(argc, argv);
}
