// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
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
      rekey_period_(0), cipher_(CIPHER_NULL), dot1x_(false), include_sci_(false) {
}

inline macsec_profile_t::macsec_profile_t(macsec_profile_name_t name) :
      name_(name), primary_key_(), fallback_key_(), key_server_priority_(16),
      rekey_period_(0), cipher_(GCM_AES_XPN_128), dot1x_(false),
      include_sci_(false) {
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
macsec_profile_t::operator==(macsec_profile_t const & other) const {
   return name_ == other.name_ &&
          primary_key_ == other.primary_key_ &&
          fallback_key_ == other.fallback_key_ &&
          key_server_priority_ == other.key_server_priority_ &&
          rekey_period_ == other.rekey_period_ &&
          cipher_ == other.cipher_ &&
          dot1x_ == other.dot1x_ &&
          include_sci_ == other.include_sci_;
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


}

#endif // EOS_INLINE_TYPES_MACSEC_H
