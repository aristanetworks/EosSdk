// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef INLINE_NEXTHOP_GROUP_H
#define INLINE_NEXTHOP_GROUP_H

namespace eos {

inline nexthop_group_t::nexthop_group_t() :
      name_(""), ttl_(64),
      source_ip_(), source_intf_(),
      encap_type_(NEXTHOP_GROUP_TYPE_NULL),
      destination_ips_(),
      persistent_(false) {
}

inline nexthop_group_t::nexthop_group_t(std::string const & name,
                                        nexthop_group_encap_t type) :
      name_(name), ttl_(64),
      source_ip_(), source_intf_(),
      encap_type_(type),
      destination_ips_(),
      persistent_(false) {
}

inline std::string const & 
nexthop_group_t::name() const {
   return name_;
}

inline nexthop_group_encap_t
nexthop_group_t::type() const {
   return encap_type_;
}

inline void
nexthop_group_t::ttl_is(uint8_t ttl) {
   ttl_ = ttl;
}

inline uint8_t
nexthop_group_t::ttl() const {
   return ttl_;
}

inline void
nexthop_group_t::source_ip_is(ip_addr_t const & src_ip) {
   source_ip_ = src_ip;
   if(!!source_ip_) {
      // If we're setting a source ip, clear any
      // source interface configuration
      source_intf_is(intf_id_t());
   }
}

inline ip_addr_t const & 
nexthop_group_t::source_ip() const {
   return source_ip_;
}

inline void
nexthop_group_t::source_intf_is(intf_id_t const & src_intf) {
   source_intf_ = src_intf;
   if(!!source_intf_) {
      // If we're setting a source interface, clear any
      // source ip configuration
      source_ip_is(ip_addr_t());
   }
}

inline intf_id_t const
nexthop_group_t::source_intf() const {
   return source_intf_;
}

inline std::map<uint16_t, ip_addr_t> const &
nexthop_group_t::destination_ips() const {
   return destination_ips_;
}

inline uint16_t
nexthop_group_t::size() const {
   // "size" really means "the index of the last non-zero entry in the
   // 'destinationIp' array of the
   // NexthopGroup::NexthopGroupConfigEntry in Ira/Routing.tac".
   //
   // We want the *index* of the last element in "destination_ips_",
   // not the "size" of the data structure, which tells you the number
   // of entries, to handle the case where "destination_ips_" is
   // sparse.
   if(destination_ips_.empty()) {
      return 0;
   }
   return destination_ips_.rbegin()->first + 1;
}

inline void
nexthop_group_t::persistent_is(bool persistent) {
   persistent_ = persistent;
}

inline bool
nexthop_group_t::persistent() const {
   return persistent_;
}

}

#endif // INLINE_NEXTHOP_GROUP_H
