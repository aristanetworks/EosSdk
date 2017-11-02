// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TYPES_EAPI_H
#define EOS_TYPES_EAPI_H

#include <eos/utility.h>
#include <sstream>
#include <vector>

namespace eos {

/** An eAPI response from the Cli server. */
class eapi_response_t {
 public:
   /** Default constructor. */
   eapi_response_t();
   /** Full constructor. */
   eapi_response_t(bool success, uint32_t error_code,
                   std::string const & error_message,
                   std::vector<std::string> const & responses);

   /** Getter for 'success': indicates if a response was received. */
   bool success() const;

   /** Getter for 'error_code': error code from eAPI response. */
   uint32_t error_code() const;

   /** Getter for 'error_message': error message from response. */
   std::string error_message() const;

   /**
    * Getter for 'responses': the set of strings that constitute an eAPI response.
    */
   std::vector<std::string> const & responses() const;

   /** Getter for 'raw_response': raw eAPI response (if requested). */
   std::string raw_response() const;

   /** Returns a string representation of the current object's values. */
   std::string to_string() const;
   /**
    * A utility stream operator that adds a string representation of
    * eapi_response_t to the ostream.
    */
   friend std::ostream& operator<<(std::ostream& os, const eapi_response_t& obj);

 private:
   bool success_;
   uint32_t error_code_;
   std::string error_message_;
   std::vector<std::string> responses_;
   std::string raw_response_;
};
}

#include <eos/inline/types/eapi.h>

#endif // EOS_TYPES_EAPI_H
