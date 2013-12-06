// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_CONVERSIONS_H
#define EOSSDK_CONVERSIONS_H

namespace eos {

struct IntfIdHelper : public Arnet::IntfId {
   explicit IntfIdHelper(intf_id_t intfId) {
      intfIdIs(intfId.intfId_);
   }
};

static inline intf_id_t convert(Arnet::IntfId i) {
   return intf_id_t(i.intfId());
}


static inline Arnet::IntfId convert(intf_id_t i) {
   return IntfIdHelper(i);
}

};

#endif // EOSSDK_CONVERSIONS_H
