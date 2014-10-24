// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_DECAP_GROUP_H
#define EOS_TYPES_DECAP_GROUP_H

#include <eos/ip.h>
#include <eos/utility.h>
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
std::ostream& operator<<(std::ostream& os, 
                         const decap_protocol_type_t & enum_val);

/**
 * An ip decap-group configuration model.
 * Note that once created, the group_name member cannot be changed.
 */
class EOS_SDK_PUBLIC decap_group_t {
 public:
   decap_group_t();
   decap_group_t(std::string group_name, ip_addr_t const & destination_addr, 
                 decap_protocol_type_t protocol_type);

   /**
    * Getter for 'group_name': the decap-group name, must be supplied.  Note that
    * the decap group namespace is per-VRF, that is, the vrf_name scopes the decap-
    * group name.
    */
   std::string group_name() const;

   /**
    * Getter for 'destination_addr': match destination IP on the outermost IP
    * header.
    */
   ip_addr_t destination_addr() const;
   /** Setter for 'destination_addr'. */
   void destination_addr_is(ip_addr_t const & destination_addr);

   /** Getter for 'protocol_type': match this outer IP protocol to decap. */
   decap_protocol_type_t protocol_type() const;
   /** Setter for 'protocol_type'. */
   void protocol_type_is(decap_protocol_type_t protocol_type);

   /**
    * Getter for 'persistent': if true, the decap group is included in the running-
    * config. Defaults to false.
    */
   bool persistent() const;
   /** Setter for 'persistent'. */
   void persistent_is(bool persistent);

   bool operator==(decap_group_t const & other) const;
   bool operator!=(decap_group_t const & other) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of decap_group_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const decap_group_t& obj);

 private:
   std::string group_name_;
   ip_addr_t destination_addr_;
   decap_protocol_type_t protocol_type_;
   bool persistent_;
};
}

#include <eos/inline/types/decap_group.h>

#endif // EOS_TYPES_DECAP_GROUP_H
