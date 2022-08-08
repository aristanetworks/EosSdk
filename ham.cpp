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

   read8_result_t read8( eossdk_ham_t ham, register_t reg ){
      read8_result_t * nop = 0;
      return *nop;
   }

   read16_result_t read16( eossdk_ham_t ham, register_t reg ){
      read16_result_t * nop = 0;
      return *nop;
   }

   read_result_t read32( eossdk_ham_t ham, register_t reg ){
      read_result_t * nop = 0;
      return *nop;
   }

   read_result_t read( eossdk_ham_t ham, register_t reg, size_t size ){
      read_result_t * nop = 0;
      return *nop;
   }

   read_result_t readBlock( eossdk_ham_t ham, register_t reg ){
      read_result_t * nop = 0;
      return *nop;
   }

   response_enum_t write8( eossdk_ham_t ham, register_t reg, uint8_t data,
                           bool reliable = false ){
      response_enum_t * nop = 0;
      return *nop;
   }

   response_enum_t write16( eossdk_ham_t ham, register_t reg, uint16_t data,
                            bool reliable = false ){
      response_enum_t * nop = 0;
      return *nop;
   }

   response_enum_t write32( eossdk_ham_t ham, register_t reg, uint32_t data,
                            bool reliable = false ){
      response_enum_t * nop = 0;
      return *nop;
   }

   response_enum_t write( eossdk_ham_t ham, register_t reg,
                          std::string const & data, bool reliable = false ){
      response_enum_t * nop = 0;
      return *nop;
   }

   response_enum_t writeBlock( eossdk_ham_t ham, register_t reg,
                               std::string const & data, bool reliable = false ){
      response_enum_t * nop = 0;
      return *nop;
   }

};

DEFINE_STUB_MGR_CTOR( ham_mgr )

} // end namespace eos
