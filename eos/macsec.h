// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

/**
 * @file
 * MACsec management module.
 * 
 * A MACsec profile contains the configuration required to setup a MACsec
 * session. A profile contains a primary key and a fallback key. Each key
 * contains a connectivity association key name (CKN) and a connectivity
 * association key (CAK). Both the CKN and the CAK must be nonzero hex strings,
 * and the CKN of the primary and fallback key cannot be the same.
 *
 * Note: Must have a valid MACsec license configured for this API to work.
 *
 * The following is an example of configuring a MACsec profile
 * and attaching it to an interface.
 *
 * @code
 * // Creating profile "test1" with a primary and fallback key
 * // and a rekey period of 300s
 * eos::macsec_profile_t profile("test1");
 * eos::macsec_key_t primary;
 * primary.ckn_is("aaaa");
 * primary.cak_is("123");
 * eos::macsec_key_t fallback;
 * fallback.ckn_is("bbbb");
 * fallback.cak_is("234");
 * profile.primary_key_is(primary);
 * profile.fallback_key_is(fallback);
 * profile.rekey_period_is(300);
 *
 * // writing profile 'test1'
 * get_macsec_mgr()->profile_set(profile);
 * 
 * // attaching the new profile 'test1' to interface Ethernet1/1
 * eos::intf_id_t intfId("Ethernet1/1");
 * get_macsec_mgr()->intf_profile_is(intfId, "test1");  
 * @endcode
 */

#ifndef EOS_MACSEC_H
#define EOS_MACSEC_H

#include <eos/base.h>
#include <eos/base_handler.h>
#include <eos/base_mgr.h>
#include <eos/intf.h>
#include <eos/iterator.h>

#include <eos/types/macsec.h>

namespace eos {

class macsec_mgr;

class macsec_profile_iter_impl;
class macsec_intf_status_iter_impl;

/**
 * This handler provides notifications when the MACsec status of an interface
 * changes.
 */
class EOS_SDK_PUBLIC macsec_handler :
   public base_handler<macsec_mgr, macsec_handler> {
 public:
   explicit macsec_handler(macsec_mgr*);
   macsec_mgr * get_macsec_mgr() const;

   /**
    * Registers this class to receive change updates on all interfaces.
    *
    * Expects a boolean signifying whether notifications should be
    * propagated to this instance or not.
    */
   void watch_all_intfs(bool);

   /**
    * Registers this class to receive change updates on the given interface.
    *
    * Expects the id of the corresponding interface and a boolean signifying whether
    * notifications should be propagated to this instance or not.
    */
   void watch_intf(intf_id_t, bool);

   /**
    * Called when the key status of a MACsec interface changes.
    */
   virtual void on_intf_status(intf_id_t, macsec_intf_status_t const &);

};

class EOS_SDK_PUBLIC macsec_profile_iter_t : public iter_base<macsec_profile_name_t,
               macsec_profile_iter_impl> {
   private:
      friend class macsec_profile_iter_impl;
      explicit macsec_profile_iter_t( 
            macsec_profile_iter_impl * const ) EOS_SDK_PRIVATE;
};

class EOS_SDK_PUBLIC macsec_intf_status_iter_t : public iter_base<intf_id_t,
               macsec_intf_status_iter_impl> {
   private:
      friend class macsec_intf_status_iter_impl;
      explicit macsec_intf_status_iter_t( 
            macsec_intf_status_iter_impl * const ) EOS_SDK_PRIVATE;
};

/**
 * The MACsec manager.
 * This class inspects and configures MACsec profiles.
 */
class EOS_SDK_PUBLIC macsec_mgr : public base_mgr<macsec_handler, intf_id_t> {
 public:
   virtual ~macsec_mgr();

   /**
    * Returns whether or not a profile with the given name exists.
    */
   virtual bool exists(macsec_profile_name_t const &) const = 0;

   /**
    * Returns the macsec_profile_t with the given name. If no such profile exists,
    * then return an empty profile with nothing configured.
    */
   virtual macsec_profile_t profile(macsec_profile_name_t const &) const = 0;

   /**
    * Writes the given profile to MACsec config. If a profile with the given name
    * already exists, update it with the configuration from the given
    * macsec_profile_t. An unencoded input CAK will be encoded if
    * the macsec_key_t's encoded attribute is set to false.
    */
   virtual void profile_set(macsec_profile_t const &) = 0;

   /**
    * Deletes the profile with the given name if such a profile exists.
    */
   virtual void profile_del(macsec_profile_name_t const &) = 0;

   /**
    * Returns the profile name of the profile attached to the interface.
    * If there is no profile configured, return an empty string.
    */
   virtual macsec_profile_name_t intf_profile(intf_id_t) const = 0;
   
   /**
    * Configures the given interface to use the given MACsec profile.
    * An interface can only have one MACsec profile applied at a time.
    * Applying a new profile to an interface which is already associated with
    * a different profile will overwrite the previous profile. If an empty
    * string is provided as profile name, any existing profile will be removed.
    */
   virtual void intf_profile_is(intf_id_t, macsec_profile_name_t const &) = 0;

   /**
    * Returns an object containing MACsec related status information of the
    * given interface.
    */
   virtual macsec_intf_status_t intf_status(intf_id_t) const = 0;

   /**
    * Returns whether or not an interface supports MACsec.
    */
   virtual bool macsec_capable(intf_id_t) const = 0;

   /*
    * Returns the current MACsec counters for the given interface.
    */
   virtual macsec_intf_counters_t intf_counters(intf_id_t) = 0;

   /*
    * Iterates over macsec profile config.
    */
   virtual macsec_profile_iter_t macsec_profile_iter() const = 0;

   /*
    * Iterates over macsec intf status.
    */
   virtual macsec_intf_status_iter_t macsec_intf_status_iter() const = 0;

 protected:
   macsec_mgr() EOS_SDK_PRIVATE;
   friend class macsec_handler;

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(macsec_mgr);
};

} // namespace eos 

#include <eos/inline/macsec.h>

#endif // EOS_MACSEC_H

