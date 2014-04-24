// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_CLASS_MAP_H
#define INLINE_CLASS_MAP_H

namespace eos {

inline class_map_rule_t::class_map_rule_t() : acl_key_() {
}

inline class_map_rule_t::class_map_rule_t(acl_key_t const & acl_key)
      : acl_key_(acl_key) {
}

inline class_map_iter_t::class_map_iter_t(class_map_iter_impl *) {
}

inline class_map_rule_iter_t::class_map_rule_iter_t(class_map_rule_iter_impl *) {
}

}

#endif // INLINE_CLASS_MAP_H
