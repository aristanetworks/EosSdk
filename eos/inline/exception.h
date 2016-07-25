// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_EXCEPTION_H
#define EOS_INLINE_EXCEPTION_H

namespace eos {

inline
error::error(std::string const & msg) noexcept : msg_(msg) {
}

inline
error::~error() noexcept {
}

inline std::string const &
error::msg() const noexcept {
   return msg_;
}

inline const char *
error::what() const noexcept {
   return msg_.c_str();
}

inline
invalid_argument_error::~invalid_argument_error() noexcept {
}

inline void
invalid_argument_error::raise() const {
   throw *this;
}

inline std::string
invalid_argument_error::argument_name() const noexcept {
   return argument_name_;
}

inline
invalid_range_error::~invalid_range_error() noexcept {
}

inline void
invalid_range_error::raise() const {
   throw *this;
}

inline uint32_t
invalid_range_error::min_valid() const noexcept {
   return min_valid_;
}

inline uint32_t
invalid_range_error::max_valid() const noexcept {
   return max_valid_;
}

inline
configuration_error::configuration_error(std::string const & name) noexcept
   : error(name) {
}

inline
configuration_error::~configuration_error() noexcept {
}

inline void
configuration_error::raise() const {
   throw *this;
}

inline unconfigured_agent_error::~unconfigured_agent_error() noexcept {
}

inline void unconfigured_agent_error::raise() const {
   throw *this;
}

inline std::string unconfigured_agent_error::agent_name() const noexcept {
   return agent_name_;
}

inline
unsupported_error::unsupported_error(std::string const & msg) noexcept : error(msg) {
}

inline
unsupported_error::~unsupported_error() noexcept {
}

inline void
unsupported_error::raise() const {
   throw *this;
}

inline
no_scoped_lock_obtained_error::no_scoped_lock_obtained_error() noexcept : 
   error("eos::sdk_scoped_lock not grabbed when calling an api while "
         "multithreaded") {
}

inline
no_scoped_lock_obtained_error::~no_scoped_lock_obtained_error() noexcept {
}

inline void
no_scoped_lock_obtained_error::raise() const {
   throw *this;
}

}

#endif // EOS_INLINE_EXCEPTION_H
