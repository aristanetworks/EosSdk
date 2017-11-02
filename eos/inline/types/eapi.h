// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_EAPI_H
#define EOS_INLINE_TYPES_EAPI_H

namespace eos {

inline eapi_response_t::eapi_response_t() :
      success_(false), error_code_(0), error_message_(), responses_(),
      raw_response_() {
}

inline eapi_response_t::eapi_response_t(bool success, uint32_t error_code,
                                        std::string const & error_message,
                                        std::vector<std::string> const & responses) :
      success_(success), error_code_(error_code), error_message_(error_message),
      responses_(responses), raw_response_() {
}

inline bool
eapi_response_t::success() const {
   return success_;
}

inline uint32_t
eapi_response_t::error_code() const {
   return error_code_;
}

inline std::string
eapi_response_t::error_message() const {
   return error_message_;
}

inline std::vector<std::string> const &
eapi_response_t::responses() const {
   return responses_;
}

inline std::string
eapi_response_t::raw_response() const {
   return raw_response_;
}

inline std::string
eapi_response_t::to_string() const {
   std::ostringstream ss;
   ss << "eapi_response_t(";
   ss << "success=" << success_;
   ss << ", error_code=" << error_code_;
   ss << ", error_message='" << error_message_ << "'";
   ss << ", responses=" <<"'";
   bool first_responses = true;
   for (auto it=responses_.cbegin(); it!=responses_.cend(); ++it) {
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

inline std::ostream&
operator<<(std::ostream& os, const eapi_response_t& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_EAPI_H
