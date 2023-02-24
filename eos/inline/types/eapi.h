// Copyright (c) 2023 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_EAPI_H
#define EOS_INLINE_TYPES_EAPI_H

namespace eos {

eapi_response_t::eapi_response_t() {
   pimpl = std::shared_ptr<eapi_response_impl_t>(
      new eapi_response_impl_t()
   );
}
eapi_response_t::eapi_response_t(bool success, uint32_t error_code,
                                        std::string const & error_message,
                                        std::vector<std::string> const & responses) {
   pimpl = std::shared_ptr<eapi_response_impl_t>(
      new eapi_response_impl_t(
         success,
         error_code,
         error_message,
         responses
      )
   );
}
eapi_response_t::eapi_response_t(
   const eapi_response_t& other)
{
   pimpl = std::make_unique<eapi_response_impl_t>(
      eapi_response_impl_t(*other.pimpl));
}
eapi_response_t&
eapi_response_t::operator=(
   eapi_response_t const & other)
{
   pimpl = std::shared_ptr<eapi_response_impl_t>(
      new eapi_response_impl_t(*other.pimpl));
   return *this;
}

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
