// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/ham.h"
#include "impl.h"

namespace eos{

ham_handler::ham_handler( ham_mgr * mgr ) : base_handler< ham_mgr, ham_handler >(
      mgr ){
}

class ham_mgr_impl : public ham_mgr {
 public:
   ham_mgr_impl(){
   }

   void ham_is( eossdk_ham_t ham ){

   }

   bool exists() const {
      return false;
   }

   response_enum_t read8( register_t reg, uint8_t * result ){
      response_enum_t * nop = 0;
      return *nop;
   }

   response_enum_t read16( register_t reg, uint16_t * result ){
      response_enum_t * nop = 0;
      return *nop;
   }

   response_enum_t read32( register_t reg, std::string * result ){
      response_enum_t * nop = 0;
      return *nop;
   }

   response_enum_t read( register_t reg, std::string * result, size_t size ){
      response_enum_t * nop = 0;
      return *nop;
   }

   response_enum_t readBlock( register_t reg, std::string * result ){
      response_enum_t * nop = 0;
      return *nop;
   }

   response_enum_t write8( register_t reg, uint8_t data,
                                bool reliable = false ){
      response_enum_t * nop = 0;
      return *nop;
   }

   response_enum_t write16( register_t reg, uint16_t data,
                                 bool reliable = false ){
      response_enum_t * nop = 0;
      return *nop;
   }

   response_enum_t write32( register_t reg, uint32_t data,
                                 bool reliable = false ){
      response_enum_t * nop = 0;
      return *nop;
   }

   response_enum_t write( register_t reg, uint32_t data,
                          size_t size, bool reliable ){
      response_enum_t * nop = 0;
      return *nop;
   }

   response_enum_t writeBlock( register_t reg, uint32_t data,
                               size_t size, bool reliable ){
      response_enum_t * nop = 0;
      return *nop;
   }

};

DEFINE_STUB_MGR_CTOR( ham_mgr )

} // end namespace eos
