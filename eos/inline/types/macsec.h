// Copyright (c) 2020 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MACSEC_H
#define EOS_INLINE_TYPES_MACSEC_H

namespace eos {

inline std::ostream&
operator<<(std::ostream& os, const macsec_cipher_suite_t & enum_val) {
   if (enum_val==CIPHER_NULL) {
      os << "CIPHER_NULL";
   } else if (enum_val==GCM_AES_XPN_128) {
      os << "GCM_AES_XPN_128";
   } else if (enum_val==GCM_AES_XPN_256) {
      os << "GCM_AES_XPN_256";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline std::ostream&
operator<<(std::ostream& os, const macsec_intf_key_status_t & enum_val) {
   if (enum_val==MACSEC_NO_PROFILE) {
      os << "MACSEC_NO_PROFILE";
   } else if (enum_val==MACSEC_KEY_NONE) {
      os << "MACSEC_KEY_NONE";
   } else if (enum_val==MACSEC_KEY_PRIMARY) {
      os << "MACSEC_KEY_PRIMARY";
   } else if (enum_val==MACSEC_KEY_FALLBACK) {
      os << "MACSEC_KEY_FALLBACK";
   } else {
      os << "Unknown value";
   }
   return os;
}



inline macsec_key_t::macsec_key_t() :
      cak_(), ckn_(), encoded_(false) {
}

inline std::string
macsec_key_t::cak() const {
   return cak_;
}

inline void
macsec_key_t::cak_is(std::string cak) {
   cak_ = cak;
}

inline std::string
macsec_key_t::ckn() const {
   return ckn_;
}

inline void
macsec_key_t::ckn_is(std::string ckn) {
   ckn_ = ckn;
}

inline bool
macsec_key_t::encoded() const {
   return encoded_;
}

inline void
macsec_key_t::encoded_is(bool encoded) {
   encoded_ = encoded;
}

inline bool
macsec_key_t::operator==(macsec_key_t const & other) const {
   return cak_ == other.cak_ &&
          ckn_ == other.ckn_ &&
          encoded_ == other.encoded_;
}

inline bool
macsec_key_t::operator!=(macsec_key_t const & other) const {
   return !operator==(other);
}

inline bool
macsec_key_t::operator<(macsec_key_t const & other) const {
   if(cak_ != other.cak_) {
      return cak_ < other.cak_;
   } else if(ckn_ != other.ckn_) {
      return ckn_ < other.ckn_;
   } else if(encoded_ != other.encoded_) {
      return encoded_ < other.encoded_;
   }
   return false;
}

inline uint32_t
macsec_key_t::hash() const {
   uint32_t ret = 0;
   ret ^= std::hash<std::string>()(cak_);
   ret ^= std::hash<std::string>()(ckn_);
   ret = hash_mix::mix((uint8_t *)&encoded_,
              sizeof(bool), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
macsec_key_t::to_string() const {
   std::ostringstream ss;
   ss << "macsec_key_t(";
   ss << "cak='" << cak_ << "'";
   ss << ", ckn='" << ckn_ << "'";
   ss << ", encoded=" << encoded_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const macsec_key_t& obj) {
   os << obj.to_string();
   return os;
}



inline macsec_profile_t::macsec_profile_t() :
      name_(), primary_key_(), fallback_key_(), key_server_priority_(0),
      rekey_period_(0), cipher_(CIPHER_NULL), dot1x_(false), include_sci_(false),
      bypass_lldp_(false), allow_unprotected_(false), replay_protection_(true),
      replay_protection_window_(0), key_retirement_immediate_(false), intfs_() {
}

inline macsec_profile_t::macsec_profile_t(macsec_profile_name_t name) :
      name_(name), primary_key_(), fallback_key_(), key_server_priority_(16),
      rekey_period_(0), cipher_(GCM_AES_XPN_128), dot1x_(false),
      include_sci_(false), bypass_lldp_(false), allow_unprotected_(false),
      replay_protection_(true), replay_protection_window_(0),
      key_retirement_immediate_(false), intfs_() {
}

inline macsec_profile_name_t
macsec_profile_t::name() const {
   return name_;
}

inline void
macsec_profile_t::name_is(macsec_profile_name_t name) {
   name_ = name;
}

inline macsec_key_t
macsec_profile_t::primary_key() const {
   return primary_key_;
}

inline void
macsec_profile_t::primary_key_is(macsec_key_t primary_key) {
   primary_key_ = primary_key;
}

inline macsec_key_t
macsec_profile_t::fallback_key() const {
   return fallback_key_;
}

inline void
macsec_profile_t::fallback_key_is(macsec_key_t fallback_key) {
   fallback_key_ = fallback_key;
}

inline uint8_t
macsec_profile_t::key_server_priority() const {
   return key_server_priority_;
}

inline void
macsec_profile_t::key_server_priority_is(uint8_t key_server_priority) {
   key_server_priority_ = key_server_priority;
}

inline uint32_t
macsec_profile_t::rekey_period() const {
   return rekey_period_;
}

inline void
macsec_profile_t::rekey_period_is(uint32_t rekey_period) {
   rekey_period_ = rekey_period;
}

inline macsec_cipher_suite_t
macsec_profile_t::cipher() const {
   return cipher_;
}

inline void
macsec_profile_t::cipher_is(macsec_cipher_suite_t cipher) {
   cipher_ = cipher;
}

inline bool
macsec_profile_t::dot1x() const {
   return dot1x_;
}

inline void
macsec_profile_t::dot1x_is(bool dot1x) {
   dot1x_ = dot1x;
}

inline bool
macsec_profile_t::include_sci() const {
   return include_sci_;
}

inline void
macsec_profile_t::include_sci_is(bool include_sci) {
   include_sci_ = include_sci;
}

inline bool
macsec_profile_t::bypass_lldp() const {
   return bypass_lldp_;
}

inline void
macsec_profile_t::bypass_lldp_is(bool bypass_lldp) {
   bypass_lldp_ = bypass_lldp;
}

inline bool
macsec_profile_t::allow_unprotected() const {
   return allow_unprotected_;
}

inline void
macsec_profile_t::allow_unprotected_is(bool allow_unprotected) {
   allow_unprotected_ = allow_unprotected;
}

inline bool
macsec_profile_t::replay_protection() const {
   return replay_protection_;
}

inline void
macsec_profile_t::replay_protection_is(bool replay_protection) {
   replay_protection_ = replay_protection;
}

inline uint32_t
macsec_profile_t::replay_protection_window() const {
   return replay_protection_window_;
}

inline void
macsec_profile_t::replay_protection_window_is(uint32_t replay_protection_window) {
   replay_protection_window_ = replay_protection_window;
}

inline bool
macsec_profile_t::key_retirement_immediate() const {
   return key_retirement_immediate_;
}

inline void
macsec_profile_t::key_retirement_immediate_is(bool key_retirement_immediate) {
   key_retirement_immediate_ = key_retirement_immediate;
}

inline std::forward_list<intf_id_t> const &
macsec_profile_t::intfs() const {
   return intfs_;
}

inline bool
macsec_profile_t::operator==(macsec_profile_t const & other) const {
   return name_ == other.name_ &&
          primary_key_ == other.primary_key_ &&
          fallback_key_ == other.fallback_key_ &&
          key_server_priority_ == other.key_server_priority_ &&
          rekey_period_ == other.rekey_period_ &&
          cipher_ == other.cipher_ &&
          dot1x_ == other.dot1x_ &&
          include_sci_ == other.include_sci_ &&
          bypass_lldp_ == other.bypass_lldp_ &&
          allow_unprotected_ == other.allow_unprotected_ &&
          replay_protection_ == other.replay_protection_ &&
          replay_protection_window_ == other.replay_protection_window_ &&
          key_retirement_immediate_ == other.key_retirement_immediate_ &&
          intfs_ == other.intfs_;
}

inline bool
macsec_profile_t::operator!=(macsec_profile_t const & other) const {
   return !operator==(other);
}

inline bool
macsec_profile_t::operator<(macsec_profile_t const & other) const {
   if(name_ != other.name_) {
      return name_ < other.name_;
   } else if(primary_key_ != other.primary_key_) {
      return primary_key_ < other.primary_key_;
   } else if(fallback_key_ != other.fallback_key_) {
      return fallback_key_ < other.fallback_key_;
   } else if(key_server_priority_ != other.key_server_priority_) {
      return key_server_priority_ < other.key_server_priority_;
   } else if(rekey_period_ != other.rekey_period_) {
      return rekey_period_ < other.rekey_period_;
   } else if(cipher_ != other.cipher_) {
      return cipher_ < other.cipher_;
   } else if(dot1x_ != other.dot1x_) {
      return dot1x_ < other.dot1x_;
   } else if(include_sci_ != other.include_sci_) {
      return include_sci_ < other.include_sci_;
   } else if(bypass_lldp_ != other.bypass_lldp_) {
      return bypass_lldp_ < other.bypass_lldp_;
   } else if(allow_unprotected_ != other.allow_unprotected_) {
      return allow_unprotected_ < other.allow_unprotected_;
   } else if(replay_protection_ != other.replay_protection_) {
      return replay_protection_ < other.replay_protection_;
   } else if(replay_protection_window_ != other.replay_protection_window_) {
      return replay_protection_window_ < other.replay_protection_window_;
   } else if(key_retirement_immediate_ != other.key_retirement_immediate_) {
      return key_retirement_immediate_ < other.key_retirement_immediate_;
   } else if(intfs_ != other.intfs_) {
      return intfs_ < other.intfs_;
   }
   return false;
}

inline uint32_t
macsec_profile_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&name_,
              sizeof(macsec_profile_name_t), ret);
   ret = hash_mix::mix((uint8_t *)&primary_key_,
              sizeof(macsec_key_t), ret);
   ret = hash_mix::mix((uint8_t *)&fallback_key_,
              sizeof(macsec_key_t), ret);
   ret = hash_mix::mix((uint8_t *)&key_server_priority_,
              sizeof(uint8_t), ret);
   ret = hash_mix::mix((uint8_t *)&rekey_period_,
              sizeof(uint32_t), ret);
   ret = hash_mix::mix((uint8_t *)&cipher_,
              sizeof(macsec_cipher_suite_t), ret);
   ret = hash_mix::mix((uint8_t *)&dot1x_,
              sizeof(bool), ret);
   ret = hash_mix::mix((uint8_t *)&include_sci_,
              sizeof(bool), ret);
   ret = hash_mix::mix((uint8_t *)&bypass_lldp_,
              sizeof(bool), ret);
   ret = hash_mix::mix((uint8_t *)&allow_unprotected_,
              sizeof(bool), ret);
   ret = hash_mix::mix((uint8_t *)&replay_protection_,
              sizeof(bool), ret);
   ret = hash_mix::mix((uint8_t *)&replay_protection_window_,
              sizeof(uint32_t), ret);
   ret = hash_mix::mix((uint8_t *)&key_retirement_immediate_,
              sizeof(bool), ret);
   for (auto it=intfs_.cbegin(); it!=intfs_.cend(); ++it) {
      ret = hash_mix::mix((uint8_t *)&(*it),
            sizeof(intf_id_t), ret);
   }
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
macsec_profile_t::to_string() const {
   std::ostringstream ss;
   ss << "macsec_profile_t(";
   ss << "name=" << name_;
   ss << ", primary_key=" << primary_key_;
   ss << ", fallback_key=" << fallback_key_;
   ss << ", key_server_priority=" << key_server_priority_;
   ss << ", rekey_period=" << rekey_period_;
   ss << ", cipher=" << cipher_;
   ss << ", dot1x=" << dot1x_;
   ss << ", include_sci=" << include_sci_;
   ss << ", bypass_lldp=" << bypass_lldp_;
   ss << ", allow_unprotected=" << allow_unprotected_;
   ss << ", replay_protection=" << replay_protection_;
   ss << ", replay_protection_window=" << replay_protection_window_;
   ss << ", key_retirement_immediate=" << key_retirement_immediate_;
   ss << ", intfs=" <<"'";
   bool first_intfs = true;
   for (auto it=intfs_.cbegin(); it!=intfs_.cend(); ++it) {
      if (first_intfs) {
         ss << (*it);
         first_intfs = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const macsec_profile_t& obj) {
   os << obj.to_string();
   return os;
}



inline macsec_intf_status_t::macsec_intf_status_t() :
      status_(MACSEC_NO_PROFILE) {
}

inline macsec_intf_key_status_t
macsec_intf_status_t::status() const {
   return status_;
}

inline void
macsec_intf_status_t::status_is(macsec_intf_key_status_t status) {
   status_ = status;
}

inline bool
macsec_intf_status_t::operator==(macsec_intf_status_t const & other) const {
   return status_ == other.status_;
}

inline bool
macsec_intf_status_t::operator!=(macsec_intf_status_t const & other) const {
   return !operator==(other);
}

inline bool
macsec_intf_status_t::operator<(macsec_intf_status_t const & other) const {
   if(status_ != other.status_) {
      return status_ < other.status_;
   }
   return false;
}

inline uint32_t
macsec_intf_status_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&status_,
              sizeof(macsec_intf_key_status_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
macsec_intf_status_t::to_string() const {
   std::ostringstream ss;
   ss << "macsec_intf_status_t(";
   ss << "status=" << status_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const macsec_intf_status_t& obj) {
   os << obj.to_string();
   return os;
}



inline macsec_intf_counters_t::macsec_intf_counters_t() :
      out_pkts_encrypted_(0), out_octets_encrypted_(0), in_pkts_decrypted_(0),
      in_octets_decrypted_(0), in_pkts_not_valid_(0) {
}

inline macsec_intf_counters_t::macsec_intf_counters_t(
         uint64_t out_pkts_encrypted, uint64_t out_octets_encrypted,
         uint64_t in_pkts_decrypted, uint64_t in_octets_decrypted,
         uint64_t in_pkts_not_valid) :
      out_pkts_encrypted_(out_pkts_encrypted),
      out_octets_encrypted_(out_octets_encrypted),
      in_pkts_decrypted_(in_pkts_decrypted),
      in_octets_decrypted_(in_octets_decrypted),
      in_pkts_not_valid_(in_pkts_not_valid) {
}

inline uint64_t
macsec_intf_counters_t::out_pkts_encrypted() const {
   return out_pkts_encrypted_;
}

inline uint64_t
macsec_intf_counters_t::out_octets_encrypted() const {
   return out_octets_encrypted_;
}

inline uint64_t
macsec_intf_counters_t::in_pkts_decrypted() const {
   return in_pkts_decrypted_;
}

inline uint64_t
macsec_intf_counters_t::in_octets_decrypted() const {
   return in_octets_decrypted_;
}

inline uint64_t
macsec_intf_counters_t::in_pkts_not_valid() const {
   return in_pkts_not_valid_;
}

inline bool
macsec_intf_counters_t::operator==(macsec_intf_counters_t const & other) const {
   return out_pkts_encrypted_ == other.out_pkts_encrypted_ &&
          out_octets_encrypted_ == other.out_octets_encrypted_ &&
          in_pkts_decrypted_ == other.in_pkts_decrypted_ &&
          in_octets_decrypted_ == other.in_octets_decrypted_ &&
          in_pkts_not_valid_ == other.in_pkts_not_valid_;
}

inline bool
macsec_intf_counters_t::operator!=(macsec_intf_counters_t const & other) const {
   return !operator==(other);
}

inline bool
macsec_intf_counters_t::operator<(macsec_intf_counters_t const & other) const {
   if(out_pkts_encrypted_ != other.out_pkts_encrypted_) {
      return out_pkts_encrypted_ < other.out_pkts_encrypted_;
   } else if(out_octets_encrypted_ != other.out_octets_encrypted_) {
      return out_octets_encrypted_ < other.out_octets_encrypted_;
   } else if(in_pkts_decrypted_ != other.in_pkts_decrypted_) {
      return in_pkts_decrypted_ < other.in_pkts_decrypted_;
   } else if(in_octets_decrypted_ != other.in_octets_decrypted_) {
      return in_octets_decrypted_ < other.in_octets_decrypted_;
   } else if(in_pkts_not_valid_ != other.in_pkts_not_valid_) {
      return in_pkts_not_valid_ < other.in_pkts_not_valid_;
   }
   return false;
}

inline uint32_t
macsec_intf_counters_t::hash() const {
   uint32_t ret = 0;
   ret = hash_mix::mix((uint8_t *)&out_pkts_encrypted_,
              sizeof(uint64_t), ret);
   ret = hash_mix::mix((uint8_t *)&out_octets_encrypted_,
              sizeof(uint64_t), ret);
   ret = hash_mix::mix((uint8_t *)&in_pkts_decrypted_,
              sizeof(uint64_t), ret);
   ret = hash_mix::mix((uint8_t *)&in_octets_decrypted_,
              sizeof(uint64_t), ret);
   ret = hash_mix::mix((uint8_t *)&in_pkts_not_valid_,
              sizeof(uint64_t), ret);
   ret = hash_mix::final_mix(ret);
   return ret;
}

inline std::string
macsec_intf_counters_t::to_string() const {
   std::ostringstream ss;
   ss << "macsec_intf_counters_t(";
   ss << "out_pkts_encrypted=" << out_pkts_encrypted_;
   ss << ", out_octets_encrypted=" << out_octets_encrypted_;
   ss << ", in_pkts_decrypted=" << in_pkts_decrypted_;
   ss << ", in_octets_decrypted=" << in_octets_decrypted_;
   ss << ", in_pkts_not_valid=" << in_pkts_not_valid_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const macsec_intf_counters_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_MACSEC_H
