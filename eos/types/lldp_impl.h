// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_LLDP_IMPL_H
#define EOS_TYPES_LLDP_IMPL_H

#include <arpa/inet.h>
#include <eos/hash_mix.h>
#include <eos/intf.h>
#include <eos/utility.h>
#include <memory>
#include <netinet/ether.h>
#include <sstream>

namespace eos {

/** An LLDP organizationally defined TLV type. */
class EOS_SDK_PUBLIC lldp_tlv_type_impl_t {
 public:
   lldp_tlv_type_impl_t();
   lldp_tlv_type_impl_t(uint32_t organization, uint8_t subtype);

   /**
    * Getter for 'organization': IEEE assigned Organizationally Unique Identifier
    * (OUI), 24 bits.
    */
   uint32_t organization() const;
   /** Setter for 'organization'. */
   void organization_is(uint32_t organization);

   /** Getter for 'subtype': Subtype under OUI (managed by org.), 8 bits. */
   uint8_t subtype() const;
   /** Setter for 'subtype'. */
   void subtype_is(uint8_t subtype);

   bool operator==(lldp_tlv_type_impl_t const & other) const;
   bool operator!=(lldp_tlv_type_impl_t const & other) const;
   bool operator<(lldp_tlv_type_impl_t const & other) const;
   /** The hash function for type lldp_tlv_type_t. */
   uint32_t hash() const;
   /** The hash mix function for type lldp_tlv_type_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * lldp_tlv_type_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const lldp_tlv_type_impl_t& obj);

 private:
   uint32_t organization_;
   uint8_t subtype_;
};

/** Defines a set of remote TLVs (for which we have a value for). */
class EOS_SDK_PUBLIC lldp_std_tlv_type_impl_t {
 public:
   lldp_std_tlv_type_impl_t();

   void chassis_id_is(bool enabled);
   void intf_id_is(bool enabled);
   void intf_description_is(bool enabled);
   void system_capabilities_is(bool enabled);
   void management_address_is(bool enabled);
   void default_vlan_is(bool enabled);
   void management_vlan_is(bool enabled);
   void max_frame_size_is(bool enabled);
   void lacp_is(bool enabled);
   void phy_is(bool enabled);
   bool chassis_id() const;
   bool intf_id() const;
   bool intf_description() const;
   bool system_capabilities() const;
   bool management_address() const;
   bool default_vlan() const;
   bool management_vlan() const;
   bool max_frame_size() const;
   bool lacp() const;
   bool phy() const;
   /** The hash function for type lldp_std_tlv_type_t. */
   uint32_t hash() const;
   /** The hash mix function for type lldp_std_tlv_type_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * lldp_std_tlv_type_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const lldp_std_tlv_type_impl_t& obj);

 private:
   lldp_std_tlv_type_bit_t bitset_;
};

/** Defines a set of remote system capabilities. */
class EOS_SDK_PUBLIC lldp_syscap_impl_t {
 public:
   lldp_syscap_impl_t();
   explicit lldp_syscap_impl_t(lldp_syscap_bits_t bitset);

   bool other() const;
   bool repeater() const;
   bool bridge() const;
   bool vlan_ap() const;
   bool router() const;
   bool telephone() const;
   bool docsis() const;
   bool station() const;
   /** The hash function for type lldp_syscap_t. */
   uint32_t hash() const;
   /** The hash mix function for type lldp_syscap_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of lldp_syscap_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const lldp_syscap_impl_t& obj);

 private:
   lldp_syscap_bits_t bitset_;
};

/** Management information of the switch across the link. */
class EOS_SDK_PUBLIC lldp_management_address_impl_t {
 public:
   lldp_management_address_impl_t();
   lldp_management_address_impl_t(uint32_t address_family, std::string address,
                                  uint32_t snmp_ifindex, std::string oid);

   /**
    * Getter for 'address_family': Type of address encoded in address field (see
    * IANA Address Family Numbers MIB).
    */
   uint32_t address_family() const;

   /**
    * Getter for 'address': The address, max size 31 octets (ipv4 or ipv6 most
    * likely).
    */
   std::string address() const;

   /**
    * Getter for 'snmp_ifindex': The SNMP interface index of the management
    * interface.
    */
   uint32_t snmp_ifindex() const;

   /**
    * Getter for 'oid': The SNMP OID that describes the hardware the management
    * interface is part of.
    */
   std::string oid() const;

   bool operator<(lldp_management_address_impl_t const & other) const;
   /** The hash function for type lldp_management_address_t. */
   uint32_t hash() const;
   /** The hash mix function for type lldp_management_address_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * lldp_management_address_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const lldp_management_address_impl_t& obj);

 private:
   uint32_t address_family_;
   std::string address_;
   uint32_t snmp_ifindex_;
   std::string oid_;
};

/** LACP information from the peer. */
class EOS_SDK_PUBLIC lldp_lacp_impl_t {
 public:
   lldp_lacp_impl_t();
   lldp_lacp_impl_t(bool capable, bool enabled, uint32_t id, bool valid);

   /** Getter for 'capable': if port can become a member of a port-channel. */
   bool capable() const;

   /** Getter for 'enabled': if port is a member of a port-channel. */
   bool enabled() const;

   /**
    * Getter for 'id': which port-channel number this interface is part of, (if
    * enabled=true).
    */
   uint32_t id() const;

   /**
    * Getter for 'valid': true if such tlv was received, else other fields are
    * bogus.
    */
   bool valid() const;

   /** invalid lacp_t returned if no such tlv received. */
   bool operator!() const;
   /** The hash function for type lldp_lacp_t. */
   uint32_t hash() const;
   /** The hash mix function for type lldp_lacp_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of lldp_lacp_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const lldp_lacp_impl_t& obj);

 private:
   bool capable_;
   bool enabled_;
   uint32_t id_;
   bool valid_;
};

/** PHY information from the peer (related to speed auto-negotiation). */
class EOS_SDK_PUBLIC lldp_phy_impl_t {
 public:
   lldp_phy_impl_t();
   lldp_phy_impl_t(bool autonegSupported, bool autonegEnabled,
                   uint16_t autonegCapabilitiesBm, bool valid);

   /** Getter for 'autonegSupported': if auto-negotiation supported. */
   bool autonegSupported() const;

   /** Getter for 'autonegEnabled': if auto-negatiation enabled. */
   bool autonegEnabled() const;

   /** Getter for 'autonegCapabilitiesBm': capabilities bitmask. */
   uint16_t autonegCapabilitiesBm() const;

   /** Getter for 'valid': if phy-info tlv received from remote. */
   bool valid() const;

   /** The hash function for type lldp_phy_t. */
   uint32_t hash() const;
   /** The hash mix function for type lldp_phy_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of lldp_phy_t to
    * the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const lldp_phy_impl_t& obj);

 private:
   bool autonegSupported_;
   bool autonegEnabled_;
   uint16_t autonegCapabilitiesBm_;
   bool valid_;
};

/** The chassis name, as an encoding plus payload. */
class EOS_SDK_PUBLIC lldp_chassis_id_impl_t {
 public:
   lldp_chassis_id_impl_t();
   lldp_chassis_id_impl_t(lldp_chassis_id_encoding_t encoding, std::string value);

   lldp_chassis_id_encoding_t encoding() const;

   std::string value() const;

   /** String representation of a chassisId. */
   std::string repr() const;
   bool operator==(lldp_chassis_id_impl_t const & other) const;
   bool operator!=(lldp_chassis_id_impl_t const & other) const;
   bool operator<(lldp_chassis_id_impl_t const & other) const;
   /** The hash function for type lldp_chassis_id_t. */
   uint32_t hash() const;
   /** The hash mix function for type lldp_chassis_id_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * lldp_chassis_id_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const lldp_chassis_id_impl_t& obj);

 private:
   lldp_chassis_id_encoding_t encoding_;
   std::string value_;
};

/** The interface name, as an encoding plus payload. */
class EOS_SDK_PUBLIC lldp_intf_id_impl_t {
 public:
   lldp_intf_id_impl_t();
   lldp_intf_id_impl_t(lldp_intf_id_encoding_t encoding, std::string value);

   lldp_intf_id_encoding_t encoding() const;

   std::string value() const;

   /** String representation of a chassisId. */
   std::string repr() const;
   bool operator==(lldp_intf_id_impl_t const & other) const;
   bool operator!=(lldp_intf_id_impl_t const & other) const;
   bool operator<(lldp_intf_id_impl_t const & other) const;
   /** The hash function for type lldp_intf_id_t. */
   uint32_t hash() const;
   /** The hash mix function for type lldp_intf_id_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of lldp_intf_id_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const lldp_intf_id_impl_t& obj);

 private:
   lldp_intf_id_encoding_t encoding_;
   std::string value_;
};

/** Identifies a remote system as seen across an LLDP interface. */
class EOS_SDK_PUBLIC lldp_remote_system_impl_t {
 public:
   lldp_remote_system_impl_t();
   lldp_remote_system_impl_t(lldp_chassis_id_t chassis, lldp_intf_id_t port);

   /** Getter for 'chassis': The chassis-id of the remote system. */
   lldp_chassis_id_t chassis() const;
   /** Setter for 'chassis'. */
   void chassis_is(lldp_chassis_id_t chassis);

   /** Getter for 'port': The port-id of the remote system. */
   lldp_intf_id_t port() const;
   /** Setter for 'port'. */
   void port_is(lldp_intf_id_t port);

   /** String representation of a chassisId. */
   std::string repr() const;
   bool operator==(lldp_remote_system_impl_t const & other) const;
   bool operator!=(lldp_remote_system_impl_t const & other) const;
   bool operator<(lldp_remote_system_impl_t const & other) const;
   /** The hash function for type lldp_remote_system_t. */
   uint32_t hash() const;
   /** The hash mix function for type lldp_remote_system_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * lldp_remote_system_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const lldp_remote_system_impl_t& obj);

 private:
   lldp_chassis_id_t chassis_;
   lldp_intf_id_t port_;
};

/** Identifies a remote system seen from the local switch. */
class EOS_SDK_PUBLIC lldp_neighbor_impl_t {
 public:
   lldp_neighbor_impl_t();
   explicit lldp_neighbor_impl_t(intf_id_t intf);
   lldp_neighbor_impl_t(intf_id_t intf, lldp_remote_system_t remote_system);

   /** Getter for 'intf': The local interface that sees this neighbor. */
   intf_id_t intf() const;
   /** Setter for 'intf'. */
   void intf_is(intf_id_t intf);

   /**
    * Getter for 'remote_system': The id of the remote system (an interface can see
    * more than one).
    */
   lldp_remote_system_t remote_system() const;
   /** Setter for 'remote_system'. */
   void remote_system_is(lldp_remote_system_t remote_system);

   /** String representation of a chassisId. */
   std::string repr() const;
   bool operator==(lldp_neighbor_impl_t const & other) const;
   bool operator!=(lldp_neighbor_impl_t const & other) const;
   bool operator<(lldp_neighbor_impl_t const & other) const;
   /** The hash function for type lldp_neighbor_t. */
   uint32_t hash() const;
   /** The hash mix function for type lldp_neighbor_t. */
   void mix_me(hash_mix & h) const;
   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * lldp_neighbor_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os,
                                   const lldp_neighbor_impl_t& obj);

 private:
   intf_id_t intf_;
   lldp_remote_system_t remote_system_;
};
}

#endif // EOS_TYPES_LLDP_IMPL_H
