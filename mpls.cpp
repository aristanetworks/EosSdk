// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/exception.h"
#include "eos/mpls.h"

namespace eos {

static uint32_t const mpls_label_unset = 0x100000;

mpls_label_t::mpls_label_t() {
   label_ = mpls_label_unset;
}

invalid_range_error invalid_mpls_label(uint32_t label) {
   return invalid_range_error("label", mpls_label_t::MIN, mpls_label_t::MAX);
}

bool mpls_label_t::operator!() const {
   return label_ == mpls_label_unset;
}

}
