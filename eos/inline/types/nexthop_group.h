// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_NEXTHOP_GROUP_H
#define EOS_INLINE_TYPES_NEXTHOP_GROUP_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const nexthop_group_encap_t & enum_val) {
   if (enum_val==NEXTHOP_GROUP_TYPE_NULL) {
      os << "NEXTHOP_GROUP_TYPE_NULL";
   } else if (enum_val==NEXTHOP_GROUP_IP_IN_IP) {
      os << "NEXTHOP_GROUP_IP_IN_IP";
   } else if (enum_val==NEXTHOP_GROUP_GRE) {
      os << "NEXTHOP_GROUP_GRE";
   } else if (enum_val==NEXTHOP_GROUP_MPLS) {
      os << "NEXTHOP_GROUP_MPLS";
   } else if (enum_val==NEXTHOP_GROUP_MPLS_OVER_GRE) {
      os << "NEXTHOP_GROUP_MPLS_OVER_GRE";
   } else if (enum_val==NEXTHOP_GROUP_IP) {
      os << "NEXTHOP_GROUP_IP";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const nexthop_group_gre_key_t & enum_val) {
   if (enum_val==NEXTHOP_GROUP_GRE_KEY_NULL) {
      os << "NEXTHOP_GROUP_GRE_KEY_NULL";
   } else if (enum_val==NEXTHOP_GROUP_GRE_KEY_INGRESS_INTF) {
      os << "NEXTHOP_GROUP_GRE_KEY_INGRESS_INTF";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline nexthop_group_mpls_action_t::nexthop_group_mpls_action_t() :
      action_type_(), label_stack_() {
}

inline nexthop_group_mpls_action_t::nexthop_group_mpls_action_t(
         mpls_action_t action_type) :
      action_type_(action_type), label_stack_() {
}

inline nexthop_group_mpls_action_t::nexthop_group_mpls_action_t(
         mpls_action_t action_type,
         std::forward_list<mpls_label_t> const & label_stack) :
      action_type_(action_type), label_stack_(label_stack) {
}

inline mpls_action_t
nexthop_group_mpls_action_t::action_type() const {
   return action_type_;
}

inline void
nexthop_group_mpls_action_t::action_type_is(mpls_action_t action_type) {
   action_type_ = action_type;
}

inline std::forward_list<mpls_label_t> const &
nexthop_group_mpls_action_t::label_stack() const {
   return label_stack_;
}

inline void
nexthop_group_mpls_action_t::label_stack_is(
         std::forward_list<mpls_label_t> const & label_stack) {
   label_stack_ = label_stack;
}

inline void
nexthop_group_mpls_action_t::label_stack_set(mpls_label_t const & label_stack) {
   label_stack_.push_front(label_stack);
}

inline void
nexthop_group_mpls_action_t::label_stack_del(mpls_label_t const & label_stack) {
   label_stack_.remove(label_stack);
}

inline bool
nexthop_group_mpls_action_t::operator==(nexthop_group_mpls_action_t const & other)
       const {
   return action_type_ == other.action_type_ &&
          label_stack_ == other.label_stack_;
}

inline bool
nexthop_group_mpls_action_t::operator!=(nexthop_group_mpls_action_t const & other)
       const {
   return !operator==(other);
}

inline bool
nexthop_group_mpls_action_t::operator<(nexthop_group_mpls_action_t const & other)
       const {
   if(action_type_ != other.action_type_) {
      return action_type_ < other.action_type_;
   } else if(label_stack_ != other.label_stack_) {
      return label_stack_ < other.label_stack_;
   }
   return false;
}

inline uint32_t
nexthop_group_mpls_action_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&action_type_,
              sizeof(mpls_action_t), ret);
   for (auto it=label_stack_.cbegin(); it!=label_stack_.cend(); ++it) {
      ret = hash_mix::mix((uint8_t *)&(*it),
            sizeof(mpls_label_t), ret);
   }
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
nexthop_group_mpls_action_t::to_string() const {
   std::ostringstream ss;
   ss << "nexthop_group_mpls_action_t(";
   ss << "action_type=" << action_type_;
   ss << ", label_stack=" <<"'";
   bool first_label_stack = true;
   for (auto it=label_stack_.cbegin(); it!=label_stack_.cend(); ++it) {
      if (first_label_stack) {
         ss << (*it);
         first_label_stack = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const nexthop_group_mpls_action_t& obj) {
   os << obj.to_string();
   return os;
}



inline nexthop_group_entry_counter_t::nexthop_group_entry_counter_t() :
      packets_(0), bytes_(0) {
}

inline nexthop_group_entry_counter_t::nexthop_group_entry_counter_t(
         uint64_t packets, uint64_t bytes) :
      packets_(packets), bytes_(bytes) {
}

inline uint64_t
nexthop_group_entry_counter_t::packets() const {
   return packets_;
}

inline uint64_t
nexthop_group_entry_counter_t::bytes() const {
   return bytes_;
}

inline bool
nexthop_group_entry_counter_t::operator==(
         nexthop_group_entry_counter_t const & other) const {
   return packets_ == other.packets_ &&
          bytes_ == other.bytes_;
}

inline bool
nexthop_group_entry_counter_t::operator!=(
         nexthop_group_entry_counter_t const & other) const {
   return !operator==(other);
}

inline bool
nexthop_group_entry_counter_t::operator<(
         nexthop_group_entry_counter_t const & other) const {
   if(packets_ != other.packets_) {
      return packets_ < other.packets_;
   } else if(bytes_ != other.bytes_) {
      return bytes_ < other.bytes_;
   }
   return false;
}

inline uint32_t
nexthop_group_entry_counter_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&packets_,
              sizeof(uint64_t), ret);
   ret = hash_mix::mix((uint8_t *)&bytes_,
              sizeof(uint64_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
nexthop_group_entry_counter_t::to_string() const {
   std::ostringstream ss;
   ss << "nexthop_group_entry_counter_t(";
   ss << "packets=" << packets_;
   ss << ", bytes=" << bytes_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const nexthop_group_entry_counter_t& obj) {
   os << obj.to_string();
   return os;
}



inline nexthop_group_entry_t::nexthop_group_entry_t() :
      mpls_action_(), nexthop_() {
}

inline nexthop_group_entry_t::nexthop_group_entry_t(ip_addr_t const & nexthop) :
      mpls_action_(), nexthop_(nexthop) {
}

inline nexthop_group_mpls_action_t
nexthop_group_entry_t::mpls_action() const {
   return mpls_action_;
}

inline void
nexthop_group_entry_t::mpls_action_is(
         nexthop_group_mpls_action_t const & mpls_action) {
   mpls_action_ = mpls_action;
}

inline ip_addr_t
nexthop_group_entry_t::nexthop() const {
   return nexthop_;
}

inline void
nexthop_group_entry_t::nexthop_is(ip_addr_t const & nexthop) {
   nexthop_ = nexthop;
}

inline bool
nexthop_group_entry_t::operator==(nexthop_group_entry_t const & other) const {
   return mpls_action_ == other.mpls_action_ &&
          nexthop_ == other.nexthop_;
}

inline bool
nexthop_group_entry_t::operator!=(nexthop_group_entry_t const & other) const {
   return !operator==(other);
}

inline bool
nexthop_group_entry_t::operator<(nexthop_group_entry_t const & other) const {
   if(mpls_action_ != other.mpls_action_) {
      return mpls_action_ < other.mpls_action_;
   } else if(nexthop_ != other.nexthop_) {
      return nexthop_ < other.nexthop_;
   }
   return false;
}

inline uint32_t
nexthop_group_entry_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&mpls_action_,
              sizeof(nexthop_group_mpls_action_t), ret);
   ret = hash_mix::mix((uint8_t *)&nexthop_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
nexthop_group_entry_t::to_string() const {
   std::ostringstream ss;
   ss << "nexthop_group_entry_t(";
   ss << "mpls_action=" << mpls_action_;
   ss << ", nexthop=" << nexthop_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const nexthop_group_entry_t& obj) {
   os << obj.to_string();
   return os;
}



inline nexthop_group_t::nexthop_group_t() :
      name_(), type_(), gre_key_type_(NEXTHOP_GROUP_GRE_KEY_NULL), ttl_(64),
      source_ip_(), source_intf_(), autosize_(false), nexthops_(),
      destination_ips_(), counters_unshared_() {
}

inline nexthop_group_t::nexthop_group_t(std::string name,
                                        nexthop_group_encap_t type) :
      name_(name), type_(type), gre_key_type_(NEXTHOP_GROUP_GRE_KEY_NULL),
      ttl_(64), source_ip_(), source_intf_(), autosize_(false), nexthops_(),
      destination_ips_(), counters_unshared_() {
}

inline nexthop_group_t::nexthop_group_t(std::string name,
                                        nexthop_group_encap_t type,
                                        nexthop_group_gre_key_t gre_key_type) :
      name_(name), type_(type), gre_key_type_(gre_key_type), ttl_(64),
      source_ip_(), source_intf_(), autosize_(false), nexthops_(),
      destination_ips_(), counters_unshared_() {
}

inline nexthop_group_t::nexthop_group_t(std::string name,
                                        ip_addr_t const & source_ip) :
      name_(name), type_(), gre_key_type_(), ttl_(), source_ip_(source_ip),
      source_intf_(), autosize_(), nexthops_(), destination_ips_(),
      counters_unshared_() {
}

inline nexthop_group_t::nexthop_group_t(
         std::string name, ip_addr_t const & source_ip,
         std::map<uint16_t, nexthop_group_entry_t> const & nexthops) :
      name_(name), type_(), gre_key_type_(), ttl_(), source_ip_(source_ip),
      source_intf_(), autosize_(), nexthops_(nexthops), destination_ips_(),
      counters_unshared_() {
}

inline std::string
nexthop_group_t::name() const {
   return name_;
}

inline nexthop_group_encap_t
nexthop_group_t::type() const {
   return type_;
}

inline nexthop_group_gre_key_t
nexthop_group_t::gre_key_type() const {
   return gre_key_type_;
}

inline uint16_t
nexthop_group_t::ttl() const {
   return ttl_;
}

inline void
nexthop_group_t::ttl_is(uint16_t ttl) {
   ttl_ = ttl;
}

inline ip_addr_t
nexthop_group_t::source_ip() const {
   return source_ip_;
}

inline void
nexthop_group_t::source_ip_is(ip_addr_t const & source_ip) {
   if (type_ == NEXTHOP_GROUP_MPLS && !!source_ip) {
      panic(invalid_argument_error(
                  "source_ip",
                  "MPLS nexthop group cannot specify a source IP"));
   } else if (!!source_ip) {
      // If we're setting a source ip, clear any
      // source interface configuration
      source_intf_is(intf_id_t());
   }
   source_ip_ = source_ip;
}

inline intf_id_t
nexthop_group_t::source_intf() const {
   return source_intf_;
}

inline void
nexthop_group_t::source_intf_is(intf_id_t source_intf) {
   if (!!source_intf) {
      // If we're setting a source interface, clear any
      // source ip configuration
      source_ip_is(ip_addr_t());
   }
   source_intf_ = source_intf;
}

inline bool
nexthop_group_t::autosize() const {
   return autosize_;
}

inline void
nexthop_group_t::autosize_is(bool autosize) {
   autosize_ = autosize;
}

inline uint16_t
nexthop_group_t::size() const {

   if (nexthops_.empty()) {
      return 0;
   }
   return nexthops_.rbegin()->first + 1;
}

inline std::map<uint16_t, nexthop_group_entry_t> const &
nexthop_group_t::nexthops() const {
   return nexthops_;
}

inline void
nexthop_group_t::nexthops_is(
         std::map<uint16_t, nexthop_group_entry_t> const & nexthops) {
   nexthops_ = nexthops;
}

inline void
nexthop_group_t::nexthop_set(uint16_t key, nexthop_group_entry_t const & value) {
   nexthops_[key] = value;
}

inline void
nexthop_group_t::nexthop_del(uint16_t key) {
   nexthops_.erase(key);
}

inline std::map<uint16_t, ip_addr_t> const &
nexthop_group_t::destination_ips() const {
   return destination_ips_;
}

inline void
nexthop_group_t::destination_ips_is(
         std::map<uint16_t, ip_addr_t> const & destination_ips) {
   destination_ips_ = destination_ips;
}

inline void
nexthop_group_t::destination_ip_set(uint16_t key, ip_addr_t const & value) {
   destination_ips_[key] = value;
}

inline void
nexthop_group_t::destination_ip_del(uint16_t key) {
   destination_ips_.erase(key);
}

inline bool
nexthop_group_t::counters_unshared() const {
   return counters_unshared_;
}

inline void
nexthop_group_t::counters_unshared_is(bool counters_unshared) {
   counters_unshared_ = counters_unshared;
}

inline bool
nexthop_group_t::operator==(nexthop_group_t const & other) const {
   return name_ == other.name_ &&
          type_ == other.type_ &&
          gre_key_type_ == other.gre_key_type_ &&
          ttl_ == other.ttl_ &&
          source_ip_ == other.source_ip_ &&
          source_intf_ == other.source_intf_ &&
          autosize_ == other.autosize_ &&
          nexthops_ == other.nexthops_ &&
          destination_ips_ == other.destination_ips_ &&
          counters_unshared_ == other.counters_unshared_;
}

inline bool
nexthop_group_t::operator!=(nexthop_group_t const & other) const {
   return !operator==(other);
}

inline bool
nexthop_group_t::operator<(nexthop_group_t const & other) const {
   if(name_ != other.name_) {
      return name_ < other.name_;
   } else if(type_ != other.type_) {
      return type_ < other.type_;
   } else if(gre_key_type_ != other.gre_key_type_) {
      return gre_key_type_ < other.gre_key_type_;
   } else if(ttl_ != other.ttl_) {
      return ttl_ < other.ttl_;
   } else if(source_ip_ != other.source_ip_) {
      return source_ip_ < other.source_ip_;
   } else if(source_intf_ != other.source_intf_) {
      return source_intf_ < other.source_intf_;
   } else if(autosize_ != other.autosize_) {
      return autosize_ < other.autosize_;
   } else if(nexthops_ != other.nexthops_) {
      return nexthops_ < other.nexthops_;
   } else if(destination_ips_ != other.destination_ips_) {
      return destination_ips_ < other.destination_ips_;
   } else if(counters_unshared_ != other.counters_unshared_) {
      return counters_unshared_ < other.counters_unshared_;
   }
   return false;
}

inline uint32_t
nexthop_group_t::hash() const {
   uint32_t ret = 0;
   ret ^= std::hash<std::string>()(name_);
   ret = hash_mix::mix((uint8_t *)&type_,
              sizeof(nexthop_group_encap_t), ret);
   ret = hash_mix::mix((uint8_t *)&gre_key_type_,
              sizeof(nexthop_group_gre_key_t), ret);
   ret = hash_mix::mix((uint8_t *)&ttl_,
              sizeof(uint16_t), ret);
   ret = hash_mix::mix((uint8_t *)&source_ip_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&source_intf_,
              sizeof(intf_id_t), ret);
   ret = hash_mix::mix((uint8_t *)&autosize_,
              sizeof(bool), ret);
   for (auto it=nexthops_.cbegin(); it!=nexthops_.cend(); ++it) {
      ret = hash_mix::mix((uint8_t *)&it->first,
                 sizeof(uint16_t), ret);
      ret = hash_mix::mix((uint8_t *)&it->second,
                 sizeof(nexthop_group_entry_t), ret);
   }
   for (auto it=destination_ips_.cbegin(); it!=destination_ips_.cend(); ++it) {
      ret = hash_mix::mix((uint8_t *)&it->first,
                 sizeof(uint16_t), ret);
      ret = hash_mix::mix((uint8_t *)&it->second,
                 sizeof(ip_addr_t), ret);
   }
   ret = hash_mix::mix((uint8_t *)&counters_unshared_,
              sizeof(bool), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
nexthop_group_t::to_string() const {
   std::ostringstream ss;
   ss << "nexthop_group_t(";
   ss << "name='" << name_ << "'";
   ss << ", type=" << type_;
   ss << ", gre_key_type=" << gre_key_type_;
   ss << ", ttl=" << ttl_;
   ss << ", source_ip=" << source_ip_;
   ss << ", source_intf=" << source_intf_;
   ss << ", autosize=" << autosize_;
   ss << ", nexthops=" <<"'";
   bool first_nexthops = true;
   for (auto it=nexthops_.cbegin(); it!=nexthops_.cend(); ++it) {
      if (first_nexthops) {
         ss << it->first << "=" << it->second;
         first_nexthops = false;
      } else {
         ss << "," << it->first << "=" << it->second;
      }
   }
   ss << "'";
   ss << ", destination_ips=" <<"'";
   bool first_destination_ips = true;
   for (auto it=destination_ips_.cbegin(); it!=destination_ips_.cend(); ++it) {
      if (first_destination_ips) {
         ss << it->first << "=" << it->second;
         first_destination_ips = false;
      } else {
         ss << "," << it->first << "=" << it->second;
      }
   }
   ss << "'";
   ss << ", counters_unshared=" << counters_unshared_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const nexthop_group_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_NEXTHOP_GROUP_H
