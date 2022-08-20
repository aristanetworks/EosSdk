// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/sdk.h>
#include <eos/tracing.h>
#include <eos/macsec.h>
#include <eos/types/macsec.h>
#include "BuildOptions.h"

class macsec_demo_agent : public eos::agent_handler,
                          public eos::macsec_handler {
 public:
   eos::tracer t;
   int numStatusChanges = 0;

   explicit macsec_demo_agent(eos::sdk & sdk)
         : eos::agent_handler(sdk.get_agent_mgr()),
           eos::macsec_handler(sdk.get_macsec_mgr()),
           t("MacsecDemo") {
      t.trace0("Agent constructed");
   }

   void on_initialized() {
      t.enabled_is(eos::Level0, true);
      t.trace0("Initialized");
      setup_demo_profiles();
      watch_all_intfs(true);
      get_agent_mgr()->status_set("Ready_for_testing", "True");
   }

   void parse_read_options(std::string const & option_name,
                           std::string const & value) {
      if(option_name == "exists") {
         bool exists = get_macsec_mgr()->exists(value);
         std::string existsStr = exists ? "True" : "False";
         get_agent_mgr()->status_set( "exists", "Profile " + value +
                                      " exists: " + existsStr );
      } else if(option_name == "profile") {
         char buff[300];
         eos::macsec_profile_t profile = get_macsec_mgr()->profile( value );
         if(profile == eos::macsec_profile_t()) {
            sprintf(buff, "Profile %s does not exist!", value.c_str());
         } else {
            eos::macsec_profile_t profile = get_macsec_mgr()->profile( value );
            sprintf( buff,
                     "name: %s\nprimary ckn: %s\nfallback ckn: %s\n"
                     "key server priority: %d\nrekey period: %d\n"
                     "mka lifetime: %d\n"
                     "cipher suite: %d\ndot1x: %d\ninclude sci: %d\n"
                     "bypass lldp: %d\n"
                     "lldp bypass level: %d\n"
                     "traffic policy: %d\n"
                     "replay protection: %d\nreplay protection window: %d\n"
                     "key retirement immediate: %d",
                     profile.name().c_str(),
                     profile.primary_key().ckn().c_str(),
                     profile.fallback_key().ckn().c_str(),
                     profile.key_server_priority(),
                     profile.rekey_period(),
                     profile.mka_life_time(),
                     profile.cipher(),
                     profile.dot1x(),
                     profile.include_sci(),
                     profile.bypass_lldp(),
                     profile.lldp_bypass_level(),
                     profile.traffic_policy(),
                     profile.replay_protection(),
                     profile.replay_protection_window(),
                     profile.key_retirement_immediate() );
         }
         get_agent_mgr()->status_set("profile", buff);
      } else if(option_name == "intf_profile") {
         try {
            eos::intf_id_t intf_id(value);
            std::string profileName = get_macsec_mgr()->intf_profile(intf_id);
            char buff[300];
            if(profileName == "") {
               sprintf(buff, "Interface %s has no profile applied", value.c_str());
            } else {
               sprintf(buff, "%s", profileName.c_str());
            }
            get_agent_mgr()->status_set("intf_profile", buff);
         } catch (eos::no_such_interface_error const & e) {
            t.trace0("intf_profile bad interface name");
            get_agent_mgr()->status_set("intf_profile", "");
         }
      } else if(option_name == "intf_status") {
         try {
            eos::intf_id_t intf_id(value);
            eos::macsec_intf_status_t intf_status =
               get_macsec_mgr()->intf_status(intf_id);
            get_agent_mgr()->status_set("intf_status", intf_status.to_string());
         } catch (eos::no_such_interface_error const & e) {
            t.trace0("intf_status bad interface name");
            get_agent_mgr()->status_set("intf_status", "");
         }
      } else if(option_name == "intf_counters") {
         try {
            eos::intf_id_t intf_id(value);
            eos::macsec_intf_counters_t intf_counters =
               get_macsec_mgr()->intf_counters(intf_id);
            get_agent_mgr()->status_set("intf_counters", intf_counters.to_string());
         } catch (eos::no_such_interface_error const & e) {
            t.trace0("intf_counters bad interface name");
            get_agent_mgr()->status_set("intf_counters", "");
         }
      }
   }

   void parse_write_options(std::string const & option_name,
                            std::string const & value) {
      if(option_name == "profile_del") {
         get_macsec_mgr()->profile_del(value);
      } else if(option_name == "profile_remove") {
         try {
            eos::intf_id_t intf_id(value);
            get_macsec_mgr()->intf_profile_is(intf_id, "");
         } catch (eos::no_such_interface_error const & e) {
            t.trace0("profile_remove bad interface name");
         }
      } else if(option_name == "demo_profile_apply") {
         try {
            eos::intf_id_t intf_id(value);
            get_macsec_mgr()->intf_profile_is(intf_id, "test1");
         } catch (eos::no_such_interface_error const & e) {
            t.trace0("demo_profile_apply bad interface name");
         }
      } else if(option_name == "mismatch_profile_apply") {
         // This profile is used to test switching to the fallback key.
         // It will have a matching fallback key to the demo_profile but
         // a different primary key. 
         try {
            eos::intf_id_t intf_id(value);
            get_macsec_mgr()->intf_profile_is(intf_id, "test2");
         } catch (eos::no_such_interface_error const & e) {
            t.trace0("mismatch_profile_apply bad interface name");
         }
      } else if(option_name == "blank_profile_create") {
         eos::macsec_profile_t profile("blank_profile");
         t.trace0("Creating profile 'blank_profile'");
         get_macsec_mgr()->profile_set(profile);
      } else if(option_name == "blank_profile_apply") {
         try {
            eos::intf_id_t intf_id(value);
            get_macsec_mgr()->intf_profile_is(intf_id, "blank_profile");
         } catch (eos::no_such_interface_error const & e) {
            t.trace0("blank_profile_apply bad interface name");
         }
      } else if(option_name == "watch_all_intfs") {
         if(value == "true") {
            watch_all_intfs(true);
         } else if(value == "false") {
            watch_all_intfs(false);
         }
      } else if(option_name == "watch_intf") {
         try {
            eos::intf_id_t intf_id(value);
            watch_intf(intf_id, true);
         } catch (eos::no_such_interface_error const & e) {
            t.trace0("watch_intf bad interface name");
         }
      }
   }

   void on_agent_option(std::string const & option_name,
                        std::string const & value) {
      parse_read_options(option_name, value);
      parse_write_options(option_name, value);
   }


   void on_agent_enabled(bool enabled) {
      if (!enabled) {
         t.trace0("Shutting down");
         get_agent_mgr()->agent_shutdown_complete_is(true);
      }
   }

   void on_intf_status(eos::intf_id_t intf_id,
                       eos::macsec_intf_status_t const & status) {
      numStatusChanges += 1;
      t.trace0("Macsec key status on intf %s changed to %s, numStatusChanges is %d",
               intf_id.to_string().c_str(), status.to_string().c_str(),
               numStatusChanges);
      char buff[300];
      sprintf(buff, "%s status changed to %s", intf_id.to_string().c_str(),
              status.to_string().c_str());
      get_agent_mgr()->status_set("on_intf_status", buff);
   }

   void setup_demo_profiles() {
      eos::macsec_profile_t profile("test1");
      eos::macsec_key_t primary;
      primary.ckn_is("aaaa");
      primary.cak_is("0055");
      eos::macsec_key_t fallback;
      fallback.ckn_is("bbbb");
      fallback.cak_is("0055");
      profile.primary_key_is(primary);
      profile.fallback_key_is(fallback); 
      int priority = 255;
      profile.key_server_priority_is(priority);
      int rekey_period = 900;
      profile.rekey_period_is(rekey_period);
      int mkalifetime = 30;
      profile.mka_life_time_is(mkalifetime);
      profile.cipher_is(eos::GCM_AES_XPN_128);
      profile.include_sci_is(true);
      profile.traffic_policy_is( eos::TRAFFIC_POLICY_BLOCKED );
      // writing profile 'test1'
      t.trace0("Writing profile 'test1'");
      get_macsec_mgr()->profile_set(profile);

      // create second test profile for testing fallback
      eos::macsec_key_t mismatched_primary;
      mismatched_primary.ckn_is("abc");
      mismatched_primary.cak_is("abc");
      eos::macsec_profile_t profile2("test2");
      profile2.primary_key_is(mismatched_primary);
      profile2.fallback_key_is(fallback);
      get_macsec_mgr()->profile_set(profile2);
   }

};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   macsec_demo_agent agent(sdk);
   sdk.main_loop(argc, argv);
}
