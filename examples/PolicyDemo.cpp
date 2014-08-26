// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <unordered_set>

#include <eos/agent.h>
#include <eos/acl.h>
#include <eos/intf.h>
#include <eos/class_map.h>
#include <eos/policy_map.h>
#include <eos/sdk.h>
#include <eos/system.h>

#include <cstdio>

class policy_demo : public eos::agent_handler,
                    public eos::acl_handler,
                    public eos::policy_map_handler {
 public:
   explicit policy_demo(eos::sdk & sdk)
         : eos::agent_handler(sdk.get_agent_mgr()),
           eos::acl_handler(sdk.get_acl_mgr()),
           eos::policy_map_handler(sdk.get_policy_map_mgr()) {

      // Setup manager refs
      class_mgr = sdk.get_class_map_mgr();

      // Register for all ACL updates; when programming policies,
      //
      // ACLs must be programmed before class maps before policy maps,
      // and they may fail independently of policy-map based PBR
      // programming. If ACL programming for ACLs used in class-maps
      // fails, the reported problem must be resolved before PBR
      // programming will complete.
      watch_all_acls(true);

   }

   ~policy_demo() {
   }

   void on_initialized() {
      printf("on_initialized - policy_demo starting\n");
      setup_policy();
   }

   void setup_policy() {
      eos::ip_addr_t sip;
      eos::parse_ip_addr("0.0.0.0", &sip);

      auto acl1 = eos::acl_key_t("acl1", eos::ACL_TYPE_IPV4);
      auto rule = eos::acl_rule_ip_t();
      // match source 0/0 (all traffic) for PBR
      rule.action_is(eos::ACL_PERMIT);
      rule.source_addr_is(eos::ip_addr_mask_t(sip, 1));
      rule.destination_addr_is(eos::ip_addr_mask_t(sip, 32));
      get_acl_mgr()->acl_rule_set(acl1, 1, rule);
      get_acl_mgr()->acl_commit();

      // now build the class map for that ACL and commit it
      auto cmkey = eos::class_map_key_t("cm1", eos::POLICY_FEATURE_PBR);
      auto cm = eos::class_map_t(cmkey);
      cm.rule_set(1, eos::class_map_rule_t(acl1));
      class_mgr->class_map_is(cm);

      // build a policy map which drops that traffic
      auto pmkey = eos::policy_map_key_t("pm1", eos::POLICY_FEATURE_PBR);
      auto pm = eos::policy_map_t(pmkey);
      // add the policy map rule matching our class map and dropping the traffic
      auto pmrule = eos::policy_map_rule_t(cmkey);
      auto action = eos::policy_map_action_t(eos::POLICY_ACTION_DROP);
      pmrule.action_set(action);
      pm.rule_set(1, pmrule);

      // commit the policy map
      get_policy_map_mgr()->policy_map_is(pm);
      // Finally, apply the policy map to the management interface to block access
      get_policy_map_mgr()->policy_map_apply(pmkey,
                                             eos::intf_id_t("Management0"),
                                             eos::ACL_IN,
                                             true);
   }

 private:
   eos::class_map_mgr * class_mgr;
};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   policy_demo demo(sdk);

   printf("Starting PolicyDemo\n");
   sdk.main_loop(argc, argv);
}
