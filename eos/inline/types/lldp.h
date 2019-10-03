// Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_LLDP_H
#define EOS_INLINE_TYPES_LLDP_H

namespace eos {


inline uint32_t modbit(uint32_t value, uint32_t bit, bool enabled) {
   if (enabled) {
      return (value | bit);
   } else {
      return (value & ~bit);
   }
}
    


// TLV Type, default constructor.
inline lldp_tlv_type_t::lldp_tlv_type_t() :
      organization_(0), subtype_(0) {
}

// TLV Type, full constructor.
inline lldp_tlv_type_t::lldp_tlv_type_t(uint32_t organization, uint8_t subtype) :
      organization_(organization), subtype_(subtype) {
}

inline uint32_t
lldp_tlv_type_t::organization() const {
   return organization_;
}

inline void
lldp_tlv_type_t::organization_is(uint32_t organization) {
   organization_ = organization;
}

inline uint8_t
lldp_tlv_type_t::subtype() const {
   return subtype_;
}

inline void
lldp_tlv_type_t::subtype_is(uint8_t subtype) {
   subtype_ = subtype;
}

inline bool
lldp_tlv_type_t::operator==(lldp_tlv_type_t const & other) const {
   return organization_ == other.organization_ &&
          subtype_ == other.subtype_;
}

inline bool
lldp_tlv_type_t::operator!=(lldp_tlv_type_t const & other) const {
   return !operator==(other);
}

inline bool
lldp_tlv_type_t::operator<(lldp_tlv_type_t const & other) const {
   if(organization_ != other.organization_) {
      return organization_ < other.organization_;
   } else if(subtype_ != other.subtype_) {
      return subtype_ < other.subtype_;
   }
   return false;
}

inline uint32_t
lldp_tlv_type_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&organization_,
              sizeof(uint32_t), ret);
   ret = hash_mix::mix((uint8_t *)&subtype_,
              sizeof(uint8_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
lldp_tlv_type_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_tlv_type_t(";
   ss << "organization=" << organization_;
   ss << ", subtype=" << subtype_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const lldp_tlv_type_t& obj) {
   os << obj.to_string();
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const lldp_std_tlv_type_bit_t & enum_val) {
   if (enum_val==LLDP_TLV_NONE) {
      os << "LLDP_TLV_NONE";
   } else if (enum_val==LLDP_TLV_CHASSIS_ID) {
      os << "LLDP_TLV_CHASSIS_ID";
   } else if (enum_val==LLDP_TLV_INTF_ID) {
      os << "LLDP_TLV_INTF_ID";
   } else if (enum_val==LLDP_TLV_INTF_DESCR) {
      os << "LLDP_TLV_INTF_DESCR";
   } else if (enum_val==LLDP_TLV_SYSTEM_CAP) {
      os << "LLDP_TLV_SYSTEM_CAP";
   } else if (enum_val==LLDP_TLV_MANAGEMENT) {
      os << "LLDP_TLV_MANAGEMENT";
   } else if (enum_val==LLDP_TLV_VLAN) {
      os << "LLDP_TLV_VLAN";
   } else if (enum_val==LLDP_TLV_MANAGMENT_VLAN) {
      os << "LLDP_TLV_MANAGMENT_VLAN";
   } else if (enum_val==LLDP_TLV_MAX_FRAME_SIZE) {
      os << "LLDP_TLV_MAX_FRAME_SIZE";
   } else if (enum_val==LLDP_TLV_LACP) {
      os << "LLDP_TLV_LACP";
   } else if (enum_val==LLDP_TLV_PHY) {
      os << "LLDP_TLV_PHY";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline lldp_std_tlv_type_t::lldp_std_tlv_type_t() :
      bitset_(LLDP_TLV_NONE) {
}

inline void
lldp_std_tlv_type_t::chassis_id_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_CHASSIS_ID, enabled);
}

inline void
lldp_std_tlv_type_t::intf_id_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_INTF_ID, enabled);
}

inline void
lldp_std_tlv_type_t::intf_description_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_INTF_DESCR, enabled);
}

inline void
lldp_std_tlv_type_t::system_capabilities_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_SYSTEM_CAP, enabled);
}

inline void
lldp_std_tlv_type_t::management_address_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_MANAGEMENT, enabled);
}

inline void
lldp_std_tlv_type_t::default_vlan_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_VLAN, enabled);
}

inline void
lldp_std_tlv_type_t::management_vlan_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_MANAGMENT_VLAN, enabled);
}

inline void
lldp_std_tlv_type_t::max_frame_size_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_MAX_FRAME_SIZE, enabled);
}

inline void
lldp_std_tlv_type_t::lacp_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_LACP, enabled);
}

inline void
lldp_std_tlv_type_t::phy_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_PHY, enabled);
}

inline bool
lldp_std_tlv_type_t::chassis_id() const {
   return bitset_ & LLDP_TLV_CHASSIS_ID;
}

inline bool
lldp_std_tlv_type_t::intf_id() const {
   return bitset_ & LLDP_TLV_INTF_ID;
}

inline bool
lldp_std_tlv_type_t::intf_description() const {
   return bitset_ & LLDP_TLV_INTF_DESCR;
}

inline bool
lldp_std_tlv_type_t::system_capabilities() const {
   return bitset_ & LLDP_TLV_SYSTEM_CAP;
}

inline bool
lldp_std_tlv_type_t::management_address() const {
   return bitset_ & LLDP_TLV_MANAGEMENT;
}

inline bool
lldp_std_tlv_type_t::default_vlan() const {
   return bitset_ & LLDP_TLV_VLAN;
}

inline bool
lldp_std_tlv_type_t::management_vlan() const {
   return bitset_ & LLDP_TLV_MANAGMENT_VLAN;
}

inline bool
lldp_std_tlv_type_t::max_frame_size() const {
   return bitset_ & LLDP_TLV_MAX_FRAME_SIZE;
}

inline bool
lldp_std_tlv_type_t::lacp() const {
   return bitset_ & LLDP_TLV_LACP;
}

inline bool
lldp_std_tlv_type_t::phy() const {
   return bitset_ & LLDP_TLV_PHY;
}

inline uint32_t
lldp_std_tlv_type_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&bitset_,
              sizeof(lldp_std_tlv_type_bit_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
lldp_std_tlv_type_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_std_tlv_type_t(";
   ss << "bitset=" << bitset_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const lldp_std_tlv_type_t& obj) {
   os << obj.to_string();
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const lldp_syscap_bits_t & enum_val) {
   if (enum_val==LLDP_SYSCAP_OTHER) {
      os << "LLDP_SYSCAP_OTHER";
   } else if (enum_val==LLDP_SYSCAP_REPEATER) {
      os << "LLDP_SYSCAP_REPEATER";
   } else if (enum_val==LLDP_SYSCAP_BRIDGE) {
      os << "LLDP_SYSCAP_BRIDGE";
   } else if (enum_val==LLDP_SYSCAP_VLAN_AP) {
      os << "LLDP_SYSCAP_VLAN_AP";
   } else if (enum_val==LLDP_SYSCAP_ROUTER) {
      os << "LLDP_SYSCAP_ROUTER";
   } else if (enum_val==LLDP_SYSCAP_TELEPONE) {
      os << "LLDP_SYSCAP_TELEPONE";
   } else if (enum_val==LLDP_SYSCAP_DOCSIS) {
      os << "LLDP_SYSCAP_DOCSIS";
   } else if (enum_val==LLDP_SYSCAP_STATION) {
      os << "LLDP_SYSCAP_STATION";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline lldp_syscap_t::lldp_syscap_t() :
      bitset_(LLDP_SYSCAP_OTHER) {
}

// syscap, full constructor.
inline lldp_syscap_t::lldp_syscap_t(lldp_syscap_bits_t bitset) :
      bitset_(bitset) {
}

inline bool
lldp_syscap_t::other() const {
   return bitset_ & LLDP_SYSCAP_OTHER;
}

inline bool
lldp_syscap_t::repeater() const {
   return bitset_ & LLDP_SYSCAP_REPEATER;
}

inline bool
lldp_syscap_t::bridge() const {
   return bitset_ & LLDP_SYSCAP_BRIDGE;
}

inline bool
lldp_syscap_t::vlan_ap() const {
   return bitset_ & LLDP_SYSCAP_VLAN_AP;
}

inline bool
lldp_syscap_t::router() const {
   return bitset_ & LLDP_SYSCAP_ROUTER;
}

inline bool
lldp_syscap_t::telephone() const {
   return bitset_ & LLDP_SYSCAP_TELEPONE;
}

inline bool
lldp_syscap_t::docsis() const {
   return bitset_ & LLDP_SYSCAP_DOCSIS;
}

inline bool
lldp_syscap_t::station() const {
   return bitset_ & LLDP_SYSCAP_STATION;
}

inline uint32_t
lldp_syscap_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&bitset_,
              sizeof(lldp_syscap_bits_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
lldp_syscap_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_syscap_t(";
   ss << "bitset=" << bitset_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const lldp_syscap_t& obj) {
   os << obj.to_string();
   return os;
}



inline lldp_management_address_t::lldp_management_address_t() :
      address_family_(0), address_(), snmp_ifindex_(), oid_() {
}

// Managment Info constructor.
inline lldp_management_address_t::lldp_management_address_t(
         uint32_t address_family, std::string address, uint32_t snmp_ifindex,
         std::string oid) :
      address_family_(address_family), address_(address),
      snmp_ifindex_(snmp_ifindex), oid_(oid) {
}

inline uint32_t
lldp_management_address_t::address_family() const {
   return address_family_;
}

inline std::string
lldp_management_address_t::address() const {
   return address_;
}

inline uint32_t
lldp_management_address_t::snmp_ifindex() const {
   return snmp_ifindex_;
}

inline std::string
lldp_management_address_t::oid() const {
   return oid_;
}

inline bool
lldp_management_address_t::operator<(lldp_management_address_t const & other)
       const {
   if(address_family_ != other.address_family_) {
      return address_family_ < other.address_family_;
   } else if(address_ != other.address_) {
      return address_ < other.address_;
   } else if(snmp_ifindex_ != other.snmp_ifindex_) {
      return snmp_ifindex_ < other.snmp_ifindex_;
   } else if(oid_ != other.oid_) {
      return oid_ < other.oid_;
   }
   return false;
}

inline uint32_t
lldp_management_address_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&address_family_,
              sizeof(uint32_t), ret);
   ret ^= std::hash<std::string>()(address_);
   ret = hash_mix::mix((uint8_t *)&snmp_ifindex_,
              sizeof(uint32_t), ret);
   ret ^= std::hash<std::string>()(oid_);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
lldp_management_address_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_management_address_t(";
   ss << "address_family=" << address_family_;
   ss << ", address='" << address_ << "'";
   ss << ", snmp_ifindex=" << snmp_ifindex_;
   ss << ", oid='" << oid_ << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const lldp_management_address_t& obj) {
   os << obj.to_string();
   return os;
}



inline lldp_lacp_t::lldp_lacp_t() :
      capable_(), enabled_(), id_(), valid_(false) {
}

// LACP Info constructor.
inline lldp_lacp_t::lldp_lacp_t(bool capable, bool enabled, uint32_t id,
                                bool valid) :
      capable_(capable), enabled_(enabled), id_(id), valid_(valid) {
}

inline bool
lldp_lacp_t::capable() const {
   return capable_;
}

inline bool
lldp_lacp_t::enabled() const {
   return enabled_;
}

inline uint32_t
lldp_lacp_t::id() const {
   return id_;
}

inline bool
lldp_lacp_t::valid() const {
   return valid_;
}

inline bool
lldp_lacp_t::operator!() const {
   return !valid_;

}

inline uint32_t
lldp_lacp_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&capable_,
              sizeof(bool), ret);
   ret = hash_mix::mix((uint8_t *)&enabled_,
              sizeof(bool), ret);
   ret = hash_mix::mix((uint8_t *)&id_,
              sizeof(uint32_t), ret);
   ret = hash_mix::mix((uint8_t *)&valid_,
              sizeof(bool), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
lldp_lacp_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_lacp_t(";
   ss << "capable=" << capable_;
   ss << ", enabled=" << enabled_;
   ss << ", id=" << id_;
   ss << ", valid=" << valid_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const lldp_lacp_t& obj) {
   os << obj.to_string();
   return os;
}



inline lldp_phy_t::lldp_phy_t() :
      autonegSupported_(), autonegEnabled_(), autonegCapabilitiesBm_(),
      valid_(false) {
}

// PHY Info constructor.
inline lldp_phy_t::lldp_phy_t(bool autonegSupported, bool autonegEnabled,
                              uint16_t autonegCapabilitiesBm, bool valid) :
      autonegSupported_(autonegSupported), autonegEnabled_(autonegEnabled),
      autonegCapabilitiesBm_(autonegCapabilitiesBm), valid_(valid) {
}

inline bool
lldp_phy_t::autonegSupported() const {
   return autonegSupported_;
}

inline bool
lldp_phy_t::autonegEnabled() const {
   return autonegEnabled_;
}

inline uint16_t
lldp_phy_t::autonegCapabilitiesBm() const {
   return autonegCapabilitiesBm_;
}

inline bool
lldp_phy_t::valid() const {
   return valid_;
}

inline uint32_t
lldp_phy_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&autonegSupported_,
              sizeof(bool), ret);
   ret = hash_mix::mix((uint8_t *)&autonegEnabled_,
              sizeof(bool), ret);
   ret = hash_mix::mix((uint8_t *)&autonegCapabilitiesBm_,
              sizeof(uint16_t), ret);
   ret = hash_mix::mix((uint8_t *)&valid_,
              sizeof(bool), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
lldp_phy_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_phy_t(";
   ss << "autonegSupported=" << autonegSupported_;
   ss << ", autonegEnabled=" << autonegEnabled_;
   ss << ", autonegCapabilitiesBm=" << autonegCapabilitiesBm_;
   ss << ", valid=" << valid_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const lldp_phy_t& obj) {
   os << obj.to_string();
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const lldp_intf_enabled_t & enum_val) {
   if (enum_val==LLDP_INTF_STATUS_NULL) {
      os << "LLDP_INTF_STATUS_NULL";
   } else if (enum_val==LLDP_INTF_ENABLE_TX) {
      os << "LLDP_INTF_ENABLE_TX";
   } else if (enum_val==LLDP_INTF_ENABLE_RX) {
      os << "LLDP_INTF_ENABLE_RX";
   } else if (enum_val==LLDP_INTF_ENABLE_BIDIR) {
      os << "LLDP_INTF_ENABLE_BIDIR";
   } else if (enum_val==LLDP_INTF_DISABLE) {
      os << "LLDP_INTF_DISABLE";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const lldp_chassis_id_encoding_t & enum_val) {
   if (enum_val==LLDP_CHASSIS_RESERVED) {
      os << "LLDP_CHASSIS_RESERVED";
   } else if (enum_val==LLDP_CHASSIS_COMPONENT) {
      os << "LLDP_CHASSIS_COMPONENT";
   } else if (enum_val==LLDP_CHASSIS_INTF_ALIAS) {
      os << "LLDP_CHASSIS_INTF_ALIAS";
   } else if (enum_val==LLDP_CHASSIS_PORT_COMPONENT) {
      os << "LLDP_CHASSIS_PORT_COMPONENT";
   } else if (enum_val==LLDP_CHASSIS_MAC_ADDR) {
      os << "LLDP_CHASSIS_MAC_ADDR";
   } else if (enum_val==LLDP_CHASSIS_NET_ADDR) {
      os << "LLDP_CHASSIS_NET_ADDR";
   } else if (enum_val==LLDP_CHASSIS_INTF_NAME) {
      os << "LLDP_CHASSIS_INTF_NAME";
   } else if (enum_val==LLDP_CHASSIS_LOCAL) {
      os << "LLDP_CHASSIS_LOCAL";
   } else if (enum_val==LLDP_CHASSIS_NULL) {
      os << "LLDP_CHASSIS_NULL";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline lldp_chassis_id_t::lldp_chassis_id_t() :
      encoding_(LLDP_CHASSIS_NULL), value_() {
}

// chassis name, full constructor.
inline lldp_chassis_id_t::lldp_chassis_id_t(lldp_chassis_id_encoding_t encoding,
                                            std::string value) :
      encoding_(encoding), value_(value) {
}

inline lldp_chassis_id_encoding_t
lldp_chassis_id_t::encoding() const {
   return encoding_;
}

inline std::string
lldp_chassis_id_t::value() const {
   return value_;
}

inline std::string
lldp_chassis_id_t::repr() const {

   char buf[128];
   if (encoding_ == LLDP_CHASSIS_INTF_NAME) {
      return value_;
   }
   if (encoding_ == LLDP_CHASSIS_MAC_ADDR) {
      if (value_.length() == 6) {
         sprintf(buf, "MAC:");
         ether_ntoa_r((const ether_addr*)&value_[0], buf+4);
         return std::string(buf);
      } else {
         return std::string("invalidMac");
      }
   }
   if (encoding_ == LLDP_CHASSIS_NET_ADDR) {
      if (value_[0] == 1) {
        if (value_.length() == 5) {
            sprintf(buf, "IPV4:");
            inet_ntop(AF_INET, &value_[1], buf+5, 100);
            return std::string(buf);
        } else {
           return std::string("invalidIpV4");
        }
      }
      if (value_[0] == 2) {
        if (value_.length() == 17) {
            sprintf(buf, "IPV6:");
            inet_ntop(AF_INET6, &value_[1], buf+5, 100) ;
            return std::string(buf);
        } else {
           return std::string("invalidIpV6");
        }
      }
   }
   /* not a known encoding: just dump as hex */
   int l = sprintf(buf, "%d:", encoding_);
   /* well, unless it is all ascii */
   uint32_t i;
   for (i = 0; i < value_.length(); i++) {
      if (!isalnum(int(value_[i]))) break;
   }
   if (i == value_.length()) {
      snprintf(&buf[l], sizeof(buf)-l, "%s", value_.c_str());
      return std::string(buf);
   }
   for (i = 0; i < value_.length(); i++) {
      if (i) l += snprintf(&buf[l], sizeof(buf)-l, ".");
      l += snprintf(&buf[l], sizeof(buf)-l, "%02x", (uint8_t)value_[i]);
   }
   return std::string(buf);

}

inline bool
lldp_chassis_id_t::operator==(lldp_chassis_id_t const & other) const {
   return encoding_ == other.encoding_ &&
          value_ == other.value_;
}

inline bool
lldp_chassis_id_t::operator!=(lldp_chassis_id_t const & other) const {
   return !operator==(other);
}

inline bool
lldp_chassis_id_t::operator<(lldp_chassis_id_t const & other) const {
   if(encoding_ != other.encoding_) {
      return encoding_ < other.encoding_;
   } else if(value_ != other.value_) {
      return value_ < other.value_;
   }
   return false;
}

inline uint32_t
lldp_chassis_id_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&encoding_,
              sizeof(lldp_chassis_id_encoding_t), ret);
   ret ^= std::hash<std::string>()(value_);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
lldp_chassis_id_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_chassis_id_t(";
   ss << "encoding=" << encoding_;
   ss << ", value='" << value_ << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const lldp_chassis_id_t& obj) {
   os << obj.to_string();
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const lldp_intf_id_encoding_t & enum_val) {
   if (enum_val==LLDP_INTF_RESERVED) {
      os << "LLDP_INTF_RESERVED";
   } else if (enum_val==LLDP_INTF_ALIAS) {
      os << "LLDP_INTF_ALIAS";
   } else if (enum_val==LLDP_INTF_COMPONENT) {
      os << "LLDP_INTF_COMPONENT";
   } else if (enum_val==LLDP_INTF_MAC_ADDR) {
      os << "LLDP_INTF_MAC_ADDR";
   } else if (enum_val==LLDP_INTF_NET_ADDR) {
      os << "LLDP_INTF_NET_ADDR";
   } else if (enum_val==LLDP_INTF_NAME) {
      os << "LLDP_INTF_NAME";
   } else if (enum_val==LLDP_INTF_CIRCUIT) {
      os << "LLDP_INTF_CIRCUIT";
   } else if (enum_val==LLDP_INTF_LOCAL) {
      os << "LLDP_INTF_LOCAL";
   } else if (enum_val==LLDP_INTF_NULL) {
      os << "LLDP_INTF_NULL";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline lldp_intf_id_t::lldp_intf_id_t() :
      encoding_(LLDP_INTF_NULL), value_() {
}

// interface name, full constructor.
inline lldp_intf_id_t::lldp_intf_id_t(lldp_intf_id_encoding_t encoding,
                                      std::string value) :
      encoding_(encoding), value_(value) {
}

inline lldp_intf_id_encoding_t
lldp_intf_id_t::encoding() const {
   return encoding_;
}

inline std::string
lldp_intf_id_t::value() const {
   return value_;
}

inline std::string
lldp_intf_id_t::repr() const {

   char buf[128];
   if (encoding_ == LLDP_INTF_NAME) {
      return value_;
   }
   if (encoding_ == LLDP_INTF_MAC_ADDR) {
      if (value_.length() == 6) {
         sprintf(buf, "MAC:");
         ether_ntoa_r((const ether_addr*)&value_[0], buf+4);
         return std::string(buf);
      } else {
         return std::string("invalidMac");
      }
   }
   if (encoding_ == LLDP_INTF_NET_ADDR) {
      if (value_[0] == 1) {
        if (value_.length() == 5) {
            sprintf(buf, "IPV4:");
            inet_ntop(AF_INET, &value_[1], buf+5, 100);
            return std::string(buf);
        } else {
           return std::string("invalidIpV4");
        }
      }
      if (value_[0] == 2) {
        if (value_.length() == 17) {
            sprintf(buf, "IPV6:");
            inet_ntop(AF_INET6, &value_[1], buf+5, 100) ;
            return std::string(buf);
        } else {
           return std::string("invalidIpV6");
        }
      }
   }
   /* not a known encoding: just dump as hex */
   int l = sprintf(buf, "%d:", encoding_);
   /* well, unless it is all ascii */
   for (uint32_t i=0; i<value_.length(); i++) {
      if (!isalnum(int(value_[i]))) break;
      if (i+1 == value_.length()) {
         snprintf(&buf[l], sizeof(buf)-l, "%s", value_.c_str());
         return std::string(buf);
      }
   }
   for (uint32_t i=0; i<value_.length(); i++) {
      if (i) l += snprintf(&buf[l], sizeof(buf)-l, ".");
      l += snprintf(&buf[l], sizeof(buf)-l, "%02x", (uint8_t)value_[i]);
   }
   return std::string(buf);

}

inline bool
lldp_intf_id_t::operator==(lldp_intf_id_t const & other) const {
   return encoding_ == other.encoding_ &&
          value_ == other.value_;
}

inline bool
lldp_intf_id_t::operator!=(lldp_intf_id_t const & other) const {
   return !operator==(other);
}

inline bool
lldp_intf_id_t::operator<(lldp_intf_id_t const & other) const {
   if(encoding_ != other.encoding_) {
      return encoding_ < other.encoding_;
   } else if(value_ != other.value_) {
      return value_ < other.value_;
   }
   return false;
}

inline uint32_t
lldp_intf_id_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&encoding_,
              sizeof(lldp_intf_id_encoding_t), ret);
   ret ^= std::hash<std::string>()(value_);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
lldp_intf_id_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_intf_id_t(";
   ss << "encoding=" << encoding_;
   ss << ", value='" << value_ << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const lldp_intf_id_t& obj) {
   os << obj.to_string();
   return os;
}



// remote system, default constructor.
inline lldp_remote_system_t::lldp_remote_system_t() :
      chassis_(lldp_chassis_id_t()), port_(lldp_intf_id_t()) {
}

// remote system, full constructor.
inline lldp_remote_system_t::lldp_remote_system_t(lldp_chassis_id_t chassis,
                                                  lldp_intf_id_t port) :
      chassis_(chassis), port_(port) {
}

inline lldp_chassis_id_t
lldp_remote_system_t::chassis() const {
   return chassis_;
}

inline void
lldp_remote_system_t::chassis_is(lldp_chassis_id_t chassis) {
   chassis_ = chassis;
}

inline lldp_intf_id_t
lldp_remote_system_t::port() const {
   return port_;
}

inline void
lldp_remote_system_t::port_is(lldp_intf_id_t port) {
   port_ = port;
}

inline std::string
lldp_remote_system_t::repr() const {

   char buf[128];
   snprintf(buf, 128, "%s;%s", chassis_.repr().c_str(),
                               port_.repr().c_str());
   return std::string(buf);

}

inline bool
lldp_remote_system_t::operator==(lldp_remote_system_t const & other) const {
   return chassis_ == other.chassis_ &&
          port_ == other.port_;
}

inline bool
lldp_remote_system_t::operator!=(lldp_remote_system_t const & other) const {
   return !operator==(other);
}

inline bool
lldp_remote_system_t::operator<(lldp_remote_system_t const & other) const {
   if(chassis_ != other.chassis_) {
      return chassis_ < other.chassis_;
   } else if(port_ != other.port_) {
      return port_ < other.port_;
   }
   return false;
}

inline uint32_t
lldp_remote_system_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&chassis_,
              sizeof(lldp_chassis_id_t), ret);
   ret = hash_mix::mix((uint8_t *)&port_,
              sizeof(lldp_intf_id_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
lldp_remote_system_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_remote_system_t(";
   ss << "chassis=" << chassis_;
   ss << ", port=" << port_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const lldp_remote_system_t& obj) {
   os << obj.to_string();
   return os;
}



// remote system, default constructor.
inline lldp_neighbor_t::lldp_neighbor_t() :
      intf_(), remote_system_() {
}

// first remote system.
inline lldp_neighbor_t::lldp_neighbor_t(intf_id_t intf) :
      intf_(intf), remote_system_() {
}

// specific remote system.
inline lldp_neighbor_t::lldp_neighbor_t(intf_id_t intf,
                                        lldp_remote_system_t remote_system) :
      intf_(intf), remote_system_(remote_system) {
}

inline intf_id_t
lldp_neighbor_t::intf() const {
   return intf_;
}

inline void
lldp_neighbor_t::intf_is(intf_id_t intf) {
   intf_ = intf;
}

inline lldp_remote_system_t
lldp_neighbor_t::remote_system() const {
   return remote_system_;
}

inline void
lldp_neighbor_t::remote_system_is(lldp_remote_system_t remote_system) {
   remote_system_ = remote_system;
}

inline std::string
lldp_neighbor_t::repr() const {

   char buf[128];
   snprintf(buf, 128, "%s;%s;%s", intf_.to_string().c_str(),
           remote_system_.chassis().repr().c_str(),
           remote_system_.port().repr().c_str());
   return std::string(buf);

}

inline bool
lldp_neighbor_t::operator==(lldp_neighbor_t const & other) const {
   return intf_ == other.intf_ &&
          remote_system_ == other.remote_system_;
}

inline bool
lldp_neighbor_t::operator!=(lldp_neighbor_t const & other) const {
   return !operator==(other);
}

inline bool
lldp_neighbor_t::operator<(lldp_neighbor_t const & other) const {
   if(intf_ != other.intf_) {
      return intf_ < other.intf_;
   } else if(remote_system_ != other.remote_system_) {
      return remote_system_ < other.remote_system_;
   }
   return false;
}

inline uint32_t
lldp_neighbor_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&intf_,
              sizeof(intf_id_t), ret);
   ret = hash_mix::mix((uint8_t *)&remote_system_,
              sizeof(lldp_remote_system_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
lldp_neighbor_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_neighbor_t(";
   ss << "intf=" << intf_;
   ss << ", remote_system=" << remote_system_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const lldp_neighbor_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_LLDP_H
