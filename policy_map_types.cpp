// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/policy_map.h"
#include <eos/class_map.h>
#include <eos/exception.h>

namespace eos {

static std::string const RULE_CONFIG_ERROR_ = \
   "Policy maps have either one MPLS match rule or a collection of other rules";

}
