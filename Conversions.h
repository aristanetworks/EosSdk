// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_INTFID_H
#define EOSSDK_INTFID_H

namespace eos {

struct IntfIdHelper : public Arnet::IntfId {
   explicit IntfIdHelper(U32 intfId) {
      intfIdIs(intfId);
   }
   explicit IntfIdHelper(intf_id_t intfId) {
      intfIdIs(intfId.intfId_);
   }
};

static inline intf_id_t intf_id_t_helper( Arnet::IntfId i ) {
   return intf_id_t( i.intfId() );
}


};

#endif // EOSSDK_INTFID_H
