// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_MPLS_H
#define EOS_TYPES_MPLS_H

#include <eos/base.h>
#include <eos/hash_mix.h>
#include <memory>

namespace eos {

/** The action to take for an MPLS route. */
enum mpls_action_t {
   MPLS_ACTION_NULL,
   MPLS_ACTION_PUSH,
   MPLS_ACTION_POP,
   MPLS_ACTION_SWAP,
   MPLS_ACTION_FORWARD,
};
/** Appends a string representation of enum mpls_action_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const mpls_action_t & enum_val);

/** Whether to use the pipe or uniform TTL inheritance mode. */
enum mpls_ttl_mode_t {
   MPLS_TTLMODE_NULL,
   /** pipe" mode, do not inherit TTL from inner IP. */
   MPLS_TTLMODE_PIPE,
   /** uniform" mode, inherit TTL from inner IP. */
   MPLS_TTLMODE_UNIFORM,
};
/** Appends a string representation of enum mpls_ttl_mode_t value to the ostream. */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const mpls_ttl_mode_t & enum_val);

/**
 * The inner payload type.
 *  Used in a similar way to ethertype, as MPLS does not provide this
 *  in the packet.
 */
enum mpls_payload_type_t {
   MPLS_PAYLOAD_TYPE_NULL,
   MPLS_PAYLOAD_TYPE_MPLS,
   MPLS_PAYLOAD_TYPE_IPV4,
   MPLS_PAYLOAD_TYPE_IPV6,
   MPLS_PAYLOAD_TYPE_GUESS,
};
/**
 * Appends a string representation of enum mpls_payload_type_t value to the
 * ostream.
 */
EOS_SDK_PUBLIC std::ostream& operator<<(std::ostream& os,
                                        const mpls_payload_type_t & enum_val);

/**
 * An MPLS label, per RFC 3032. Note: label id 0 (default value) is the explicit
 * null label. LSRs receiving this label are expected to pop it and perform
 * ultimate IP orwarding. MPLS label numbers are 20 bits in size, covering the
 * range 0..1048575.
 */
class EOS_SDK_PUBLIC mpls_label_t {
 public:
   explicit mpls_label_t(uint32_t label);

    mpls_label_t();
   /** Getter for 'label': key for the route that this via is attached to. */
   uint32_t label() const;
   /** Setter for 'label'. */
   void label_is(uint32_t label);

   enum  {
      MIN,
      /** 1048575. */
      MAX = 0xfffff,
      /** 1048576. */
      INVALID = 0x100000,
   };
   bool operator!() const;
   /** Returns a string representation of the MPLS label. */
   std::string to_string() const;
   bool operator==(mpls_label_t const & other) const;
   bool operator!=(mpls_label_t const & other) const;
   bool operator<(mpls_label_t const & other) const;
   /** The hash function for type mpls_label_t. */
   uint32_t hash() const;
   /** The hash mix function for type mpls_label_t. */
   void mix_me(hash_mix & h) const;
   /**
    * A utility stream operator that adds a string representation of mpls_label_t
    * to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const mpls_label_t& obj);

 private:
   uint32_t label_;
   friend struct MplsLabelHelper;
};

EOS_SDK_PUBLIC
std::ostream& operator<<(std::ostream& os, const mpls_label_t& obj);
}

#endif // EOS_TYPES_MPLS_H
