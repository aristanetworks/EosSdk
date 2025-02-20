// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_LLDP_IMPL_H
#define EOS_INLINE_TYPES_LLDP_IMPL_H

namespace eos {


EOS_SDK_PRIVATE uint32_t modbit(uint32_t value, uint32_t bit, bool enabled) {
   if (enabled) {
      return (value | bit);
   } else {
      return (value & ~bit);
   }
}
    


// TLV Type, default constructor.
lldp_tlv_type_impl_t::lldp_tlv_type_impl_t() :
      organization_(0), subtype_(0) {
}

// TLV Type, full constructor.
lldp_tlv_type_impl_t::lldp_tlv_type_impl_t(uint32_t organization,
                                                  uint8_t subtype) :
      organization_(organization), subtype_(subtype) {
}

uint32_t
lldp_tlv_type_impl_t::organization() const {
   return organization_;
}

void
lldp_tlv_type_impl_t::organization_is(uint32_t organization) {
   organization_ = organization;
}

uint8_t
lldp_tlv_type_impl_t::subtype() const {
   return subtype_;
}

void
lldp_tlv_type_impl_t::subtype_is(uint8_t subtype) {
   subtype_ = subtype;
}

bool
lldp_tlv_type_impl_t::operator==(lldp_tlv_type_impl_t const & other) const {
   return organization_ == other.organization_ &&
          subtype_ == other.subtype_;
}

bool
lldp_tlv_type_impl_t::operator!=(lldp_tlv_type_impl_t const & other) const {
   return !operator==(other);
}

bool
lldp_tlv_type_impl_t::operator<(lldp_tlv_type_impl_t const & other) const {
   if(organization_ != other.organization_) {
      return organization_ < other.organization_;
   } else if(subtype_ != other.subtype_) {
      return subtype_ < other.subtype_;
   }
   return false;
}

uint32_t
lldp_tlv_type_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
lldp_tlv_type_impl_t::mix_me(hash_mix & h) const {
   h.mix(organization_); // uint32_t
   h.mix(subtype_); // uint8_t
}

std::string
lldp_tlv_type_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_tlv_type_t(";
   ss << "organization=" << organization_;
   ss << ", subtype=" << subtype_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const lldp_tlv_type_impl_t& obj) {
   os << obj.to_string();
   return os;
}





lldp_std_tlv_type_impl_t::lldp_std_tlv_type_impl_t() :
      bitset_(LLDP_TLV_NONE) {
}

void
lldp_std_tlv_type_impl_t::chassis_id_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_CHASSIS_ID, enabled);
}

void
lldp_std_tlv_type_impl_t::intf_id_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_INTF_ID, enabled);
}

void
lldp_std_tlv_type_impl_t::intf_description_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_INTF_DESCR, enabled);
}

void
lldp_std_tlv_type_impl_t::system_capabilities_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_SYSTEM_CAP, enabled);
}

void
lldp_std_tlv_type_impl_t::management_address_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_MANAGEMENT, enabled);
}

void
lldp_std_tlv_type_impl_t::default_vlan_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_VLAN, enabled);
}

void
lldp_std_tlv_type_impl_t::management_vlan_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_MANAGMENT_VLAN, enabled);
}

void
lldp_std_tlv_type_impl_t::max_frame_size_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_MAX_FRAME_SIZE, enabled);
}

void
lldp_std_tlv_type_impl_t::lacp_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_LACP, enabled);
}

void
lldp_std_tlv_type_impl_t::phy_is(bool enabled) {
   modbit(bitset_, LLDP_TLV_PHY, enabled);
}

bool
lldp_std_tlv_type_impl_t::chassis_id() const {
   return bitset_ & LLDP_TLV_CHASSIS_ID;
}

bool
lldp_std_tlv_type_impl_t::intf_id() const {
   return bitset_ & LLDP_TLV_INTF_ID;
}

bool
lldp_std_tlv_type_impl_t::intf_description() const {
   return bitset_ & LLDP_TLV_INTF_DESCR;
}

bool
lldp_std_tlv_type_impl_t::system_capabilities() const {
   return bitset_ & LLDP_TLV_SYSTEM_CAP;
}

bool
lldp_std_tlv_type_impl_t::management_address() const {
   return bitset_ & LLDP_TLV_MANAGEMENT;
}

bool
lldp_std_tlv_type_impl_t::default_vlan() const {
   return bitset_ & LLDP_TLV_VLAN;
}

bool
lldp_std_tlv_type_impl_t::management_vlan() const {
   return bitset_ & LLDP_TLV_MANAGMENT_VLAN;
}

bool
lldp_std_tlv_type_impl_t::max_frame_size() const {
   return bitset_ & LLDP_TLV_MAX_FRAME_SIZE;
}

bool
lldp_std_tlv_type_impl_t::lacp() const {
   return bitset_ & LLDP_TLV_LACP;
}

bool
lldp_std_tlv_type_impl_t::phy() const {
   return bitset_ & LLDP_TLV_PHY;
}

uint32_t
lldp_std_tlv_type_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
lldp_std_tlv_type_impl_t::mix_me(hash_mix & h) const {
   h.mix(bitset_); // lldp_std_tlv_type_bit_t
}

std::string
lldp_std_tlv_type_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_std_tlv_type_t(";
   ss << "bitset=" << bitset_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const lldp_std_tlv_type_impl_t& obj) {
   os << obj.to_string();
   return os;
}





lldp_syscap_impl_t::lldp_syscap_impl_t() :
      bitset_(LLDP_SYSCAP_OTHER) {
}

// syscap, full constructor.
lldp_syscap_impl_t::lldp_syscap_impl_t(lldp_syscap_bits_t bitset) :
      bitset_(bitset) {
}

bool
lldp_syscap_impl_t::other() const {
   return bitset_ & LLDP_SYSCAP_OTHER;
}

bool
lldp_syscap_impl_t::repeater() const {
   return bitset_ & LLDP_SYSCAP_REPEATER;
}

bool
lldp_syscap_impl_t::bridge() const {
   return bitset_ & LLDP_SYSCAP_BRIDGE;
}

bool
lldp_syscap_impl_t::vlan_ap() const {
   return bitset_ & LLDP_SYSCAP_VLAN_AP;
}

bool
lldp_syscap_impl_t::router() const {
   return bitset_ & LLDP_SYSCAP_ROUTER;
}

bool
lldp_syscap_impl_t::telephone() const {
   return bitset_ & LLDP_SYSCAP_TELEPONE;
}

bool
lldp_syscap_impl_t::docsis() const {
   return bitset_ & LLDP_SYSCAP_DOCSIS;
}

bool
lldp_syscap_impl_t::station() const {
   return bitset_ & LLDP_SYSCAP_STATION;
}

uint32_t
lldp_syscap_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
lldp_syscap_impl_t::mix_me(hash_mix & h) const {
   h.mix(bitset_); // lldp_syscap_bits_t
}

std::string
lldp_syscap_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_syscap_t(";
   ss << "bitset=" << bitset_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const lldp_syscap_impl_t& obj) {
   os << obj.to_string();
   return os;
}



lldp_management_address_impl_t::lldp_management_address_impl_t() :
      address_family_(0), address_(), snmp_ifindex_(), oid_() {
}

// Managment Info constructor.
lldp_management_address_impl_t::lldp_management_address_impl_t(
         uint32_t address_family, std::string address, uint32_t snmp_ifindex,
         std::string oid) :
      address_family_(address_family), address_(address),
      snmp_ifindex_(snmp_ifindex), oid_(oid) {
}

uint32_t
lldp_management_address_impl_t::address_family() const {
   return address_family_;
}

std::string
lldp_management_address_impl_t::address() const {
   return address_;
}

uint32_t
lldp_management_address_impl_t::snmp_ifindex() const {
   return snmp_ifindex_;
}

std::string
lldp_management_address_impl_t::oid() const {
   return oid_;
}

bool
lldp_management_address_impl_t::operator<(
         lldp_management_address_impl_t const & other) const {
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

uint32_t
lldp_management_address_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
lldp_management_address_impl_t::mix_me(hash_mix & h) const {
   h.mix(address_family_); // uint32_t
   h.mix(address_); // std::string
   h.mix(snmp_ifindex_); // uint32_t
   h.mix(oid_); // std::string
}

std::string
lldp_management_address_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_management_address_t(";
   ss << "address_family=" << address_family_;
   ss << ", address='" << address_ << "'";
   ss << ", snmp_ifindex=" << snmp_ifindex_;
   ss << ", oid='" << oid_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const lldp_management_address_impl_t& obj) {
   os << obj.to_string();
   return os;
}



lldp_lacp_impl_t::lldp_lacp_impl_t() :
      capable_(), enabled_(), id_(), valid_(false) {
}

// LACP Info constructor.
lldp_lacp_impl_t::lldp_lacp_impl_t(bool capable, bool enabled, uint32_t id,
                                          bool valid) :
      capable_(capable), enabled_(enabled), id_(id), valid_(valid) {
}

bool
lldp_lacp_impl_t::capable() const {
   return capable_;
}

bool
lldp_lacp_impl_t::enabled() const {
   return enabled_;
}

uint32_t
lldp_lacp_impl_t::id() const {
   return id_;
}

bool
lldp_lacp_impl_t::valid() const {
   return valid_;
}

bool
lldp_lacp_impl_t::operator!() const {
   return !valid_;

}

uint32_t
lldp_lacp_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
lldp_lacp_impl_t::mix_me(hash_mix & h) const {
   h.mix(capable_); // bool
   h.mix(enabled_); // bool
   h.mix(id_); // uint32_t
   h.mix(valid_); // bool
}

std::string
lldp_lacp_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_lacp_t(";
   ss << "capable=" << capable_;
   ss << ", enabled=" << enabled_;
   ss << ", id=" << id_;
   ss << ", valid=" << valid_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const lldp_lacp_impl_t& obj) {
   os << obj.to_string();
   return os;
}



lldp_phy_impl_t::lldp_phy_impl_t() :
      autonegSupported_(), autonegEnabled_(), autonegCapabilitiesBm_(),
      valid_(false) {
}

// PHY Info constructor.
lldp_phy_impl_t::lldp_phy_impl_t(bool autonegSupported, bool autonegEnabled,
                                        uint16_t autonegCapabilitiesBm, bool valid) :
      autonegSupported_(autonegSupported), autonegEnabled_(autonegEnabled),
      autonegCapabilitiesBm_(autonegCapabilitiesBm), valid_(valid) {
}

bool
lldp_phy_impl_t::autonegSupported() const {
   return autonegSupported_;
}

bool
lldp_phy_impl_t::autonegEnabled() const {
   return autonegEnabled_;
}

uint16_t
lldp_phy_impl_t::autonegCapabilitiesBm() const {
   return autonegCapabilitiesBm_;
}

bool
lldp_phy_impl_t::valid() const {
   return valid_;
}

uint32_t
lldp_phy_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
lldp_phy_impl_t::mix_me(hash_mix & h) const {
   h.mix(autonegSupported_); // bool
   h.mix(autonegEnabled_); // bool
   h.mix(autonegCapabilitiesBm_); // uint16_t
   h.mix(valid_); // bool
}

std::string
lldp_phy_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_phy_t(";
   ss << "autonegSupported=" << autonegSupported_;
   ss << ", autonegEnabled=" << autonegEnabled_;
   ss << ", autonegCapabilitiesBm=" << autonegCapabilitiesBm_;
   ss << ", valid=" << valid_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const lldp_phy_impl_t& obj) {
   os << obj.to_string();
   return os;
}







lldp_chassis_id_impl_t::lldp_chassis_id_impl_t() :
      encoding_(LLDP_CHASSIS_NULL), value_() {
}

// chassis name, full constructor.
lldp_chassis_id_impl_t::lldp_chassis_id_impl_t(
         lldp_chassis_id_encoding_t encoding, std::string value) :
      encoding_(encoding), value_(value) {
}

lldp_chassis_id_encoding_t
lldp_chassis_id_impl_t::encoding() const {
   return encoding_;
}

std::string
lldp_chassis_id_impl_t::value() const {
   return value_;
}

std::string
lldp_chassis_id_impl_t::repr() const {

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

bool
lldp_chassis_id_impl_t::operator==(lldp_chassis_id_impl_t const & other) const {
   return encoding_ == other.encoding_ &&
          value_ == other.value_;
}

bool
lldp_chassis_id_impl_t::operator!=(lldp_chassis_id_impl_t const & other) const {
   return !operator==(other);
}

bool
lldp_chassis_id_impl_t::operator<(lldp_chassis_id_impl_t const & other) const {
   if(encoding_ != other.encoding_) {
      return encoding_ < other.encoding_;
   } else if(value_ != other.value_) {
      return value_ < other.value_;
   }
   return false;
}

uint32_t
lldp_chassis_id_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
lldp_chassis_id_impl_t::mix_me(hash_mix & h) const {
   h.mix(encoding_); // lldp_chassis_id_encoding_t
   h.mix(value_); // std::string
}

std::string
lldp_chassis_id_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_chassis_id_t(";
   ss << "encoding=" << encoding_;
   ss << ", value='" << value_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const lldp_chassis_id_impl_t& obj) {
   os << obj.to_string();
   return os;
}





lldp_intf_id_impl_t::lldp_intf_id_impl_t() :
      encoding_(LLDP_INTF_NULL), value_() {
}

// interface name, full constructor.
lldp_intf_id_impl_t::lldp_intf_id_impl_t(lldp_intf_id_encoding_t encoding,
                                                std::string value) :
      encoding_(encoding), value_(value) {
}

lldp_intf_id_encoding_t
lldp_intf_id_impl_t::encoding() const {
   return encoding_;
}

std::string
lldp_intf_id_impl_t::value() const {
   return value_;
}

std::string
lldp_intf_id_impl_t::repr() const {

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

bool
lldp_intf_id_impl_t::operator==(lldp_intf_id_impl_t const & other) const {
   return encoding_ == other.encoding_ &&
          value_ == other.value_;
}

bool
lldp_intf_id_impl_t::operator!=(lldp_intf_id_impl_t const & other) const {
   return !operator==(other);
}

bool
lldp_intf_id_impl_t::operator<(lldp_intf_id_impl_t const & other) const {
   if(encoding_ != other.encoding_) {
      return encoding_ < other.encoding_;
   } else if(value_ != other.value_) {
      return value_ < other.value_;
   }
   return false;
}

uint32_t
lldp_intf_id_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
lldp_intf_id_impl_t::mix_me(hash_mix & h) const {
   h.mix(encoding_); // lldp_intf_id_encoding_t
   h.mix(value_); // std::string
}

std::string
lldp_intf_id_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_intf_id_t(";
   ss << "encoding=" << encoding_;
   ss << ", value='" << value_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const lldp_intf_id_impl_t& obj) {
   os << obj.to_string();
   return os;
}



// remote system, default constructor.
lldp_remote_system_impl_t::lldp_remote_system_impl_t() :
      chassis_(lldp_chassis_id_t()), port_(lldp_intf_id_t()) {
}

// remote system, full constructor.
lldp_remote_system_impl_t::lldp_remote_system_impl_t(
         lldp_chassis_id_t chassis, lldp_intf_id_t port) :
      chassis_(chassis), port_(port) {
}

lldp_chassis_id_t
lldp_remote_system_impl_t::chassis() const {
   return chassis_;
}

void
lldp_remote_system_impl_t::chassis_is(lldp_chassis_id_t chassis) {
   chassis_ = chassis;
}

lldp_intf_id_t
lldp_remote_system_impl_t::port() const {
   return port_;
}

void
lldp_remote_system_impl_t::port_is(lldp_intf_id_t port) {
   port_ = port;
}

std::string
lldp_remote_system_impl_t::repr() const {

   char buf[128];
   snprintf(buf, 128, "%s;%s", chassis_.repr().c_str(),
                               port_.repr().c_str());
   return std::string(buf);

}

bool
lldp_remote_system_impl_t::operator==(lldp_remote_system_impl_t const & other)
       const {
   return chassis_ == other.chassis_ &&
          port_ == other.port_;
}

bool
lldp_remote_system_impl_t::operator!=(lldp_remote_system_impl_t const & other)
       const {
   return !operator==(other);
}

bool
lldp_remote_system_impl_t::operator<(lldp_remote_system_impl_t const & other)
       const {
   if(chassis_ != other.chassis_) {
      return chassis_ < other.chassis_;
   } else if(port_ != other.port_) {
      return port_ < other.port_;
   }
   return false;
}

uint32_t
lldp_remote_system_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
lldp_remote_system_impl_t::mix_me(hash_mix & h) const {
   h.mix(chassis_); // lldp_chassis_id_t
   h.mix(port_); // lldp_intf_id_t
}

std::string
lldp_remote_system_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_remote_system_t(";
   ss << "chassis=" << chassis_;
   ss << ", port=" << port_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const lldp_remote_system_impl_t& obj) {
   os << obj.to_string();
   return os;
}



// remote system, default constructor.
lldp_neighbor_impl_t::lldp_neighbor_impl_t() :
      intf_(), remote_system_() {
}

// first remote system.
lldp_neighbor_impl_t::lldp_neighbor_impl_t(intf_id_t intf) :
      intf_(intf), remote_system_() {
}

// specific remote system.
lldp_neighbor_impl_t::lldp_neighbor_impl_t(
         intf_id_t intf, lldp_remote_system_t remote_system) :
      intf_(intf), remote_system_(remote_system) {
}

intf_id_t
lldp_neighbor_impl_t::intf() const {
   return intf_;
}

void
lldp_neighbor_impl_t::intf_is(intf_id_t intf) {
   intf_ = intf;
}

lldp_remote_system_t
lldp_neighbor_impl_t::remote_system() const {
   return remote_system_;
}

void
lldp_neighbor_impl_t::remote_system_is(lldp_remote_system_t remote_system) {
   remote_system_ = remote_system;
}

std::string
lldp_neighbor_impl_t::repr() const {

   char buf[128];
   snprintf(buf, 128, "%s;%s;%s", intf_.to_string().c_str(),
           remote_system_.chassis().repr().c_str(),
           remote_system_.port().repr().c_str());
   return std::string(buf);

}

bool
lldp_neighbor_impl_t::operator==(lldp_neighbor_impl_t const & other) const {
   return intf_ == other.intf_ &&
          remote_system_ == other.remote_system_;
}

bool
lldp_neighbor_impl_t::operator!=(lldp_neighbor_impl_t const & other) const {
   return !operator==(other);
}

bool
lldp_neighbor_impl_t::operator<(lldp_neighbor_impl_t const & other) const {
   if(intf_ != other.intf_) {
      return intf_ < other.intf_;
   } else if(remote_system_ != other.remote_system_) {
      return remote_system_ < other.remote_system_;
   }
   return false;
}

uint32_t
lldp_neighbor_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
lldp_neighbor_impl_t::mix_me(hash_mix & h) const {
   h.mix(intf_); // intf_id_t
   h.mix(remote_system_); // lldp_remote_system_t
}

std::string
lldp_neighbor_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "lldp_neighbor_t(";
   ss << "intf=" << intf_;
   ss << ", remote_system=" << remote_system_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const lldp_neighbor_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/lldp.h>

#endif // EOS_INLINE_TYPES_LLDP_IMPL_H
