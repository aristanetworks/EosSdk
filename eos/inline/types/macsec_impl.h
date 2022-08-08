// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MACSEC_IMPL_H
#define EOS_INLINE_TYPES_MACSEC_IMPL_H

namespace eos {











macsec_key_impl_t::macsec_key_impl_t() :
      cak_(), ckn_(), encoded_(false) {
}

std::string
macsec_key_impl_t::cak() const {
   return cak_;
}

void
macsec_key_impl_t::cak_is(std::string cak) {
   cak_ = cak;
}

std::string
macsec_key_impl_t::ckn() const {
   return ckn_;
}

void
macsec_key_impl_t::ckn_is(std::string ckn) {
   ckn_ = ckn;
}

bool
macsec_key_impl_t::encoded() const {
   return encoded_;
}

void
macsec_key_impl_t::encoded_is(bool encoded) {
   encoded_ = encoded;
}

bool
macsec_key_impl_t::operator==(macsec_key_impl_t const & other) const {
   return cak_ == other.cak_ &&
          ckn_ == other.ckn_ &&
          encoded_ == other.encoded_;
}

bool
macsec_key_impl_t::operator!=(macsec_key_impl_t const & other) const {
   return !operator==(other);
}

bool
macsec_key_impl_t::operator<(macsec_key_impl_t const & other) const {
   if(cak_ != other.cak_) {
      return cak_ < other.cak_;
   } else if(ckn_ != other.ckn_) {
      return ckn_ < other.ckn_;
   } else if(encoded_ != other.encoded_) {
      return encoded_ < other.encoded_;
   }
   return false;
}

uint32_t
macsec_key_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
macsec_key_impl_t::mix_me(hash_mix & h) const {
   h.mix(cak_); // std::string
   h.mix(ckn_); // std::string
   h.mix(encoded_); // bool
}

std::string
macsec_key_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "macsec_key_t(";
   ss << "cak='" << cak_ << "'";
   ss << ", ckn='" << ckn_ << "'";
   ss << ", encoded=" << encoded_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const macsec_key_impl_t& obj) {
   os << obj.to_string();
   return os;
}



macsec_profile_impl_t::macsec_profile_impl_t() :
      name_(), primary_key_(), fallback_key_(), key_server_priority_(16),
      rekey_period_(0), mka_life_time_(6), cipher_(GCM_AES_XPN_128), dot1x_(false),
      include_sci_(false), bypass_lldp_(false), lldp_bypass_level_(BYPASS_NULL),
      traffic_policy_(TRAFFIC_POLICY_ACTIVE_SAK), replay_protection_(true),
      replay_protection_window_(0), key_retirement_immediate_(false), intfs_() {
}

macsec_profile_impl_t::macsec_profile_impl_t(macsec_profile_name_t name) :
      name_(name), primary_key_(), fallback_key_(), key_server_priority_(16),
      rekey_period_(0), mka_life_time_(6), cipher_(GCM_AES_XPN_128), dot1x_(false),
      include_sci_(false), bypass_lldp_(false), lldp_bypass_level_(BYPASS_NULL),
      traffic_policy_(TRAFFIC_POLICY_ACTIVE_SAK), replay_protection_(true),
      replay_protection_window_(0), key_retirement_immediate_(false), intfs_() {
}

macsec_profile_name_t
macsec_profile_impl_t::name() const {
   return name_;
}

void
macsec_profile_impl_t::name_is(macsec_profile_name_t name) {
   name_ = name;
}

macsec_key_t
macsec_profile_impl_t::primary_key() const {
   return primary_key_;
}

void
macsec_profile_impl_t::primary_key_is(macsec_key_t primary_key) {
   primary_key_ = primary_key;
}

macsec_key_t
macsec_profile_impl_t::fallback_key() const {
   return fallback_key_;
}

void
macsec_profile_impl_t::fallback_key_is(macsec_key_t fallback_key) {
   fallback_key_ = fallback_key;
}

uint8_t
macsec_profile_impl_t::key_server_priority() const {
   return key_server_priority_;
}

void
macsec_profile_impl_t::key_server_priority_is(uint8_t key_server_priority) {
   key_server_priority_ = key_server_priority;
}

uint32_t
macsec_profile_impl_t::rekey_period() const {
   return rekey_period_;
}

void
macsec_profile_impl_t::rekey_period_is(uint32_t rekey_period) {
   rekey_period_ = rekey_period;
}

uint32_t
macsec_profile_impl_t::mka_life_time() const {
   return mka_life_time_;
}

void
macsec_profile_impl_t::mka_life_time_is(uint32_t mka_life_time) {
   mka_life_time_ = mka_life_time;
}

macsec_cipher_suite_t
macsec_profile_impl_t::cipher() const {
   return cipher_;
}

void
macsec_profile_impl_t::cipher_is(macsec_cipher_suite_t cipher) {
   cipher_ = cipher;
}

bool
macsec_profile_impl_t::dot1x() const {
   return dot1x_;
}

void
macsec_profile_impl_t::dot1x_is(bool dot1x) {
   dot1x_ = dot1x;
}

bool
macsec_profile_impl_t::include_sci() const {
   return include_sci_;
}

void
macsec_profile_impl_t::include_sci_is(bool include_sci) {
   include_sci_ = include_sci;
}

bool
macsec_profile_impl_t::bypass_lldp() const {
                return !(lldp_bypass_level() == BYPASS_NULL);
}

void
macsec_profile_impl_t::bypass_lldp_is(bool bypass_lldp) {
                lldp_bypass_level_is(bypass_lldp ? BYPASS_AUTHORIZED : BYPASS_NULL);
}

macsec_bypass_t
macsec_profile_impl_t::lldp_bypass_level() const {
   return lldp_bypass_level_;
}

void
macsec_profile_impl_t::lldp_bypass_level_is(macsec_bypass_t lldp_bypass_level) {
   lldp_bypass_level_ = lldp_bypass_level;
}

macsec_profile_traffic_policy_t
macsec_profile_impl_t::traffic_policy() const {
   return traffic_policy_;
}

void
macsec_profile_impl_t::traffic_policy_is(
         macsec_profile_traffic_policy_t traffic_policy) {
   traffic_policy_ = traffic_policy;
}

bool
macsec_profile_impl_t::allow_unprotected() const {
   return traffic_policy() == TRAFFIC_POLICY_UNPROTECTED;
}

void
macsec_profile_impl_t::allow_unprotected_is(bool allow_unprotected) {
   traffic_policy_is(allow_unprotected ? TRAFFIC_POLICY_UNPROTECTED :
                                         TRAFFIC_POLICY_ACTIVE_SAK);
}

bool
macsec_profile_impl_t::replay_protection() const {
   return replay_protection_;
}

void
macsec_profile_impl_t::replay_protection_is(bool replay_protection) {
   replay_protection_ = replay_protection;
}

uint32_t
macsec_profile_impl_t::replay_protection_window() const {
   return replay_protection_window_;
}

void
macsec_profile_impl_t::replay_protection_window_is(
         uint32_t replay_protection_window) {
   replay_protection_window_ = replay_protection_window;
}

bool
macsec_profile_impl_t::key_retirement_immediate() const {
   return key_retirement_immediate_;
}

void
macsec_profile_impl_t::key_retirement_immediate_is(bool key_retirement_immediate) {
   key_retirement_immediate_ = key_retirement_immediate;
}

std::forward_list<intf_id_t> const &
macsec_profile_impl_t::intfs() const {
   return intfs_;
}

bool
macsec_profile_impl_t::operator==(macsec_profile_impl_t const & other) const {
   return name_ == other.name_ &&
          primary_key_ == other.primary_key_ &&
          fallback_key_ == other.fallback_key_ &&
          key_server_priority_ == other.key_server_priority_ &&
          rekey_period_ == other.rekey_period_ &&
          mka_life_time_ == other.mka_life_time_ &&
          cipher_ == other.cipher_ &&
          dot1x_ == other.dot1x_ &&
          include_sci_ == other.include_sci_ &&
          bypass_lldp_ == other.bypass_lldp_ &&
          lldp_bypass_level_ == other.lldp_bypass_level_ &&
          traffic_policy_ == other.traffic_policy_ &&
          replay_protection_ == other.replay_protection_ &&
          replay_protection_window_ == other.replay_protection_window_ &&
          key_retirement_immediate_ == other.key_retirement_immediate_ &&
          intfs_ == other.intfs_;
}

bool
macsec_profile_impl_t::operator!=(macsec_profile_impl_t const & other) const {
   return !operator==(other);
}

bool
macsec_profile_impl_t::operator<(macsec_profile_impl_t const & other) const {
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
   } else if(mka_life_time_ != other.mka_life_time_) {
      return mka_life_time_ < other.mka_life_time_;
   } else if(cipher_ != other.cipher_) {
      return cipher_ < other.cipher_;
   } else if(dot1x_ != other.dot1x_) {
      return dot1x_ < other.dot1x_;
   } else if(include_sci_ != other.include_sci_) {
      return include_sci_ < other.include_sci_;
   } else if(bypass_lldp_ != other.bypass_lldp_) {
      return bypass_lldp_ < other.bypass_lldp_;
   } else if(lldp_bypass_level_ != other.lldp_bypass_level_) {
      return lldp_bypass_level_ < other.lldp_bypass_level_;
   } else if(traffic_policy_ != other.traffic_policy_) {
      return traffic_policy_ < other.traffic_policy_;
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

uint32_t
macsec_profile_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
macsec_profile_impl_t::mix_me(hash_mix & h) const {
   h.mix(name_); // macsec_profile_name_t
   h.mix(primary_key_); // macsec_key_t
   h.mix(fallback_key_); // macsec_key_t
   h.mix(key_server_priority_); // uint8_t
   h.mix(rekey_period_); // uint32_t
   h.mix(mka_life_time_); // uint32_t
   h.mix(cipher_); // macsec_cipher_suite_t
   h.mix(dot1x_); // bool
   h.mix(include_sci_); // bool
   h.mix(bypass_lldp_); // bool
   h.mix(lldp_bypass_level_); // macsec_bypass_t
   h.mix(traffic_policy_); // macsec_profile_traffic_policy_t
   h.mix(replay_protection_); // bool
   h.mix(replay_protection_window_); // uint32_t
   h.mix(key_retirement_immediate_); // bool
   for (auto it=intfs_.cbegin(); it!=intfs_.cend(); ++it) {
      h.mix(*it); // intf_id_t
   }
}

std::string
macsec_profile_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "macsec_profile_t(";
   ss << "name=" << name_;
   ss << ", primary_key=" << primary_key_;
   ss << ", fallback_key=" << fallback_key_;
   ss << ", key_server_priority=" << key_server_priority_;
   ss << ", rekey_period=" << rekey_period_;
   ss << ", mka_life_time=" << mka_life_time_;
   ss << ", cipher=" << cipher_;
   ss << ", dot1x=" << dot1x_;
   ss << ", include_sci=" << include_sci_;
   ss << ", bypass_lldp=" << bypass_lldp_;
   ss << ", lldp_bypass_level=" << lldp_bypass_level_;
   ss << ", traffic_policy=" << traffic_policy_;
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

std::ostream&
operator<<(std::ostream& os, const macsec_profile_impl_t& obj) {
   os << obj.to_string();
   return os;
}



macsec_intf_status_impl_t::macsec_intf_status_impl_t() :
      status_(MACSEC_NO_PROFILE), key_status_(MACSEC_NO_PROFILE),
      traffic_status_(MACSEC_TRAFFIC_BLOCKED) {
}

macsec_intf_key_status_t
macsec_intf_status_impl_t::key_status() const {
   return key_status_;
}

macsec_intf_traffic_status_t
macsec_intf_status_impl_t::traffic_status() const {
   return traffic_status_;
}

void
macsec_intf_status_impl_t::status_is(macsec_intf_key_status_t status) {
   status_ = status;
}

macsec_intf_key_status_t
macsec_intf_status_impl_t::status() const {
   return status_;
}

bool
macsec_intf_status_impl_t::operator==(macsec_intf_status_impl_t const & other)
       const {
   return status_ == other.status_ &&
          key_status_ == other.key_status_ &&
          traffic_status_ == other.traffic_status_;
}

bool
macsec_intf_status_impl_t::operator!=(macsec_intf_status_impl_t const & other)
       const {
   return !operator==(other);
}

bool
macsec_intf_status_impl_t::operator<(macsec_intf_status_impl_t const & other)
       const {
   if(status_ != other.status_) {
      return status_ < other.status_;
   } else if(key_status_ != other.key_status_) {
      return key_status_ < other.key_status_;
   } else if(traffic_status_ != other.traffic_status_) {
      return traffic_status_ < other.traffic_status_;
   }
   return false;
}

uint32_t
macsec_intf_status_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
macsec_intf_status_impl_t::mix_me(hash_mix & h) const {
   h.mix(status_); // macsec_intf_key_status_t
   h.mix(key_status_); // macsec_intf_key_status_t
   h.mix(traffic_status_); // macsec_intf_traffic_status_t
}

std::string
macsec_intf_status_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "macsec_intf_status_t(";
   ss << "status=" << status_;
   ss << ", key_status=" << key_status_;
   ss << ", traffic_status=" << traffic_status_;
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const macsec_intf_status_impl_t& obj) {
   os << obj.to_string();
   return os;
}



macsec_intf_counters_impl_t::macsec_intf_counters_impl_t() :
      out_pkts_encrypted_(0), out_octets_encrypted_(0), in_pkts_decrypted_(0),
      in_octets_decrypted_(0), in_pkts_not_valid_(0) {
}

macsec_intf_counters_impl_t::macsec_intf_counters_impl_t(
         uint64_t out_pkts_encrypted, uint64_t out_octets_encrypted,
         uint64_t in_pkts_decrypted, uint64_t in_octets_decrypted,
         uint64_t in_pkts_not_valid) :
      out_pkts_encrypted_(out_pkts_encrypted),
      out_octets_encrypted_(out_octets_encrypted),
      in_pkts_decrypted_(in_pkts_decrypted),
      in_octets_decrypted_(in_octets_decrypted),
      in_pkts_not_valid_(in_pkts_not_valid) {
}

uint64_t
macsec_intf_counters_impl_t::out_pkts_encrypted() const {
   return out_pkts_encrypted_;
}

uint64_t
macsec_intf_counters_impl_t::out_octets_encrypted() const {
   return out_octets_encrypted_;
}

uint64_t
macsec_intf_counters_impl_t::in_pkts_decrypted() const {
   return in_pkts_decrypted_;
}

uint64_t
macsec_intf_counters_impl_t::in_octets_decrypted() const {
   return in_octets_decrypted_;
}

uint64_t
macsec_intf_counters_impl_t::in_pkts_not_valid() const {
   return in_pkts_not_valid_;
}

bool
macsec_intf_counters_impl_t::operator==(macsec_intf_counters_impl_t const & other)
       const {
   return out_pkts_encrypted_ == other.out_pkts_encrypted_ &&
          out_octets_encrypted_ == other.out_octets_encrypted_ &&
          in_pkts_decrypted_ == other.in_pkts_decrypted_ &&
          in_octets_decrypted_ == other.in_octets_decrypted_ &&
          in_pkts_not_valid_ == other.in_pkts_not_valid_;
}

bool
macsec_intf_counters_impl_t::operator!=(macsec_intf_counters_impl_t const & other)
       const {
   return !operator==(other);
}

bool
macsec_intf_counters_impl_t::operator<(macsec_intf_counters_impl_t const & other)
       const {
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

uint32_t
macsec_intf_counters_impl_t::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
macsec_intf_counters_impl_t::mix_me(hash_mix & h) const {
   h.mix(out_pkts_encrypted_); // uint64_t
   h.mix(out_octets_encrypted_); // uint64_t
   h.mix(in_pkts_decrypted_); // uint64_t
   h.mix(in_octets_decrypted_); // uint64_t
   h.mix(in_pkts_not_valid_); // uint64_t
}

std::string
macsec_intf_counters_impl_t::to_string() const {
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

std::ostream&
operator<<(std::ostream& os, const macsec_intf_counters_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/macsec.h>

#endif // EOS_INLINE_TYPES_MACSEC_IMPL_H
