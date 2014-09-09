// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/policy_map.h"
#include <eos/class_map.h>
#include <eos/exception.h>

namespace eos {

static std::string const RULE_CONFIG_ERROR_ = \
   "Policy maps have either one MPLS match rule or a collection of other rules";


void
policy_map_t::rules_is(std::map<uint32_t, policy_map_rule_t> const & rules) {
   uint32_t mpls_ = 0;
   uint32_t non_mpls_ = 0;
   for(auto it = rules.cbegin(); it != rules.cend(); ++it) {
      if (it->second.class_map_key().name() == CLASS_MAP_MPLS_ANY) {
         mpls_++;
      } else {
         non_mpls_++;
      }
   }
   if ((non_mpls_ > 0 && mpls_ > 0) || mpls_ > 1) {
      panic(configuration_error(RULE_CONFIG_ERROR_));
   }
   rules_ = rules;
   
}

void
policy_map_t::rule_set(uint32_t key, policy_map_rule_t const & value) {
   // We can set only one MPLS rule and no others in a map.
   if(rules_.size() > 1 || 
        (rules_.size() && rules_.cbegin()->first != key)) {
      if(value.class_map_key().name() == CLASS_MAP_MPLS_ANY){
         panic(configuration_error(RULE_CONFIG_ERROR_));
      } else {
         if(rules_.cbegin()->second.class_map_key().name() == 
               CLASS_MAP_MPLS_ANY) {
            panic(configuration_error(RULE_CONFIG_ERROR_));
         }
      }
   }
   rules_[key] = value;
   
}


}
