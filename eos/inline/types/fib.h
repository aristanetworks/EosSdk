// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_FIB_H
#define EOS_INLINE_TYPES_FIB_H

namespace eos {

// Default constructor.
inline fib_route_key_t::fib_route_key_t() :
      prefix_() {
}

inline fib_route_key_t::fib_route_key_t(ip_prefix_t const & prefix) :
      prefix_(prefix) {
}

inline ip_prefix_t
fib_route_key_t::prefix() const {
   return prefix_;
}

inline void
fib_route_key_t::prefix_is(ip_prefix_t const & prefix) {
   prefix_ = prefix;
}

inline bool
fib_route_key_t::operator==(fib_route_key_t const & other) const {
   return prefix_ == other.prefix_;
}

inline bool
fib_route_key_t::operator!=(fib_route_key_t const & other) const {
   return !operator==(other);
}

inline std::string
fib_route_key_t::to_string() const {
   std::ostringstream ss;
   ss << "fib_route_key_t(";
   ss << "prefix=" << prefix_.to_string();
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const fib_route_key_t& obj) {
   os << obj.to_string();
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const fib_route_type_t & enum_val) {
   if (enum_val==ROUTE_TYPE_INVALID) {
      os << "ROUTE_TYPE_INVALID";
   } else if (enum_val==ROUTE_TYPE_RECEIVE) {
      os << "ROUTE_TYPE_RECEIVE";
   } else if (enum_val==ROUTE_TYPE_RECEIVE_BCAST) {
      os << "ROUTE_TYPE_RECEIVE_BCAST";
   } else if (enum_val==ROUTE_TYPE_ATTACHED) {
      os << "ROUTE_TYPE_ATTACHED";
   } else if (enum_val==ROUTE_TYPE_UNKNOWN) {
      os << "ROUTE_TYPE_UNKNOWN";
   } else if (enum_val==ROUTE_TYPE_STATIC_CONFIG) {
      os << "ROUTE_TYPE_STATIC_CONFIG";
   } else if (enum_val==ROUTE_TYPE_KERNEL) {
      os << "ROUTE_TYPE_KERNEL";
   } else if (enum_val==ROUTE_TYPE_RIP) {
      os << "ROUTE_TYPE_RIP";
   } else if (enum_val==ROUTE_TYPE_CONNECTED) {
      os << "ROUTE_TYPE_CONNECTED";
   } else if (enum_val==ROUTE_TYPE_REDIRECT) {
      os << "ROUTE_TYPE_REDIRECT";
   } else if (enum_val==ROUTE_TYPE_BGP_AGGREGATE) {
      os << "ROUTE_TYPE_BGP_AGGREGATE";
   } else if (enum_val==ROUTE_TYPE_OSPF_AGGREGATE) {
      os << "ROUTE_TYPE_OSPF_AGGREGATE";
   } else if (enum_val==ROUTE_TYPE_OSPF_INTRA_AREA) {
      os << "ROUTE_TYPE_OSPF_INTRA_AREA";
   } else if (enum_val==ROUTE_TYPE_OSPF_INTER_AREA) {
      os << "ROUTE_TYPE_OSPF_INTER_AREA";
   } else if (enum_val==ROUTE_TYPE_OSPF_EXTERNAL_TYPE1) {
      os << "ROUTE_TYPE_OSPF_EXTERNAL_TYPE1";
   } else if (enum_val==ROUTE_TYPE_OSPF_EXTERNAL_TYPE2) {
      os << "ROUTE_TYPE_OSPF_EXTERNAL_TYPE2";
   } else if (enum_val==ROUTE_TYPE_OSPF_NSSA_EXTERNAL_TYPE1) {
      os << "ROUTE_TYPE_OSPF_NSSA_EXTERNAL_TYPE1";
   } else if (enum_val==ROUTE_TYPE_OSPF_NSSA_EXTERNAL_TYPE2) {
      os << "ROUTE_TYPE_OSPF_NSSA_EXTERNAL_TYPE2";
   } else if (enum_val==ROUTE_TYPE_BGP) {
      os << "ROUTE_TYPE_BGP";
   } else if (enum_val==ROUTE_TYPE_IBGP) {
      os << "ROUTE_TYPE_IBGP";
   } else if (enum_val==ROUTE_TYPE_EBGP) {
      os << "ROUTE_TYPE_EBGP";
   } else if (enum_val==ROUTE_TYPE_ISIS) {
      os << "ROUTE_TYPE_ISIS";
   } else if (enum_val==ROUTE_TYPE_ISIS_LEVEL1) {
      os << "ROUTE_TYPE_ISIS_LEVEL1";
   } else if (enum_val==ROUTE_TYPE_ISIS_LEVEL2) {
      os << "ROUTE_TYPE_ISIS_LEVEL2";
   } else if (enum_val==ROUTE_TYPE_NEXTHOP_GROUP) {
      os << "ROUTE_TYPE_NEXTHOP_GROUP";
   } else {
      os << "Unknown value";
   }
   return os;
}



// Default constructor.
inline fib_route_t::fib_route_t() :
      route_key_(), preference_(1), metric_(0), route_type_(), fec_id_(0) {
}

inline fib_route_t::fib_route_t(fib_route_key_t const & route_key) :
      route_key_(route_key), preference_(1), metric_(0), route_type_(), fec_id_(0) {
}

inline fib_route_key_t
fib_route_t::route_key() const {
   return route_key_;
}

inline void
fib_route_t::route_key_is(fib_route_key_t const & route_key) {
   route_key_ = route_key;
}

inline ip_route_preference_t
fib_route_t::preference() const {
   return preference_;
}

inline void
fib_route_t::preference_is(ip_route_preference_t preference) {
   preference_ = preference;
}

inline ip_route_metric_t
fib_route_t::metric() const {
   return metric_;
}

inline void
fib_route_t::metric_is(ip_route_metric_t metric) {
   metric_ = metric;
}

inline fib_route_type_t
fib_route_t::route_type() const {
   return route_type_;
}

inline void
fib_route_t::route_type_is(fib_route_type_t route_type) {
   route_type_ = route_type;
}

inline uint64_t
fib_route_t::fec_id() const {
   return fec_id_;
}

inline void
fib_route_t::fec_id_is(uint64_t fec_id) {
   fec_id_ = fec_id;
}

inline bool
fib_route_t::operator==(fib_route_t const & other) const {
   return route_key_ == other.route_key_ &&
          preference_ == other.preference_ &&
          metric_ == other.metric_ &&
          route_type_ == other.route_type_ &&
          fec_id_ == other.fec_id_;
}

inline bool
fib_route_t::operator!=(fib_route_t const & other) const {
   return !operator==(other);
}

inline std::string
fib_route_t::to_string() const {
   std::ostringstream ss;
   ss << "fib_route_t(";
   ss << "route_key=" << route_key_;
   ss << ", preference=" << preference_;
   ss << ", metric=" << metric_;
   ss << ", route_type=" << route_type_;
   ss << ", fec_id=" << fec_id_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const fib_route_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
inline fib_fec_key_t::fib_fec_key_t() :
      fec_id_(0) {
}

inline fib_fec_key_t::fib_fec_key_t(uint64_t fec_id) :
      fec_id_(fec_id) {
}

inline uint64_t
fib_fec_key_t::fec_id() const {
   return fec_id_;
}

inline void
fib_fec_key_t::fec_id_is(uint64_t fec_id) {
   fec_id_ = fec_id;
}

inline bool
fib_fec_key_t::operator==(fib_fec_key_t const & other) const {
   return fec_id_ == other.fec_id_;
}

inline bool
fib_fec_key_t::operator!=(fib_fec_key_t const & other) const {
   return !operator==(other);
}

inline std::string
fib_fec_key_t::to_string() const {
   std::ostringstream ss;
   ss << "fib_fec_key_t(";
   ss << "fec_id=" << fec_id_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const fib_fec_key_t& obj) {
   os << obj.to_string();
   return os;
}



// Default constructor.
inline fib_via_t::fib_via_t() :
      hop_(), intf_() {
}

inline fib_via_t::fib_via_t(ip_addr_t const & hop, intf_id_t intf) :
      hop_(hop), intf_(intf) {
}

inline ip_addr_t
fib_via_t::hop() const {
   return hop_;
}

inline void
fib_via_t::hop_is(ip_addr_t const & hop) {
   hop_ = hop;
}

inline intf_id_t
fib_via_t::intf() const {
   return intf_;
}

inline void
fib_via_t::intf_is(intf_id_t intf) {
   intf_ = intf;
}

inline bool
fib_via_t::operator==(fib_via_t const & other) const {
   return hop_ == other.hop_ &&
          intf_ == other.intf_;
}

inline bool
fib_via_t::operator!=(fib_via_t const & other) const {
   return !operator==(other);
}

inline std::string
fib_via_t::to_string() const {
   std::ostringstream ss;
   ss << "fib_via_t(";
   ss << "hop=" << hop_.to_string();
   ss << ", intf=" << intf_.to_string();
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const fib_via_t& obj) {
   os << obj.to_string();
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const fib_fec_type_t & enum_val) {
   if (enum_val==FEC_TYPE_FORWARD) {
      os << "FEC_TYPE_FORWARD";
   } else if (enum_val==FEC_TYPE_DROP) {
      os << "FEC_TYPE_DROP";
   } else if (enum_val==FEC_TYPE_RECEIVE) {
      os << "FEC_TYPE_RECEIVE";
   } else if (enum_val==FEC_TYPE_ATTACHED) {
      os << "FEC_TYPE_ATTACHED";
   } else if (enum_val==FEC_TYPE_RECEIVE_BCAST) {
      os << "FEC_TYPE_RECEIVE_BCAST";
   } else if (enum_val==FEC_TYPE_NEXTHOP_GROUP) {
      os << "FEC_TYPE_NEXTHOP_GROUP";
   } else if (enum_val==FEC_TYPE_KERNEL) {
      os << "FEC_TYPE_KERNEL";
   } else if (enum_val==FEC_TYPE_UNKNOWN) {
      os << "FEC_TYPE_UNKNOWN";
   } else {
      os << "Unknown value";
   }
   return os;
}



// Default constructor.
inline fib_fec_t::fib_fec_t() :
      fec_key_(), fec_type_(), nexthop_group_name_(), via_() {
}

inline fib_fec_t::fib_fec_t(fib_fec_key_t fec_key) :
      fec_key_(fec_key), fec_type_(), nexthop_group_name_(), via_() {
}

inline fib_fec_key_t
fib_fec_t::fec_key() const {
   return fec_key_;
}

inline void
fib_fec_t::fec_key_is(fib_fec_key_t fec_key) {
   fec_key_ = fec_key;
}

inline fib_fec_type_t
fib_fec_t::fec_type() const {
   return fec_type_;
}

inline void
fib_fec_t::fec_type_is(fib_fec_type_t fec_type) {
   fec_type_ = fec_type;
}

inline std::string
fib_fec_t::nexthop_group_name() const {
   return nexthop_group_name_;
}

inline void
fib_fec_t::nexthop_group_name_is(std::string nexthop_group_name) {
   nexthop_group_name_ = nexthop_group_name;
}

inline std::forward_list<fib_via_t> const &
fib_fec_t::via() const {
   return via_;
}

inline void
fib_fec_t::via_is(std::forward_list<fib_via_t> const & via) {
   via_ = via;
}

inline void
fib_fec_t::via_set(fib_via_t const & via) {
   via_.push_front(via);
}

inline void
fib_fec_t::via_del(fib_via_t const & via) {
   via_.remove(via);
}

inline std::string
fib_fec_t::to_string() const {
   std::ostringstream ss;
   ss << "fib_fec_t(";
   ss << "fec_key=" << fec_key_;
   ss << ", fec_type=" << fec_type_;
   ss << ", nexthop_group_name='" << nexthop_group_name_ << "'";
   ss << ", via=" <<"'";
   bool first_via = true;
   for (auto it=via_.cbegin(); it!=via_.cend(); ++it) {
      if (first_via) {
         ss << (*it);
         first_via = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const fib_fec_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_FIB_H
