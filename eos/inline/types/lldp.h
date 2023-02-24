// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_LLDP_H
#define EOS_INLINE_TYPES_LLDP_H

namespace eos {



// TLV Type, default constructor.
lldp_tlv_type_t::lldp_tlv_type_t() {
   pimpl = std::shared_ptr<lldp_tlv_type_impl_t>(
      new lldp_tlv_type_impl_t()
   );
}
// TLV Type, full constructor.
lldp_tlv_type_t::lldp_tlv_type_t(uint32_t organization, uint8_t subtype) {
   pimpl = std::shared_ptr<lldp_tlv_type_impl_t>(
      new lldp_tlv_type_impl_t(
         organization,
         subtype
      )
   );
}
lldp_tlv_type_t::lldp_tlv_type_t(
   const lldp_tlv_type_t& other)
{
   pimpl = std::make_unique<lldp_tlv_type_impl_t>(
      lldp_tlv_type_impl_t(*other.pimpl));
}
lldp_tlv_type_t&
lldp_tlv_type_t::operator=(
   lldp_tlv_type_t const & other)
{
   pimpl = std::shared_ptr<lldp_tlv_type_impl_t>(
      new lldp_tlv_type_impl_t(*other.pimpl));
   return *this;
}

uint32_t
lldp_tlv_type_t::organization() const {
   return pimpl->organization();
}
void
lldp_tlv_type_t::organization_is(uint32_t organization) {
   pimpl->organization_is(organization);
}
uint8_t
lldp_tlv_type_t::subtype() const {
   return pimpl->subtype();
}
void
lldp_tlv_type_t::subtype_is(uint8_t subtype) {
   pimpl->subtype_is(subtype);
}
bool
lldp_tlv_type_t::operator==(lldp_tlv_type_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
lldp_tlv_type_t::operator!=(lldp_tlv_type_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
lldp_tlv_type_t::operator<(lldp_tlv_type_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
lldp_tlv_type_t::hash() const {
   return pimpl->hash();
}
void
lldp_tlv_type_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
lldp_tlv_type_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const lldp_tlv_type_t& obj) {
   return operator<<(os, *obj.pimpl);
}


EOS_SDK_PUBLIC std::ostream&
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


lldp_std_tlv_type_t::lldp_std_tlv_type_t() {
   pimpl = std::shared_ptr<lldp_std_tlv_type_impl_t>(
      new lldp_std_tlv_type_impl_t()
   );
}
lldp_std_tlv_type_t::lldp_std_tlv_type_t(
   const lldp_std_tlv_type_t& other)
{
   pimpl = std::make_unique<lldp_std_tlv_type_impl_t>(
      lldp_std_tlv_type_impl_t(*other.pimpl));
}
lldp_std_tlv_type_t&
lldp_std_tlv_type_t::operator=(
   lldp_std_tlv_type_t const & other)
{
   pimpl = std::shared_ptr<lldp_std_tlv_type_impl_t>(
      new lldp_std_tlv_type_impl_t(*other.pimpl));
   return *this;
}

void
lldp_std_tlv_type_t::chassis_id_is(bool enabled) {
   pimpl->chassis_id_is(enabled);
}
void
lldp_std_tlv_type_t::intf_id_is(bool enabled) {
   pimpl->intf_id_is(enabled);
}
void
lldp_std_tlv_type_t::intf_description_is(bool enabled) {
   pimpl->intf_description_is(enabled);
}
void
lldp_std_tlv_type_t::system_capabilities_is(bool enabled) {
   pimpl->system_capabilities_is(enabled);
}
void
lldp_std_tlv_type_t::management_address_is(bool enabled) {
   pimpl->management_address_is(enabled);
}
void
lldp_std_tlv_type_t::default_vlan_is(bool enabled) {
   pimpl->default_vlan_is(enabled);
}
void
lldp_std_tlv_type_t::management_vlan_is(bool enabled) {
   pimpl->management_vlan_is(enabled);
}
void
lldp_std_tlv_type_t::max_frame_size_is(bool enabled) {
   pimpl->max_frame_size_is(enabled);
}
void
lldp_std_tlv_type_t::lacp_is(bool enabled) {
   pimpl->lacp_is(enabled);
}
void
lldp_std_tlv_type_t::phy_is(bool enabled) {
   pimpl->phy_is(enabled);
}
bool
lldp_std_tlv_type_t::chassis_id() const {
   return pimpl->chassis_id();
}
bool
lldp_std_tlv_type_t::intf_id() const {
   return pimpl->intf_id();
}
bool
lldp_std_tlv_type_t::intf_description() const {
   return pimpl->intf_description();
}
bool
lldp_std_tlv_type_t::system_capabilities() const {
   return pimpl->system_capabilities();
}
bool
lldp_std_tlv_type_t::management_address() const {
   return pimpl->management_address();
}
bool
lldp_std_tlv_type_t::default_vlan() const {
   return pimpl->default_vlan();
}
bool
lldp_std_tlv_type_t::management_vlan() const {
   return pimpl->management_vlan();
}
bool
lldp_std_tlv_type_t::max_frame_size() const {
   return pimpl->max_frame_size();
}
bool
lldp_std_tlv_type_t::lacp() const {
   return pimpl->lacp();
}
bool
lldp_std_tlv_type_t::phy() const {
   return pimpl->phy();
}
uint32_t
lldp_std_tlv_type_t::hash() const {
   return pimpl->hash();
}
void
lldp_std_tlv_type_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
lldp_std_tlv_type_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const lldp_std_tlv_type_t& obj) {
   return operator<<(os, *obj.pimpl);
}


EOS_SDK_PUBLIC std::ostream&
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


lldp_syscap_t::lldp_syscap_t() {
   pimpl = std::shared_ptr<lldp_syscap_impl_t>(
      new lldp_syscap_impl_t()
   );
}
// syscap, full constructor.
lldp_syscap_t::lldp_syscap_t(lldp_syscap_bits_t bitset) {
   pimpl = std::shared_ptr<lldp_syscap_impl_t>(
      new lldp_syscap_impl_t(
         bitset
      )
   );
}
lldp_syscap_t::lldp_syscap_t(
   const lldp_syscap_t& other)
{
   pimpl = std::make_unique<lldp_syscap_impl_t>(
      lldp_syscap_impl_t(*other.pimpl));
}
lldp_syscap_t&
lldp_syscap_t::operator=(
   lldp_syscap_t const & other)
{
   pimpl = std::shared_ptr<lldp_syscap_impl_t>(
      new lldp_syscap_impl_t(*other.pimpl));
   return *this;
}

bool
lldp_syscap_t::other() const {
   return pimpl->other();
}
bool
lldp_syscap_t::repeater() const {
   return pimpl->repeater();
}
bool
lldp_syscap_t::bridge() const {
   return pimpl->bridge();
}
bool
lldp_syscap_t::vlan_ap() const {
   return pimpl->vlan_ap();
}
bool
lldp_syscap_t::router() const {
   return pimpl->router();
}
bool
lldp_syscap_t::telephone() const {
   return pimpl->telephone();
}
bool
lldp_syscap_t::docsis() const {
   return pimpl->docsis();
}
bool
lldp_syscap_t::station() const {
   return pimpl->station();
}
uint32_t
lldp_syscap_t::hash() const {
   return pimpl->hash();
}
void
lldp_syscap_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
lldp_syscap_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const lldp_syscap_t& obj) {
   return operator<<(os, *obj.pimpl);
}


lldp_management_address_t::lldp_management_address_t() {
   pimpl = std::shared_ptr<lldp_management_address_impl_t>(
      new lldp_management_address_impl_t()
   );
}
// Managment Info constructor.
lldp_management_address_t::lldp_management_address_t(
         uint32_t address_family, std::string address, uint32_t snmp_ifindex,
         std::string oid) {
   pimpl = std::shared_ptr<lldp_management_address_impl_t>(
      new lldp_management_address_impl_t(
         address_family,
         address,
         snmp_ifindex,
         oid
      )
   );
}
lldp_management_address_t::lldp_management_address_t(
   const lldp_management_address_t& other)
{
   pimpl = std::make_unique<lldp_management_address_impl_t>(
      lldp_management_address_impl_t(*other.pimpl));
}
lldp_management_address_t&
lldp_management_address_t::operator=(
   lldp_management_address_t const & other)
{
   pimpl = std::shared_ptr<lldp_management_address_impl_t>(
      new lldp_management_address_impl_t(*other.pimpl));
   return *this;
}

uint32_t
lldp_management_address_t::address_family() const {
   return pimpl->address_family();
}
std::string
lldp_management_address_t::address() const {
   return pimpl->address();
}
uint32_t
lldp_management_address_t::snmp_ifindex() const {
   return pimpl->snmp_ifindex();
}
std::string
lldp_management_address_t::oid() const {
   return pimpl->oid();
}
bool
lldp_management_address_t::operator<(lldp_management_address_t const & other)
       const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
lldp_management_address_t::hash() const {
   return pimpl->hash();
}
void
lldp_management_address_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
lldp_management_address_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const lldp_management_address_t& obj) {
   return operator<<(os, *obj.pimpl);
}


lldp_lacp_t::lldp_lacp_t() {
   pimpl = std::shared_ptr<lldp_lacp_impl_t>(
      new lldp_lacp_impl_t()
   );
}
// LACP Info constructor.
lldp_lacp_t::lldp_lacp_t(bool capable, bool enabled, uint32_t id,
                                bool valid) {
   pimpl = std::shared_ptr<lldp_lacp_impl_t>(
      new lldp_lacp_impl_t(
         capable,
         enabled,
         id,
         valid
      )
   );
}
lldp_lacp_t::lldp_lacp_t(
   const lldp_lacp_t& other)
{
   pimpl = std::make_unique<lldp_lacp_impl_t>(
      lldp_lacp_impl_t(*other.pimpl));
}
lldp_lacp_t&
lldp_lacp_t::operator=(
   lldp_lacp_t const & other)
{
   pimpl = std::shared_ptr<lldp_lacp_impl_t>(
      new lldp_lacp_impl_t(*other.pimpl));
   return *this;
}

bool
lldp_lacp_t::capable() const {
   return pimpl->capable();
}
bool
lldp_lacp_t::enabled() const {
   return pimpl->enabled();
}
uint32_t
lldp_lacp_t::id() const {
   return pimpl->id();
}
bool
lldp_lacp_t::valid() const {
   return pimpl->valid();
}
bool
lldp_lacp_t::operator!() const {
   return pimpl->operator!();
}
uint32_t
lldp_lacp_t::hash() const {
   return pimpl->hash();
}
void
lldp_lacp_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
lldp_lacp_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const lldp_lacp_t& obj) {
   return operator<<(os, *obj.pimpl);
}


lldp_phy_t::lldp_phy_t() {
   pimpl = std::shared_ptr<lldp_phy_impl_t>(
      new lldp_phy_impl_t()
   );
}
// PHY Info constructor.
lldp_phy_t::lldp_phy_t(bool autonegSupported, bool autonegEnabled,
                              uint16_t autonegCapabilitiesBm, bool valid) {
   pimpl = std::shared_ptr<lldp_phy_impl_t>(
      new lldp_phy_impl_t(
         autonegSupported,
         autonegEnabled,
         autonegCapabilitiesBm,
         valid
      )
   );
}
lldp_phy_t::lldp_phy_t(
   const lldp_phy_t& other)
{
   pimpl = std::make_unique<lldp_phy_impl_t>(
      lldp_phy_impl_t(*other.pimpl));
}
lldp_phy_t&
lldp_phy_t::operator=(
   lldp_phy_t const & other)
{
   pimpl = std::shared_ptr<lldp_phy_impl_t>(
      new lldp_phy_impl_t(*other.pimpl));
   return *this;
}

bool
lldp_phy_t::autonegSupported() const {
   return pimpl->autonegSupported();
}
bool
lldp_phy_t::autonegEnabled() const {
   return pimpl->autonegEnabled();
}
uint16_t
lldp_phy_t::autonegCapabilitiesBm() const {
   return pimpl->autonegCapabilitiesBm();
}
bool
lldp_phy_t::valid() const {
   return pimpl->valid();
}
uint32_t
lldp_phy_t::hash() const {
   return pimpl->hash();
}
void
lldp_phy_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
lldp_phy_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const lldp_phy_t& obj) {
   return operator<<(os, *obj.pimpl);
}


EOS_SDK_PUBLIC std::ostream&
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


EOS_SDK_PUBLIC std::ostream&
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


lldp_chassis_id_t::lldp_chassis_id_t() {
   pimpl = std::shared_ptr<lldp_chassis_id_impl_t>(
      new lldp_chassis_id_impl_t()
   );
}
// chassis name, full constructor.
lldp_chassis_id_t::lldp_chassis_id_t(lldp_chassis_id_encoding_t encoding,
                                            std::string value) {
   pimpl = std::shared_ptr<lldp_chassis_id_impl_t>(
      new lldp_chassis_id_impl_t(
         encoding,
         value
      )
   );
}
lldp_chassis_id_t::lldp_chassis_id_t(
   const lldp_chassis_id_t& other)
{
   pimpl = std::make_unique<lldp_chassis_id_impl_t>(
      lldp_chassis_id_impl_t(*other.pimpl));
}
lldp_chassis_id_t&
lldp_chassis_id_t::operator=(
   lldp_chassis_id_t const & other)
{
   pimpl = std::shared_ptr<lldp_chassis_id_impl_t>(
      new lldp_chassis_id_impl_t(*other.pimpl));
   return *this;
}

lldp_chassis_id_encoding_t
lldp_chassis_id_t::encoding() const {
   return pimpl->encoding();
}
std::string
lldp_chassis_id_t::value() const {
   return pimpl->value();
}
std::string
lldp_chassis_id_t::repr() const {
   return pimpl->repr();
}
bool
lldp_chassis_id_t::operator==(lldp_chassis_id_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
lldp_chassis_id_t::operator!=(lldp_chassis_id_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
lldp_chassis_id_t::operator<(lldp_chassis_id_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
lldp_chassis_id_t::hash() const {
   return pimpl->hash();
}
void
lldp_chassis_id_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
lldp_chassis_id_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const lldp_chassis_id_t& obj) {
   return operator<<(os, *obj.pimpl);
}


EOS_SDK_PUBLIC std::ostream&
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


lldp_intf_id_t::lldp_intf_id_t() {
   pimpl = std::shared_ptr<lldp_intf_id_impl_t>(
      new lldp_intf_id_impl_t()
   );
}
// interface name, full constructor.
lldp_intf_id_t::lldp_intf_id_t(lldp_intf_id_encoding_t encoding,
                                      std::string value) {
   pimpl = std::shared_ptr<lldp_intf_id_impl_t>(
      new lldp_intf_id_impl_t(
         encoding,
         value
      )
   );
}
lldp_intf_id_t::lldp_intf_id_t(
   const lldp_intf_id_t& other)
{
   pimpl = std::make_unique<lldp_intf_id_impl_t>(
      lldp_intf_id_impl_t(*other.pimpl));
}
lldp_intf_id_t&
lldp_intf_id_t::operator=(
   lldp_intf_id_t const & other)
{
   pimpl = std::shared_ptr<lldp_intf_id_impl_t>(
      new lldp_intf_id_impl_t(*other.pimpl));
   return *this;
}

lldp_intf_id_encoding_t
lldp_intf_id_t::encoding() const {
   return pimpl->encoding();
}
std::string
lldp_intf_id_t::value() const {
   return pimpl->value();
}
std::string
lldp_intf_id_t::repr() const {
   return pimpl->repr();
}
bool
lldp_intf_id_t::operator==(lldp_intf_id_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
lldp_intf_id_t::operator!=(lldp_intf_id_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
lldp_intf_id_t::operator<(lldp_intf_id_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
lldp_intf_id_t::hash() const {
   return pimpl->hash();
}
void
lldp_intf_id_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
lldp_intf_id_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const lldp_intf_id_t& obj) {
   return operator<<(os, *obj.pimpl);
}


// remote system, default constructor.
lldp_remote_system_t::lldp_remote_system_t() {
   pimpl = std::shared_ptr<lldp_remote_system_impl_t>(
      new lldp_remote_system_impl_t()
   );
}
// remote system, full constructor.
lldp_remote_system_t::lldp_remote_system_t(lldp_chassis_id_t chassis,
                                                  lldp_intf_id_t port) {
   pimpl = std::shared_ptr<lldp_remote_system_impl_t>(
      new lldp_remote_system_impl_t(
         chassis,
         port
      )
   );
}
lldp_remote_system_t::lldp_remote_system_t(
   const lldp_remote_system_t& other)
{
   pimpl = std::make_unique<lldp_remote_system_impl_t>(
      lldp_remote_system_impl_t(*other.pimpl));
}
lldp_remote_system_t&
lldp_remote_system_t::operator=(
   lldp_remote_system_t const & other)
{
   pimpl = std::shared_ptr<lldp_remote_system_impl_t>(
      new lldp_remote_system_impl_t(*other.pimpl));
   return *this;
}

lldp_chassis_id_t
lldp_remote_system_t::chassis() const {
   return pimpl->chassis();
}
void
lldp_remote_system_t::chassis_is(lldp_chassis_id_t chassis) {
   pimpl->chassis_is(chassis);
}
lldp_intf_id_t
lldp_remote_system_t::port() const {
   return pimpl->port();
}
void
lldp_remote_system_t::port_is(lldp_intf_id_t port) {
   pimpl->port_is(port);
}
std::string
lldp_remote_system_t::repr() const {
   return pimpl->repr();
}
bool
lldp_remote_system_t::operator==(lldp_remote_system_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
lldp_remote_system_t::operator!=(lldp_remote_system_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
lldp_remote_system_t::operator<(lldp_remote_system_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
lldp_remote_system_t::hash() const {
   return pimpl->hash();
}
void
lldp_remote_system_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
lldp_remote_system_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const lldp_remote_system_t& obj) {
   return operator<<(os, *obj.pimpl);
}


// remote system, default constructor.
lldp_neighbor_t::lldp_neighbor_t() {
   pimpl = std::shared_ptr<lldp_neighbor_impl_t>(
      new lldp_neighbor_impl_t()
   );
}
// first remote system.
lldp_neighbor_t::lldp_neighbor_t(intf_id_t intf) {
   pimpl = std::shared_ptr<lldp_neighbor_impl_t>(
      new lldp_neighbor_impl_t(
         intf
      )
   );
}
// specific remote system.
lldp_neighbor_t::lldp_neighbor_t(intf_id_t intf,
                                        lldp_remote_system_t remote_system) {
   pimpl = std::shared_ptr<lldp_neighbor_impl_t>(
      new lldp_neighbor_impl_t(
         intf,
         remote_system
      )
   );
}
lldp_neighbor_t::lldp_neighbor_t(
   const lldp_neighbor_t& other)
{
   pimpl = std::make_unique<lldp_neighbor_impl_t>(
      lldp_neighbor_impl_t(*other.pimpl));
}
lldp_neighbor_t&
lldp_neighbor_t::operator=(
   lldp_neighbor_t const & other)
{
   pimpl = std::shared_ptr<lldp_neighbor_impl_t>(
      new lldp_neighbor_impl_t(*other.pimpl));
   return *this;
}

intf_id_t
lldp_neighbor_t::intf() const {
   return pimpl->intf();
}
void
lldp_neighbor_t::intf_is(intf_id_t intf) {
   pimpl->intf_is(intf);
}
lldp_remote_system_t
lldp_neighbor_t::remote_system() const {
   return pimpl->remote_system();
}
void
lldp_neighbor_t::remote_system_is(lldp_remote_system_t remote_system) {
   pimpl->remote_system_is(remote_system);
}
std::string
lldp_neighbor_t::repr() const {
   return pimpl->repr();
}
bool
lldp_neighbor_t::operator==(lldp_neighbor_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
lldp_neighbor_t::operator!=(lldp_neighbor_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
lldp_neighbor_t::operator<(lldp_neighbor_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
lldp_neighbor_t::hash() const {
   return pimpl->hash();
}
void
lldp_neighbor_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
lldp_neighbor_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const lldp_neighbor_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_LLDP_H
