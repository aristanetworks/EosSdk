// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_HAM_H
#define EOS_HAM_H

#include <eos/base_handler.h>
#include <eos/base.h>
#include <eos/base_mgr.h>
#include <eos/types/ham.h>
#include <eos/utility.h>


/**
 * @file
 * HAM management module.
 *
 * Provides a Hardware Access Method manager with read and write APIs to
 * support communication protocols such as i2c within EosSdk.
 */

namespace eos{

class ham_mgr;

class EOS_SDK_PUBLIC ham_handler : public base_handler< ham_mgr, ham_handler > {
  public:
   explicit ham_handler( ham_mgr * );
   ham_mgr * get_ham_mgr() const;
};

class EOS_SDK_PUBLIC ham_mgr : public base_mgr<ham_handler> {
  public:
   virtual ~ham_mgr();

   /**
    * Called to read 8 bytes of data at a time from given register, stores
    * the 8 bytes that was read within the return value's attribute named 'result',
    * and stores the response_enum within the return value's attribute named
    * 'status', using the HAM passed in to this API.
    */
   virtual eos::read8_result_t read8( eossdk_ham_t ham,
                                      register_t reg ) = 0;

   /**
    * Called to read 16 bytes of data at a time from given register, stores
    * the 16 bytes that was read within the return value's attribute named 'result',
    * and stores the response_enum within the return value's attribute named
    * 'status', using the HAM passed into this API.
    */
   virtual eos::read16_result_t read16( eossdk_ham_t ham,
                                        register_t reg ) = 0;

   /**
    * Called to read 32 bytes of data at a time from given register, stores
    * the 32 bytes that was read within the return value's attribute named 'result',
    * and stores the response_enum within the return value's attribute named
    * 'status', using the HAM passed into this API.
    * Uses string ptr to store result because underlying pluto
    * call requires a string pointer for this call.
    */
   virtual eos::read_result_t read32( eossdk_ham_t ham, register_t reg ) = 0;

   /**
    * Called to issue an I2C variable-sized/block read from given register.
    * Reads up to 'size' amount of bytes of data from given register, and
    * stores the bytes that were read within the return value's attribute named
    * 'result'. Uses the HAM passed into this API.
    */
   virtual eos::read_result_t read( eossdk_ham_t ham, register_t reg,
                                    size_t size ) = 0;

   /**
    * Called to issue am Smbus block read from given register, stores the bytes
    * that were read within the return value's attribute named  'result',
    * using the HAM passed into this API.
    * Reads up to a max of 32 bytes from register.
    * Uses string ptr to store result because underlying pluto
    * call requires a string pointer for this call.
    */
   virtual eos::read_result_t readBlock( eossdk_ham_t ham, register_t reg ) = 0;

   /**
    * Called to write 8 bytes that are stored in 'data' to register 'reg',
    * using the HAM passed into this API. 'reliable' represents if the
    * data transfer was reliable/successful or not.
    */
   virtual eos::response_enum_t write8( eossdk_ham_t ham, register_t reg,
                                        uint8_t data, bool reliable = false ) = 0;

   /**
    * Called to write 16 bytes that are stored in 'data' to register 'reg',
    * using the HAM passed into this API. 'reliable' represents if the
    * data transfer was reliable/successful or not.
    */
   virtual eos::response_enum_t write16( eossdk_ham_t ham, register_t reg,
                                         uint16_t data, bool reliable = false ) = 0;

   /**
    * Called to write 32 bytes that are stored in 'data' to register 'reg',
    * using the HAM passed into this API. 'reliable' represents if the
    * data transfer was reliable/successful or not.
    */
   virtual  eos::response_enum_t write32( eossdk_ham_t ham, register_t reg,
                                          uint32_t data, bool reliable = false ) = 0;

   /**
    * Called to issue an I2C variable-sized/block write call, writes a block of data
    * of a given size to register 'reg', using the HAM passed into this API.
    * Stores the result in 'data'. 'reliable' represents if the data transfer was
    * reliable/successful or not.
    */
   virtual eos::response_enum_t write( eossdk_ham_t ham, register_t reg,
                                       eos::ByteString const & data,
                                       bool reliable = false ) = 0;

   /**
    * Called to issue an Smbus write block call, writes a block of data of a
    * given size to register 'reg',  using the HAM passed into this API.
    * Stores the result in 'data'.
    * 'reliable' represents if the data transfer was reliable/successful or not.
    */
   virtual  eos::response_enum_t writeBlock( eossdk_ham_t ham, register_t reg,
                                             eos::ByteString const & data,
                                             bool reliable = false ) = 0;

  protected:
   ham_mgr() EOS_SDK_PRIVATE;
   friend class ham_handler;

  private:
   EOS_SDK_DISALLOW_COPY_CTOR( ham_mgr );

};
}

#include <eos/inline/ham.h>
#endif // EOS_HAM_H
