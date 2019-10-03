// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_DIRECTFLOW_H
#define EOS_INLINE_TYPES_DIRECTFLOW_H

namespace eos {

inline flow_match_field_set_t::flow_match_field_set_t() :
      match_bitset_() {
}

inline bool
flow_match_field_set_t::operator==(flow_match_field_set_t const & other) const {
   return match_bitset_ == other.match_bitset_;
}

inline bool
flow_match_field_set_t::operator!=(flow_match_field_set_t const & other) const {
   return !operator==(other);
}

inline bool
flow_match_field_set_t::operator<(flow_match_field_set_t const & other) const {
   if(match_bitset_ != other.match_bitset_) {
      return match_bitset_ < other.match_bitset_;
   }
   return false;
}

inline uint32_t
flow_match_field_set_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&match_bitset_,
              sizeof(uint32_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
flow_match_field_set_t::to_string() const {
   std::ostringstream ss;
   ss << "flow_match_field_set_t(";
   ss << "match_bitset=" << match_bitset_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const flow_match_field_set_t& obj) {
   os << obj.to_string();
   return os;
}



inline flow_match_t::flow_match_t() :
      match_field_set_(), input_intfs_(), eth_src_(), eth_src_mask_(), eth_dst_(),
      eth_dst_mask_(), eth_type_(), vlan_id_(), vlan_id_mask_(), cos_(), ip_src_(),
      ip_src_mask_(), ip_dst_(), ip_dst_mask_() {
}

inline flow_match_field_set_t
flow_match_t::match_field_set() const {
   return match_field_set_;
}

inline void
flow_match_t::match_field_set_is(flow_match_field_set_t match_field_set) {
   match_field_set_ = match_field_set;
}

inline std::set<intf_id_t> const &
flow_match_t::input_intfs() const {
   return input_intfs_;
}

inline void
flow_match_t::input_intfs_is(std::set<intf_id_t> const & input_intfs) {
   input_intfs_ = input_intfs;
}

inline void
flow_match_t::input_intf_set(intf_id_t const & value) {
   input_intfs_.insert(value);
}

inline void
flow_match_t::input_intf_del(intf_id_t const & value) {
   input_intfs_.erase(value);
}

inline eth_addr_t
flow_match_t::eth_src() const {
   return eth_src_;
}

inline void
flow_match_t::eth_src_is(eth_addr_t eth_src) {
   eth_src_ = eth_src;
}

inline void
flow_match_t::eth_src_is(eth_addr_t src, eth_addr_t mask) {
   eth_src_ = src;
   eth_src_mask_ = mask;
}

inline eth_addr_t
flow_match_t::eth_src_mask() const {
   return eth_src_mask_;
}

inline void
flow_match_t::eth_src_mask_is(eth_addr_t eth_src_mask) {
   eth_src_mask_ = eth_src_mask;
}

inline eth_addr_t
flow_match_t::eth_dst() const {
   return eth_dst_;
}

inline void
flow_match_t::eth_dst_is(eth_addr_t eth_dst) {
   eth_dst_ = eth_dst;
}

inline void
flow_match_t::eth_dst_is(eth_addr_t dst, eth_addr_t mask) {
   eth_dst_ = dst;
   eth_dst_mask_ = mask;
}

inline eth_addr_t
flow_match_t::eth_dst_mask() const {
   return eth_dst_mask_;
}

inline void
flow_match_t::eth_dst_mask_is(eth_addr_t eth_dst_mask) {
   eth_dst_mask_ = eth_dst_mask;
}

inline eth_type_t
flow_match_t::eth_type() const {
   return eth_type_;
}

inline void
flow_match_t::eth_type_is(eth_type_t eth_type) {
   eth_type_ = eth_type;
}

inline vlan_id_t
flow_match_t::vlan_id() const {
   return vlan_id_;
}

inline void
flow_match_t::vlan_id_is(vlan_id_t vlan_id) {
   vlan_id_ = vlan_id;
}

inline void
flow_match_t::vlan_id_is(vlan_id_t vlan_id, uint16_t mask) {
   vlan_id_ = vlan_id;
   vlan_id_mask_ = mask;
}

inline vlan_id_t
flow_match_t::vlan_id_mask() const {
   return vlan_id_mask_;
}

inline void
flow_match_t::vlan_id_mask_is(vlan_id_t vlan_id_mask) {
   vlan_id_mask_ = vlan_id_mask;
}

inline cos_t
flow_match_t::cos() const {
   return cos_;
}

inline void
flow_match_t::cos_is(cos_t cos) {
   cos_ = cos;
}

inline ip_addr_t
flow_match_t::ip_src() const {
   return ip_src_;
}

inline void
flow_match_t::ip_src_is(ip_addr_t const & ip_src) {
   ip_src_ = ip_src;
}

inline void
flow_match_t::ip_src_is(ip_addr_t const & src, ip_addr_t const & mask) {
   ip_src_ = src;
   ip_src_mask_ = mask;
}

inline ip_addr_t
flow_match_t::ip_src_mask() const {
   return ip_src_mask_;
}

inline void
flow_match_t::ip_src_mask_is(ip_addr_t const & ip_src_mask) {
   ip_src_mask_ = ip_src_mask;
}

inline ip_addr_t
flow_match_t::ip_dst() const {
   return ip_dst_;
}

inline void
flow_match_t::ip_dst_is(ip_addr_t const & ip_dst) {
   ip_dst_ = ip_dst;
}

inline void
flow_match_t::ip_dst_is(ip_addr_t const & dst, ip_addr_t const & mask) {
   ip_dst_ = dst;
   ip_dst_mask_ = mask;
}

inline ip_addr_t
flow_match_t::ip_dst_mask() const {
   return ip_dst_mask_;
}

inline void
flow_match_t::ip_dst_mask_is(ip_addr_t const & ip_dst_mask) {
   ip_dst_mask_ = ip_dst_mask;
}

inline bool
flow_match_t::operator==(flow_match_t const & other) const {
   return match_field_set_ == other.match_field_set_ &&
          input_intfs_ == other.input_intfs_ &&
          eth_src_ == other.eth_src_ &&
          eth_src_mask_ == other.eth_src_mask_ &&
          eth_dst_ == other.eth_dst_ &&
          eth_dst_mask_ == other.eth_dst_mask_ &&
          eth_type_ == other.eth_type_ &&
          vlan_id_ == other.vlan_id_ &&
          vlan_id_mask_ == other.vlan_id_mask_ &&
          cos_ == other.cos_ &&
          ip_src_ == other.ip_src_ &&
          ip_src_mask_ == other.ip_src_mask_ &&
          ip_dst_ == other.ip_dst_ &&
          ip_dst_mask_ == other.ip_dst_mask_;
}

inline bool
flow_match_t::operator!=(flow_match_t const & other) const {
   return !operator==(other);
}

inline bool
flow_match_t::operator<(flow_match_t const & other) const {
   if(match_field_set_ != other.match_field_set_) {
      return match_field_set_ < other.match_field_set_;
   } else if(input_intfs_ != other.input_intfs_) {
      return input_intfs_ < other.input_intfs_;
   } else if(eth_src_ != other.eth_src_) {
      return eth_src_ < other.eth_src_;
   } else if(eth_src_mask_ != other.eth_src_mask_) {
      return eth_src_mask_ < other.eth_src_mask_;
   } else if(eth_dst_ != other.eth_dst_) {
      return eth_dst_ < other.eth_dst_;
   } else if(eth_dst_mask_ != other.eth_dst_mask_) {
      return eth_dst_mask_ < other.eth_dst_mask_;
   } else if(eth_type_ != other.eth_type_) {
      return eth_type_ < other.eth_type_;
   } else if(vlan_id_ != other.vlan_id_) {
      return vlan_id_ < other.vlan_id_;
   } else if(vlan_id_mask_ != other.vlan_id_mask_) {
      return vlan_id_mask_ < other.vlan_id_mask_;
   } else if(cos_ != other.cos_) {
      return cos_ < other.cos_;
   } else if(ip_src_ != other.ip_src_) {
      return ip_src_ < other.ip_src_;
   } else if(ip_src_mask_ != other.ip_src_mask_) {
      return ip_src_mask_ < other.ip_src_mask_;
   } else if(ip_dst_ != other.ip_dst_) {
      return ip_dst_ < other.ip_dst_;
   } else if(ip_dst_mask_ != other.ip_dst_mask_) {
      return ip_dst_mask_ < other.ip_dst_mask_;
   }
   return false;
}

inline uint32_t
flow_match_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&match_field_set_,
              sizeof(flow_match_field_set_t), ret);
   for (auto it=input_intfs_.cbegin(); it!=input_intfs_.cend(); ++it) {
      ret = hash_mix::mix((uint8_t *)&(*it),
            sizeof(intf_id_t), ret);
   }
   ret = hash_mix::mix((uint8_t *)&eth_src_,
              sizeof(eth_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&eth_src_mask_,
              sizeof(eth_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&eth_dst_,
              sizeof(eth_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&eth_dst_mask_,
              sizeof(eth_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&eth_type_,
              sizeof(eth_type_t), ret);
   ret = hash_mix::mix((uint8_t *)&vlan_id_,
              sizeof(vlan_id_t), ret);
   ret = hash_mix::mix((uint8_t *)&vlan_id_mask_,
              sizeof(vlan_id_t), ret);
   ret = hash_mix::mix((uint8_t *)&cos_,
              sizeof(cos_t), ret);
   ret = hash_mix::mix((uint8_t *)&ip_src_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&ip_src_mask_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&ip_dst_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&ip_dst_mask_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
flow_match_t::to_string() const {
   std::ostringstream ss;
   ss << "flow_match_t(";
   ss << "match_field_set=" << match_field_set_;
   ss << ", input_intfs=" <<"'";
   bool first_input_intfs = true;
   for (auto it=input_intfs_.cbegin(); it!=input_intfs_.cend(); ++it) {
      if (first_input_intfs) {
         ss << (*it);
         first_input_intfs = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", eth_src=" << eth_src_;
   ss << ", eth_src_mask=" << eth_src_mask_;
   ss << ", eth_dst=" << eth_dst_;
   ss << ", eth_dst_mask=" << eth_dst_mask_;
   ss << ", eth_type=" << eth_type_;
   ss << ", vlan_id=" << vlan_id_;
   ss << ", vlan_id_mask=" << vlan_id_mask_;
   ss << ", cos=" << cos_;
   ss << ", ip_src=" << ip_src_;
   ss << ", ip_src_mask=" << ip_src_mask_;
   ss << ", ip_dst=" << ip_dst_;
   ss << ", ip_dst_mask=" << ip_dst_mask_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const flow_match_t& obj) {
   os << obj.to_string();
   return os;
}



inline flow_action_set_t::flow_action_set_t() :
      action_bitset_() {
}

inline bool
flow_action_set_t::operator==(flow_action_set_t const & other) const {
   return action_bitset_ == other.action_bitset_;
}

inline bool
flow_action_set_t::operator!=(flow_action_set_t const & other) const {
   return !operator==(other);
}

inline uint32_t
flow_action_set_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&action_bitset_,
              sizeof(uint32_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
flow_action_set_t::to_string() const {
   std::ostringstream ss;
   ss << "flow_action_set_t(";
   ss << "action_bitset=" << action_bitset_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const flow_action_set_t& obj) {
   os << obj.to_string();
   return os;
}



inline flow_action_t::flow_action_t() :
      action_set_(), output_intfs_(), vlan_id_(), cos_(), eth_src_(), eth_dst_(),
      ip_src_(), ip_dst_() {
}

inline flow_action_set_t
flow_action_t::action_set() const {
   return action_set_;
}

inline void
flow_action_t::action_set_is(flow_action_set_t action_set) {
   action_set_ = action_set;
}

inline std::set<intf_id_t> const &
flow_action_t::output_intfs() const {
   return output_intfs_;
}

inline void
flow_action_t::output_intfs_is(std::set<intf_id_t> const & output_intfs) {
   output_intfs_ = output_intfs;
}

inline void
flow_action_t::output_intf_set(intf_id_t const & value) {
   output_intfs_.insert(value);
}

inline void
flow_action_t::output_intf_del(intf_id_t const & value) {
   output_intfs_.erase(value);
}

inline vlan_id_t
flow_action_t::vlan_id() const {
   return vlan_id_;
}

inline void
flow_action_t::vlan_id_is(vlan_id_t vlan_id) {
   if (vlan_id == 0 || vlan_id == 4095) {
     panic(
        invalid_argument_error(
           "vlan_id",
           "vlan_id cannot be 0 or 4095."));
   }
   vlan_id_ = vlan_id;
}

inline cos_t
flow_action_t::cos() const {
   return cos_;
}

inline void
flow_action_t::cos_is(cos_t cos) {
   cos_ = cos;
}

inline eth_addr_t
flow_action_t::eth_src() const {
   return eth_src_;
}

inline void
flow_action_t::eth_src_is(eth_addr_t eth_src) {
   eth_src_ = eth_src;
}

inline eth_addr_t
flow_action_t::eth_dst() const {
   return eth_dst_;
}

inline void
flow_action_t::eth_dst_is(eth_addr_t eth_dst) {
   eth_dst_ = eth_dst;
}

inline ip_addr_t
flow_action_t::ip_src() const {
   return ip_src_;
}

inline void
flow_action_t::ip_src_is(ip_addr_t const & ip_src) {
   ip_src_ = ip_src;
}

inline ip_addr_t
flow_action_t::ip_dst() const {
   return ip_dst_;
}

inline void
flow_action_t::ip_dst_is(ip_addr_t const & ip_dst) {
   ip_dst_ = ip_dst;
}

inline bool
flow_action_t::operator==(flow_action_t const & other) const {
   return action_set_ == other.action_set_ &&
          output_intfs_ == other.output_intfs_ &&
          vlan_id_ == other.vlan_id_ &&
          cos_ == other.cos_ &&
          eth_src_ == other.eth_src_ &&
          eth_dst_ == other.eth_dst_ &&
          ip_src_ == other.ip_src_ &&
          ip_dst_ == other.ip_dst_;
}

inline bool
flow_action_t::operator!=(flow_action_t const & other) const {
   return !operator==(other);
}

inline uint32_t
flow_action_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&action_set_,
              sizeof(flow_action_set_t), ret);
   for (auto it=output_intfs_.cbegin(); it!=output_intfs_.cend(); ++it) {
      ret = hash_mix::mix((uint8_t *)&(*it),
            sizeof(intf_id_t), ret);
   }
   ret = hash_mix::mix((uint8_t *)&vlan_id_,
              sizeof(vlan_id_t), ret);
   ret = hash_mix::mix((uint8_t *)&cos_,
              sizeof(cos_t), ret);
   ret = hash_mix::mix((uint8_t *)&eth_src_,
              sizeof(eth_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&eth_dst_,
              sizeof(eth_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&ip_src_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::mix((uint8_t *)&ip_dst_,
              sizeof(ip_addr_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
flow_action_t::to_string() const {
   std::ostringstream ss;
   ss << "flow_action_t(";
   ss << "action_set=" << action_set_;
   ss << ", output_intfs=" <<"'";
   bool first_output_intfs = true;
   for (auto it=output_intfs_.cbegin(); it!=output_intfs_.cend(); ++it) {
      if (first_output_intfs) {
         ss << (*it);
         first_output_intfs = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", vlan_id=" << vlan_id_;
   ss << ", cos=" << cos_;
   ss << ", eth_src=" << eth_src_;
   ss << ", eth_dst=" << eth_dst_;
   ss << ", ip_src=" << ip_src_;
   ss << ", ip_dst=" << ip_dst_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const flow_action_t& obj) {
   os << obj.to_string();
   return os;
}



inline flow_entry_t::flow_entry_t() :
      name_(), match_(), action_(), priority_() {
}

inline flow_entry_t::flow_entry_t(std::string const & name, flow_match_t match,
                                  flow_action_t action, flow_priority_t priority) :
      name_(name), match_(match), action_(action), priority_(priority) {
}

inline std::string
flow_entry_t::name() const {
   return name_;
}

inline flow_match_t
flow_entry_t::match() const {
   return match_;
}

inline flow_action_t
flow_entry_t::action() const {
   return action_;
}

inline flow_priority_t
flow_entry_t::priority() const {
   return priority_;
}

inline bool
flow_entry_t::operator==(flow_entry_t const & other) const {
   return name_ == other.name_ &&
          match_ == other.match_ &&
          action_ == other.action_ &&
          priority_ == other.priority_;
}

inline bool
flow_entry_t::operator!=(flow_entry_t const & other) const {
   return !operator==(other);
}

inline uint32_t
flow_entry_t::hash() const {
   uint32_t ret = 0;
   ret ^= std::hash<std::string>()(name_);
   ret = hash_mix::mix((uint8_t *)&match_,
              sizeof(flow_match_t), ret);
   ret = hash_mix::mix((uint8_t *)&action_,
              sizeof(flow_action_t), ret);
   ret = hash_mix::mix((uint8_t *)&priority_,
              sizeof(flow_priority_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
flow_entry_t::to_string() const {
   std::ostringstream ss;
   ss << "flow_entry_t(";
   ss << "name='" << name_ << "'";
   ss << ", match=" << match_;
   ss << ", action=" << action_;
   ss << ", priority=" << priority_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const flow_entry_t& obj) {
   os << obj.to_string();
   return os;
}



inline flow_counters_t::flow_counters_t() :
      bytes_(0), packets_(0) {
}

inline uint64_t
flow_counters_t::bytes() const {
   return bytes_;
}

inline uint64_t
flow_counters_t::packets() const {
   return packets_;
}

inline bool
flow_counters_t::operator==(flow_counters_t const & other) const {
   return bytes_ == other.bytes_ &&
          packets_ == other.packets_;
}

inline bool
flow_counters_t::operator!=(flow_counters_t const & other) const {
   return !operator==(other);
}

inline uint32_t
flow_counters_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&bytes_,
              sizeof(uint64_t), ret);
   ret = hash_mix::mix((uint8_t *)&packets_,
              sizeof(uint64_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
flow_counters_t::to_string() const {
   std::ostringstream ss;
   ss << "flow_counters_t(";
   ss << "bytes=" << bytes_;
   ss << ", packets=" << packets_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const flow_counters_t& obj) {
   os << obj.to_string();
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const flow_status_t & enum_val) {
   if (enum_val==FLOW_STATUS_UNKNOWN) {
      os << "FLOW_STATUS_UNKNOWN";
   } else if (enum_val==FLOW_CREATED) {
      os << "FLOW_CREATED";
   } else if (enum_val==FLOW_DELETED) {
      os << "FLOW_DELETED";
   } else if (enum_val==FLOW_REJECTED) {
      os << "FLOW_REJECTED";
   } else if (enum_val==FLOW_PENDING) {
      os << "FLOW_PENDING";
   } else if (enum_val==FLOW_HW_TABLE_PENDING) {
      os << "FLOW_HW_TABLE_PENDING";
   } else if (enum_val==FLOW_REQUEST_ACCEPTED) {
      os << "FLOW_REQUEST_ACCEPTED";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const flow_rejected_reason_t & enum_val) {
   if (enum_val==FLOW_REJECTED_BAD_MATCH) {
      os << "FLOW_REJECTED_BAD_MATCH";
   } else if (enum_val==FLOW_REJECTED_BAD_ACTION) {
      os << "FLOW_REJECTED_BAD_ACTION";
   } else if (enum_val==FLOW_REJECTED_HW_TABLE_FULL) {
      os << "FLOW_REJECTED_HW_TABLE_FULL";
   } else if (enum_val==FLOW_REJECTED_OTHER) {
      os << "FLOW_REJECTED_OTHER";
   } else if (enum_val==FLOW_REJECTED_ACTIONS_UNSUPPORTED) {
      os << "FLOW_REJECTED_ACTIONS_UNSUPPORTED";
   } else if (enum_val==FLOW_REJECTED_TIMEOUT_NOT_SUPPORTED) {
      os << "FLOW_REJECTED_TIMEOUT_NOT_SUPPORTED";
   } else {
      os << "Unknown value";
   }
   return os;
}


}

#endif // EOS_INLINE_TYPES_DIRECTFLOW_H
