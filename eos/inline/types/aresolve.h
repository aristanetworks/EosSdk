// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ARESOLVE_H
#define EOS_INLINE_TYPES_ARESOLVE_H

namespace eos {

inline aresolve_record_base::aresolve_record_base() :
      qname_(), last_refresh_(), valid_(), last_error_() {}

inline aresolve_record_base::~aresolve_record_base() {}

inline std::string
aresolve_record_base::qname() const {
   return qname_;
}

inline seconds_t
aresolve_record_base::last_refresh() const {
   return last_refresh_;
}

inline bool
aresolve_record_base::valid() const {
   return valid_;
}

inline int
aresolve_record_base::last_error() const {
   return last_error_;
}

inline std::string
aresolve_record_base::to_string() const {
   std::ostringstream ss;
   ss << "aresolve_record_base(";
   ss << "qname='" << qname_ << "'";
   ss << ", last_refresh=" << last_refresh_;
   ss << ", valid=" << valid_;
   ss << ", last_error=" << last_error_;
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const aresolve_record_base& obj) {
   os << obj.to_string();
   return os;
}



inline std::list<ip_addr_t> const &
aresolve_record_host::addr_v4() const {
   return addr_v4_;
}

inline std::list<ip_addr_t> const &
aresolve_record_host::addr_v6() const {
   return addr_v6_;
}

inline std::string
aresolve_record_host::to_string() const {
   std::ostringstream ss;
   ss << "aresolve_record_host(";
   ss << "addr_v4=" <<"'";
   bool first_addr_v4 = true;
   for (auto it=addr_v4_.cbegin(); it!=addr_v4_.cend(); ++it) {
      if (first_addr_v4) {
         ss << (*it).to_string();
         first_addr_v4 = false;
      } else {
         ss << "," << (*it).to_string();
      }
   }
   ss << "'";
   ss << ", addr_v6=" <<"'";
   bool first_addr_v6 = true;
   for (auto it=addr_v6_.cbegin(); it!=addr_v6_.cend(); ++it) {
      if (first_addr_v6) {
         ss << (*it).to_string();
         first_addr_v6 = false;
      } else {
         ss << "," << (*it).to_string();
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

inline std::ostream&
operator<<(std::ostream& os, const aresolve_record_host& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_ARESOLVE_H
