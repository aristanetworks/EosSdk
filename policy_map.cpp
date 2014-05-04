// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/policy_map.h"

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

policy_map_mgr::policy_map_mgr() {
}

policy_map_mgr::~policy_map_mgr() {
}

policy_map_handler::policy_map_handler(policy_map_mgr * mgr) : base_handler(mgr) {
}

void
policy_map_handler::watch_policy_map(policy_map_key_t const & key,
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

}
