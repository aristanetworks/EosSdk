// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/intf.h"

namespace eos {

intf_id_t::intf_id_t() : intfId_(0) {
}

intf_id_t::intf_id_t(uint32_t id) : intfId_(id) {
}

intf_id_t::intf_id_t(char const * intfname) : intfId_(0) {
   // TODO: No op impl.
}

intf_id_t::intf_id_t(const std::string & intfname) : intfId_(0) {
   // TODO: No op impl.
}

bool
intf_id_t::is_null0() const {
   return false;
}

intf_type_t
intf_id_t::intf_type() const {
   return INTF_TYPE_OTHER;
}

bool
intf_id_t::operator !() const {
   return intfId_;
}

bool
intf_id_t::operator==(intf_id_t const & other) const {
   return intfId_ == other.intfId_;
}

bool
intf_id_t::operator!=(intf_id_t const & other) const {
   return intfId_ != other.intfId_;
}

std::string
intf_id_t::to_string() const {
   return "NotImplemented";  // TODO: No op impl.
}

intf_handler::intf_handler() {
}

intf_handler::~intf_handler() {
}

void
intf_handler::watch_all_intfs(bool all) {
   watching_all_intfs_ = all;
}

void
intf_handler::on_intf_create(intf_id_t) {
   // TODO: No op impl.
}

void
intf_handler::on_intf_delete(intf_id_t) {
   // TODO: No op impl.
}

void
intf_handler::on_oper_status(intf_id_t, oper_status_t) {
   // TODO: No op impl.
}

void
intf_handler::on_admin_enabled(intf_id_t, bool) {
   // TODO: No op impl.
}

void
intf_mgr::intf_foreach(bool (*handler)(intf_id_t, void *), void *) {
   // TODO: No op impl.
}

void
intf_mgr::intf_foreach(bool (*handler)(intf_id_t, void *), void *,
                       intf_id_t bookmark) {
   // TODO: No op impl.
}

bool
intf_mgr::exists(intf_id_t) const {
   return false;  // TODO: No op impl.
}

bool
intf_mgr::admin_enabled(intf_id_t id) const {
   return false;  // TODO: No op impl.
}

void
intf_mgr::admin_enabled_is(intf_id_t id, bool enabled) {
   // TODO: No op impl.
}

void
intf_mgr::description_is(intf_id_t, char const *) {
   // TODO: No op impl.
}

oper_status_t intf_mgr::oper_status(intf_id_t) const {
   return INTF_OPER_NULL;  // TODO: No op impl.
}

intf_mgr::intf_mgr() {
   // TODO: No op impl.
}

class intf_mgr_impl : public intf_mgr {
 public:
   intf_mgr_impl() {
   }
};

intf_mgr * get_intf_mgr() {
   static intf_mgr_impl impl;
   return &impl;
}

}
