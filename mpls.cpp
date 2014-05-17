// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/exception.h"
#include "eos/mpls.h"
#include "eos/panic.h"

namespace eos {

static uint32_t const mpls_label_unset = 0x100000;

mpls_label_t::mpls_label_t() {
   label_ = mpls_label_unset;
}

mpls_label_t::mpls_label_t(uint32_t label) {
   if(label == mpls_label_unset) {
      panic(invalid_argument_error("Cannot use the null mpls label"));
   }
   label_ = label;
}

bool mpls_label_t::operator!() const {
   return (label_ == mpls_label_unset);
}

}
