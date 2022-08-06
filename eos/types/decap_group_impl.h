// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_DECAP_GROUP_IMPL_H
#define EOS_TYPES_DECAP_GROUP_IMPL_H

#include <eos/hash_mix.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

/**
 * An IP decap group configuration model. At this time, all decap  groups are
 * configured in the default VRF.
 */
class EOS_SDK_PUBLIC decap_group_impl_t {
 public:
   decap_group_impl_t();
   decap_group_impl_t(std::string const & group_name,
                      ip_addr_t const & destination_addr,
                      decap_protocol_type_t protocol_type);

   /**
    * Getter for 'group_name': the decap group name. Used to uniquely identify this
    * group.
    */
   std::string group_name() const;

   /**
    * Getter for 'destination_addr': match this destination IP on the outermost IP
    * header.
    */
   ip_addr_t destination_addr() const;
   /** Setter for 'destination_addr'. */
   void destination_addr_is(ip_addr_t const & destination_addr);

   /**
    * Getter for 'protocol_type': decapsulate only packets matching this outer IP
    * protocol type.
    */
   decap_protocol_type_t protocol_type() const;
   /** Setter for 'protocol_type'. */
   void protocol_type_is(decap_protocol_type_t protocol_type);

   bool operator==(decap_group_impl_t const & other) const;
   bool operator!=(decap_group_impl_t const & other) const;
   bool operator<(decap_group_impl_t const & other) const;
   /** The hash function for type decap_group_t. */
   uint32_t hash() const;
   /** The hash mix function for type decap_group_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of decap_group_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const decap_group_impl_t& obj);

 private:
   std::string group_name_;
   ip_addr_t destination_addr_;
   decap_protocol_type_t protocol_type_;
};
}

#endif // EOS_TYPES_DECAP_GROUP_IMPL_H
