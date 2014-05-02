// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_ARESOLVE_H
#define EOS_INLINE_ARESOLVE_H

namespace eos {

inline aresolve_record_base::aresolve_record_base() :
      qname_(), last_refresh_(), valid_(), last_error_() {}

inline aresolve_record_base::~aresolve_record_base() {}

inline std::string const & aresolve_record_base::qname() const {
   return qname_;
}

inline seconds_t aresolve_record_base::last_refresh() const {
   return last_refresh_;
}

inline bool aresolve_record_base::valid() const {
   return valid_;
}

inline int aresolve_record_base::last_error() const {
   return last_error_;
}

inline std::list<ip_addr_t> const & aresolve_record_host::addr_v4() const {
   return addr_v4_;
}

inline std::list<ip_addr_t> const & aresolve_record_host::addr_v6() const {
   return addr_v6_;
}

inline aresolve_mgr * aresolve_handler::get_aresolve_mgr() const {
   return mgr_;
}

}

#endif // EOS_INLINE_ARESOLVE_H
