// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/class_map.h"
#include "eos/exception.h"
#include "impl.h"

namespace std {

size_t hash<eos::policy_map_action_t>::operator() (eos::policy_map_action_t
                                                   const & action) const {
   // TODO: no op impl
   return 0;
}

size_t hash<eos::policy_map_key_t>::operator() (eos::policy_map_key_t
                                                const & key) const {
   // TODO: no op impl
   return 0;
}

}

namespace eos {

policy_map_handler::policy_map_handler(policy_map_mgr * mgr) : 
      base_handler<policy_map_mgr, policy_map_handler>(mgr) {
}

void
policy_map_handler::watch_all_policy_maps(bool interest) {
   // TODO: no op impl.
}

void
policy_map_handler::watch_policy_map(policy_map_key_t const & key,
                                         bool interest) {
   // TODO: no op impl.
}

void
policy_map_handler::watch_policy_map(policy_map_key_t const & key,
                                     std::string const & name,
                                     bool interest) {
   // TODO: no op impl.
}

void
policy_map_handler::on_policy_map_sync_fail(policy_map_key_t const & key,
                                            std::string const & message) {
   // TODO: no op impl.
}

void
policy_map_handler::on_policy_map_sync(policy_map_key_t const & key) {
   // TODO: no op impl.
}

void
policy_map_handler::on_policy_map_config_set(policy_map_key_t const & name) {
   // TODO: no op impl.
}

#if TRAFFIC_POLICY_ENABLED
void
policy_map_handler::on_traffic_policy_config_set( policy_map_key_t const & name ) {
   // TODO: no op impl.
}
#endif

class policy_map_mgr_impl : public policy_map_mgr {
 public:
   policy_map_mgr_impl() {
   }

   void resync_init() {
   }

   void resync_complete() {
   }

   bool exists(policy_map_key_t const & key) const {
      return false;
   }

   #if TRAFFIC_POLICY_ENABLED
   bool traffic_policy_exists(std::string const & key) const {
      return false;
   }
   #endif

   policy_map_t policy_map(policy_map_key_t const & key) const {
      return policy_map_t();
   }

   void policy_map_is(policy_map_t const & policy_map) {
   }

   void policy_map_del(policy_map_key_t const & key) {
   }

   #if TRAFFIC_POLICY_ENABLED
   traffic_policy_t traffic_policy(std::string const & tpName) const {
      return traffic_policy_t("");
   }

   void traffic_policy_is(traffic_policy_t const & tp) {
   }

   void traffic_policy_del(std::string const & tpName) {
   }
   #endif

   policy_map_iter_t policy_map_iter(policy_feature_t) const {
      policy_map_iter_t * nop = 0;
      return *nop;
   }

   #if TRAFFIC_POLICY_ENABLED
   policy_map_iter_t traffic_policy_iter() const {
      policy_map_iter_t * nop = 0;
      return *nop;
   }
   #endif

   void policy_map_apply(policy_map_key_t const &, intf_id_t,
                         acl_direction_t, bool apply) {
   }

   #if TRAFFIC_POLICY_ENABLED
   void traffic_policy_apply(std::string const &, intf_id_t,
                             traffic_policy_direction_t, bool apply) {
   }
   #endif

   policy_map_hw_status_iter_t policy_map_hw_status_iter(policy_feature_t) const {
      policy_map_hw_status_iter_t *nop = 0;
      return *nop;
   }
   
   policy_map_hw_statuses_t hw_status(policy_map_key_t const &key) const {
      return policy_map_hw_statuses_t();
   }

};

DEFINE_STUB_MGR_CTOR(policy_map_mgr)

}
