// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <string>
#include <sstream>

#include "eos/exception.h"

namespace eos {

// This file contains non-inlined constructors because the constructors
// contain literal strings.  Should they be inlined, there would be one
// copy of each string used in each translation unit, which contributes
// to increased binary size.

invalid_argument_error::invalid_argument_error(
      std::string const & argument_name) noexcept
   : error(std::string("Invalid argument '" + argument_name + "'")),
   argument_name_(argument_name) {
}

invalid_argument_error::invalid_argument_error(
      std::string const & argument_name,
      std::string const & error_details) noexcept
   : error(std::string("Invalid argument '" + argument_name +
                       "': " + error_details)),
   argument_name_(argument_name) {
}

static inline std::string
invalid_range_error_msg(uint32_t min_valid, uint32_t max_valid) {
   std::stringstream str;
   str << "value is outside its valid range. min_valid = "
       << min_valid << ", max_valid = " << max_valid;
   return str.str();
}

invalid_range_error::invalid_range_error(std::string const & argument_name,
                                         uint32_t min_valid, uint32_t max_valid)
   noexcept
   : invalid_argument_error(argument_name,
                            invalid_range_error_msg(min_valid, max_valid)),
                            min_valid_(min_valid), max_valid_(max_valid) {
}
                             
static
inline std::string unconfigured_agent_error_msg(std::string const & agent_name) {
   std::stringstream str;
   str << "The agent " << agent_name.c_str() << " has not been configured. "
      "Ensure that the agent has been configured to run from the CLI and "
      "that the executable uses the same agent name.";
   return str.str();
}

unconfigured_agent_error::unconfigured_agent_error(std::string const & name) noexcept
   : configuration_error(unconfigured_agent_error_msg(name)), agent_name_(name) {
}

}
