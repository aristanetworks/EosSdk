// Copyright (c) 2024 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_EAPI_IMPL_H
#define EOS_INLINE_TYPES_EAPI_IMPL_H

namespace eos {

eapi_response_impl_t::eapi_response_impl_t() :
      success_(false), error_code_(0), error_message_(), responses_(),
      raw_response_() {
}

eapi_response_impl_t::eapi_response_impl_t(
         bool success, uint32_t error_code, std::string const & error_message,
         std::vector<std::string> const & responses) :
      success_(success), error_code_(error_code), error_message_(error_message),
      responses_(responses), raw_response_() {
}

bool
eapi_response_impl_t::success() const {
   return success_;
}

uint32_t
eapi_response_impl_t::error_code() const {
   return error_code_;
}

std::string
eapi_response_impl_t::error_message() const {
   return error_message_;
}

std::vector<std::string> const &
eapi_response_impl_t::responses() const {
   return responses_;
}

std::string
eapi_response_impl_t::raw_response() const {
   return raw_response_;
}

std::string
eapi_response_impl_t::to_string() const {
   std::ostringstream ss;
   ss << "eapi_response_t(";
   ss << "success=" << success_;
   ss << ", error_code=" << error_code_;
   ss << ", error_message='" << error_message_ << "'";
   ss << ", responses=" <<"'";
   bool first_responses = true;
   for (auto it=responses_.cbegin();
        it!=responses_.cend(); ++it) {
      if (first_responses) {
         ss << (*it);
         first_responses = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", raw_response='" << raw_response_ << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const eapi_response_impl_t& obj) {
   os << obj.to_string();
   return os;
}


}

#include <eos/inline/types/eapi.h>

#endif // EOS_INLINE_TYPES_EAPI_IMPL_H
