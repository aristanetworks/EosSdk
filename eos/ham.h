// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_HAM_H
#define EOS_HAM_H

#include <eos/base_handler.h>
#include <eos/base.h>
#include <eos/base_mgr.h>
#include <eos/types/ham.h>


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
    * Create the EosSdk HAM object to use for future reads and writes.
    */
   virtual void ham_is( eossdk_ham_t ham ) = 0;

   /**
    * Verifies that the HAM object was successfully created and exists.
    */
   virtual bool exists() const = 0;

   /**
    * Called to read 8 bytes of data at a time from given register, stores
    * the 8 bytes that was read within 'result', using the HAM created in
    * the ham_is API.
    */
   virtual eos::response_enum_t read8( register_t reg, uint8_t * result ) = 0;

   /**
    * Called to read 16 bytes of data at a time from given register, stores
    * the 16 bytes that was read within 'result', using the HAM created in
    * the ham_is API.
    */
   virtual eos::response_enum_t read16( register_t reg, uint16_t * result ) = 0;

   /**
    * Called to read 32 bytes of data at a time from given register, stores
    * the 32 bytes that was read within 'result', using the HAM created in
    * the ham_is API. Uses string ptr to store result because underlying pluto
    * call requires a string pointer for this call.
    */
   virtual eos::response_enum_t read32( register_t reg, std::string * result ) = 0;

   /**
    * Called to issue an I2C variable-sized/block read from given register.
    * Reads up to 'size' amount of bytes of data from given register, and
    * stores the bytes that were read within 'result'. Uses the HAM created
    * in the ham_is API.
    */
   virtual eos::response_enum_t read( register_t reg, std::string * result,
                                      size_t size ) = 0;

   /**
    * Called to issue am Smbus block read from given register, stores the bytes
    * that were read within 'result', using the HAM created in
    * the ham_is API. Reads up to a max of 32 bytes from register.
    * Uses string ptr to store result because underlying pluto
    * call requires a string pointer for this call.
    */
   virtual eos::response_enum_t readBlock( register_t reg,
                                           std::string * result ) = 0;

   /**
    * Called to write 8 bytes that are stored in 'data' to register 'reg',
    * using the HAM created in the ham_is API. 'reliable' represents if the
    * data transfer was reliable/successful or not.
    */
   virtual eos::response_enum_t write8( register_t reg, uint8_t data,
                                        bool reliable = false ) = 0;

   /**
    * Called to write 16 bytes that are stored in 'data' to register 'reg',
    * using the HAM created in the ham_is API. 'reliable' represents if the
    * data transfer was reliable/successful or not.
    */
   virtual eos::response_enum_t write16( register_t reg, uint16_t data,
                                         bool reliable = false ) = 0;

   /**
    * Called to write 32 bytes that are stored in 'data' to register 'reg',
    * using the HAM created in the ham_is API. 'reliable' represents if the
    * data transfer was reliable/successful or not.
    */
   virtual  eos::response_enum_t write32( register_t reg, uint32_t data,
                                          bool reliable = false ) = 0;

   /**
    * Called to issue an I2C variable-sized/block write call, writes a block of data
    * of a given size to register 'reg', using the HAM created in the ham_is API.
    * Stores the result in 'data'. 'reliable' represents if the data transfer was
    * reliable/successful or not.
    */
   virtual eos::response_enum_t write( register_t reg, uint32_t data,
                                       size_t size, bool reliable ) = 0;

   /**
    * Called to issue an Smbus write block call, writes a block of data of a
    * given size to register 'reg',  using the HAM created in the ham_is API.
    * Stores the result in 'data'.
    * 'reliable' represents if the data transfer was reliable/successful or not.
    */
   virtual  eos::response_enum_t writeBlock( register_t reg, uint32_t data,
                                             size_t size, bool reliable ) = 0;

  protected:
   ham_mgr() EOS_SDK_PRIVATE;
   friend class ham_handler;

  private:
   EOS_SDK_DISALLOW_COPY_CTOR( ham_mgr );

};
}

#include <eos/inline/ham.h>
#endif // EOS_HAM_H
