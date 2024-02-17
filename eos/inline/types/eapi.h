// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_EAPI_H
#define EOS_INLINE_TYPES_EAPI_H

namespace eos {

bool
eapi_response_t::success() const {
   return pimpl->success();
}
uint32_t
eapi_response_t::error_code() const {
   return pimpl->error_code();
}
std::string
eapi_response_t::error_message() const {
   return pimpl->error_message();
}
std::vector<std::string> const &
eapi_response_t::responses() const {
   return pimpl->responses();
}
std::string
eapi_response_t::raw_response() const {
   return pimpl->raw_response();
}
std::string
eapi_response_t::to_string() const {
   return pimpl->to_string();
}
std::ostream&
operator<<(std::ostream& os, const eapi_response_t& obj) {
   return operator<<(os, *obj.pimpl);
}

}

#endif // EOS_INLINE_TYPES_EAPI_H
