// Copyright (c) 2022 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_MACSEC_H
#define EOS_INLINE_TYPES_MACSEC_H

namespace eos {

EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const macsec_cipher_suite_t & enum_val) {
   if (enum_val==CIPHER_NULL) {
      os << "CIPHER_NULL";
   } else if (enum_val==GCM_AES_128) {
      os << "GCM_AES_128";
   } else if (enum_val==GCM_AES_256) {
      os << "GCM_AES_256";
   } else if (enum_val==GCM_AES_XPN_128) {
      os << "GCM_AES_XPN_128";
   } else if (enum_val==GCM_AES_XPN_256) {
      os << "GCM_AES_XPN_256";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const macsec_intf_key_status_t & enum_val) {
   if (enum_val==MACSEC_NO_PROFILE) {
      os << "MACSEC_NO_PROFILE";
   } else if (enum_val==MACSEC_KEY_NONE) {
      os << "MACSEC_KEY_NONE";
   } else if (enum_val==MACSEC_KEY_PRIMARY) {
      os << "MACSEC_KEY_PRIMARY";
   } else if (enum_val==MACSEC_KEY_FALLBACK) {
      os << "MACSEC_KEY_FALLBACK";
   } else if (enum_val==MACSEC_KEY_PRIMARY_CACHED) {
      os << "MACSEC_KEY_PRIMARY_CACHED";
   } else if (enum_val==MACSEC_KEY_FALLBACK_CACHED) {
      os << "MACSEC_KEY_FALLBACK_CACHED";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const macsec_intf_traffic_status_t & enum_val) {
   if (enum_val==MACSEC_TRAFFIC_PROTECTED) {
      os << "MACSEC_TRAFFIC_PROTECTED";
   } else if (enum_val==MACSEC_TRAFFIC_UNPROTECTED) {
      os << "MACSEC_TRAFFIC_UNPROTECTED";
   } else if (enum_val==MACSEC_TRAFFIC_BLOCKED) {
      os << "MACSEC_TRAFFIC_BLOCKED";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const macsec_bypass_t & enum_val) {
   if (enum_val==BYPASS_NULL) {
      os << "BYPASS_NULL";
   } else if (enum_val==BYPASS_AUTHORIZED) {
      os << "BYPASS_AUTHORIZED";
   } else if (enum_val==BYPASS_UNAUTHORIZED) {
      os << "BYPASS_UNAUTHORIZED";
   } else {
      os << "Unknown value";
   }
   return os;
}


EOS_SDK_PUBLIC std::ostream&
operator<<(std::ostream& os, const macsec_profile_traffic_policy_t & enum_val) {
   if (enum_val==TRAFFIC_POLICY_NULL) {
      os << "TRAFFIC_POLICY_NULL";
   } else if (enum_val==TRAFFIC_POLICY_ACTIVE_SAK) {
      os << "TRAFFIC_POLICY_ACTIVE_SAK";
   } else if (enum_val==TRAFFIC_POLICY_UNPROTECTED) {
      os << "TRAFFIC_POLICY_UNPROTECTED";
   } else if (enum_val==TRAFFIC_POLICY_BLOCKED) {
      os << "TRAFFIC_POLICY_BLOCKED";
   } else {
      os << "Unknown value";
   }
   return os;
}


macsec_key_t::macsec_key_t() {
   pimpl = std::shared_ptr<macsec_key_impl_t>(
      new macsec_key_impl_t()
   );
}
macsec_key_t::macsec_key_t(
   const macsec_key_t& other)
{
   pimpl = std::make_unique<macsec_key_impl_t>(
      macsec_key_impl_t(*other.pimpl));
}
macsec_key_t&
macsec_key_t::operator=(
   macsec_key_t const & other)
{
   pimpl = std::shared_ptr<macsec_key_impl_t>(
      new macsec_key_impl_t(*other.pimpl));
   return *this;
}

std::string
macsec_key_t::cak() const {
   return pimpl->cak();
}
void
macsec_key_t::cak_is(std::string cak) {
   pimpl->cak_is(cak);
}
std::string
macsec_key_t::ckn() const {
   return pimpl->ckn();
}
void
macsec_key_t::ckn_is(std::string ckn) {
   pimpl->ckn_is(ckn);
}
bool
macsec_key_t::encoded() const {
   return pimpl->encoded();
}
void
macsec_key_t::encoded_is(bool encoded) {
   pimpl->encoded_is(encoded);
}
bool
macsec_key_t::operator==(macsec_key_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
macsec_key_t::operator!=(macsec_key_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
macsec_key_t::operator<(macsec_key_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
macsec_key_t::hash() const {
   return pimpl->hash();
}
void
macsec_key_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
macsec_key_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const macsec_key_t& obj) {
   return operator<<(os, *obj.pimpl);
}


macsec_profile_t::macsec_profile_t() {
   pimpl = std::shared_ptr<macsec_profile_impl_t>(
      new macsec_profile_impl_t()
   );
}
macsec_profile_t::macsec_profile_t(macsec_profile_name_t name) {
   pimpl = std::shared_ptr<macsec_profile_impl_t>(
      new macsec_profile_impl_t(
         name
      )
   );
}
macsec_profile_t::macsec_profile_t(
   const macsec_profile_t& other)
{
   pimpl = std::make_unique<macsec_profile_impl_t>(
      macsec_profile_impl_t(*other.pimpl));
}
macsec_profile_t&
macsec_profile_t::operator=(
   macsec_profile_t const & other)
{
   pimpl = std::shared_ptr<macsec_profile_impl_t>(
      new macsec_profile_impl_t(*other.pimpl));
   return *this;
}

macsec_profile_name_t
macsec_profile_t::name() const {
   return pimpl->name();
}
void
macsec_profile_t::name_is(macsec_profile_name_t name) {
   pimpl->name_is(name);
}
macsec_key_t
macsec_profile_t::primary_key() const {
   return pimpl->primary_key();
}
void
macsec_profile_t::primary_key_is(macsec_key_t primary_key) {
   pimpl->primary_key_is(primary_key);
}
macsec_key_t
macsec_profile_t::fallback_key() const {
   return pimpl->fallback_key();
}
void
macsec_profile_t::fallback_key_is(macsec_key_t fallback_key) {
   pimpl->fallback_key_is(fallback_key);
}
uint8_t
macsec_profile_t::key_server_priority() const {
   return pimpl->key_server_priority();
}
void
macsec_profile_t::key_server_priority_is(uint8_t key_server_priority) {
   pimpl->key_server_priority_is(key_server_priority);
}
uint32_t
macsec_profile_t::rekey_period() const {
   return pimpl->rekey_period();
}
void
macsec_profile_t::rekey_period_is(uint32_t rekey_period) {
   pimpl->rekey_period_is(rekey_period);
}
uint32_t
macsec_profile_t::mka_life_time() const {
   return pimpl->mka_life_time();
}
void
macsec_profile_t::mka_life_time_is(uint32_t mka_life_time) {
   pimpl->mka_life_time_is(mka_life_time);
}
macsec_cipher_suite_t
macsec_profile_t::cipher() const {
   return pimpl->cipher();
}
void
macsec_profile_t::cipher_is(macsec_cipher_suite_t cipher) {
   pimpl->cipher_is(cipher);
}
bool
macsec_profile_t::dot1x() const {
   return pimpl->dot1x();
}
void
macsec_profile_t::dot1x_is(bool dot1x) {
   pimpl->dot1x_is(dot1x);
}
bool
macsec_profile_t::include_sci() const {
   return pimpl->include_sci();
}
void
macsec_profile_t::include_sci_is(bool include_sci) {
   pimpl->include_sci_is(include_sci);
}
bool
macsec_profile_t::bypass_lldp() const {
   return pimpl->bypass_lldp();
}
void
macsec_profile_t::bypass_lldp_is(bool bypass_lldp) {
   pimpl->bypass_lldp_is(bypass_lldp);
}
macsec_bypass_t
macsec_profile_t::lldp_bypass_level() const {
   return pimpl->lldp_bypass_level();
}
void
macsec_profile_t::lldp_bypass_level_is(macsec_bypass_t lldp_bypass_level) {
   pimpl->lldp_bypass_level_is(lldp_bypass_level);
}
macsec_profile_traffic_policy_t
macsec_profile_t::traffic_policy() const {
   return pimpl->traffic_policy();
}
void
macsec_profile_t::traffic_policy_is(macsec_profile_traffic_policy_t traffic_policy)
       {
   pimpl->traffic_policy_is(traffic_policy);
}
bool
macsec_profile_t::allow_unprotected() const {
   return pimpl->allow_unprotected();
}
void
macsec_profile_t::allow_unprotected_is(bool allow_unprotected) {
   pimpl->allow_unprotected_is(allow_unprotected);
}
bool
macsec_profile_t::replay_protection() const {
   return pimpl->replay_protection();
}
void
macsec_profile_t::replay_protection_is(bool replay_protection) {
   pimpl->replay_protection_is(replay_protection);
}
uint32_t
macsec_profile_t::replay_protection_window() const {
   return pimpl->replay_protection_window();
}
void
macsec_profile_t::replay_protection_window_is(uint32_t replay_protection_window) {
   pimpl->replay_protection_window_is(replay_protection_window);
}
bool
macsec_profile_t::key_retirement_immediate() const {
   return pimpl->key_retirement_immediate();
}
void
macsec_profile_t::key_retirement_immediate_is(bool key_retirement_immediate) {
   pimpl->key_retirement_immediate_is(key_retirement_immediate);
}
std::forward_list<intf_id_t> const &
macsec_profile_t::intfs() const {
   return pimpl->intfs();
}
bool
macsec_profile_t::operator==(macsec_profile_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
macsec_profile_t::operator!=(macsec_profile_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
macsec_profile_t::operator<(macsec_profile_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
macsec_profile_t::hash() const {
   return pimpl->hash();
}
void
macsec_profile_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
macsec_profile_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const macsec_profile_t& obj) {
   return operator<<(os, *obj.pimpl);
}


macsec_intf_status_t::macsec_intf_status_t() {
   pimpl = std::shared_ptr<macsec_intf_status_impl_t>(
      new macsec_intf_status_impl_t()
   );
}
macsec_intf_status_t::macsec_intf_status_t(
   const macsec_intf_status_t& other)
{
   pimpl = std::make_unique<macsec_intf_status_impl_t>(
      macsec_intf_status_impl_t(*other.pimpl));
}
macsec_intf_status_t&
macsec_intf_status_t::operator=(
   macsec_intf_status_t const & other)
{
   pimpl = std::shared_ptr<macsec_intf_status_impl_t>(
      new macsec_intf_status_impl_t(*other.pimpl));
   return *this;
}

macsec_intf_key_status_t
macsec_intf_status_t::key_status() const {
   return pimpl->key_status();
}
macsec_intf_traffic_status_t
macsec_intf_status_t::traffic_status() const {
   return pimpl->traffic_status();
}
void
macsec_intf_status_t::status_is(macsec_intf_key_status_t status) {
   pimpl->status_is(status);
}
macsec_intf_key_status_t
macsec_intf_status_t::status() const {
   return pimpl->status();
}
bool
macsec_intf_status_t::operator==(macsec_intf_status_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
macsec_intf_status_t::operator!=(macsec_intf_status_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
macsec_intf_status_t::operator<(macsec_intf_status_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
macsec_intf_status_t::hash() const {
   return pimpl->hash();
}
void
macsec_intf_status_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
macsec_intf_status_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const macsec_intf_status_t& obj) {
   return operator<<(os, *obj.pimpl);
}


macsec_intf_counters_t::macsec_intf_counters_t() {
   pimpl = std::shared_ptr<macsec_intf_counters_impl_t>(
      new macsec_intf_counters_impl_t()
   );
}
macsec_intf_counters_t::macsec_intf_counters_t(
         uint64_t out_pkts_encrypted, uint64_t out_octets_encrypted,
         uint64_t in_pkts_decrypted, uint64_t in_octets_decrypted,
         uint64_t in_pkts_not_valid) {
   pimpl = std::shared_ptr<macsec_intf_counters_impl_t>(
      new macsec_intf_counters_impl_t(
         out_pkts_encrypted,
         out_octets_encrypted,
         in_pkts_decrypted,
         in_octets_decrypted,
         in_pkts_not_valid
      )
   );
}
macsec_intf_counters_t::macsec_intf_counters_t(
   const macsec_intf_counters_t& other)
{
   pimpl = std::make_unique<macsec_intf_counters_impl_t>(
      macsec_intf_counters_impl_t(*other.pimpl));
}
macsec_intf_counters_t&
macsec_intf_counters_t::operator=(
   macsec_intf_counters_t const & other)
{
   pimpl = std::shared_ptr<macsec_intf_counters_impl_t>(
      new macsec_intf_counters_impl_t(*other.pimpl));
   return *this;
}

uint64_t
macsec_intf_counters_t::out_pkts_encrypted() const {
   return pimpl->out_pkts_encrypted();
}
uint64_t
macsec_intf_counters_t::out_octets_encrypted() const {
   return pimpl->out_octets_encrypted();
}
uint64_t
macsec_intf_counters_t::in_pkts_decrypted() const {
   return pimpl->in_pkts_decrypted();
}
uint64_t
macsec_intf_counters_t::in_octets_decrypted() const {
   return pimpl->in_octets_decrypted();
}
uint64_t
macsec_intf_counters_t::in_pkts_not_valid() const {
   return pimpl->in_pkts_not_valid();
}
bool
macsec_intf_counters_t::operator==(macsec_intf_counters_t const & other) const {
   return pimpl->operator==(*other.pimpl);
}
bool
macsec_intf_counters_t::operator!=(macsec_intf_counters_t const & other) const {
   return pimpl->operator!=(*other.pimpl);
}
bool
macsec_intf_counters_t::operator<(macsec_intf_counters_t const & other) const {
   return pimpl->operator<(*other.pimpl);
}
uint32_t
macsec_intf_counters_t::hash() const {
   return pimpl->hash();
}
void
macsec_intf_counters_t::mix_me(hash_mix & h) const {
   pimpl->mix_me(h);
}
std::string
macsec_intf_counters_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const macsec_intf_counters_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_MACSEC_H
