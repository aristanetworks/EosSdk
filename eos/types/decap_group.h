// Copyright (c) 2021 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_DECAP_GROUP_H
#define EOS_TYPES_DECAP_GROUP_H

#include <eos/hash_mix.h>
#include <eos/ip.h>
#include <eos/utility.h>
#include <memory>
#include <sstream>

namespace eos {

/**
 * Inner (IP) protocol to match for a decap group,
 * only the GRE protocol is presently supported.
 */
enum decap_protocol_type_t {
   PROTOCOL_TYPE_NULL,
   PROTOCOL_TYPE_GRE,
};
/**
 * Appends a string representation of enum decap_protocol_type_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const decap_protocol_type_t & enum_val);

class decap_group_impl_t;
/**
 * An IP decap group configuration model. At this time, all decap  groups are
 * configured in the default VRF.
 */
class EOS_SDK_PUBLIC decap_group_t {
 public:
   decap_group_t();
   decap_group_t(std::string const & group_name,
                 ip_addr_t const & destination_addr,
                 decap_protocol_type_t protocol_type);
   decap_group_t(const decap_group_t& other);
   decap_group_t& operator=(
      decap_group_t const & other);


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

   bool operator==(decap_group_t const & other) const;
   bool operator!=(decap_group_t const & other) const;
   bool operator<(decap_group_t const & other) const;
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
   friend std::ostream& operator<<(std::ostream& os, const decap_group_t& obj);

 private:
   std::shared_ptr<decap_group_impl_t> pimpl;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const decap_group_t& obj);
}

#endif // EOS_TYPES_DECAP_GROUP_H
