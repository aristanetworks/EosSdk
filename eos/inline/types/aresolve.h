// Copyright (c) 2025 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_INLINE_TYPES_ARESOLVE_H
#define EOS_INLINE_TYPES_ARESOLVE_H

namespace eos {

aresolve_record_base::aresolve_record_base() :
      qname_(), last_refresh_(), valid_(), last_error_() {}

aresolve_record_base::~aresolve_record_base() {}

std::string
aresolve_record_base::qname() const {
   return qname_;
}

seconds_t
aresolve_record_base::last_refresh() const {
   return last_refresh_;
}

bool
aresolve_record_base::valid() const {
   return valid_;
}

int
aresolve_record_base::last_error() const {
   return last_error_;
}

uint32_t
aresolve_record_base::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
aresolve_record_base::mix_me(hash_mix & h) const {
   h.mix(qname_); // std::string
   h.mix(last_refresh_); // seconds_t
   h.mix(valid_); // bool
   h.mix(last_error_); // int
}

std::string
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

std::ostream&
operator<<(std::ostream& os, const aresolve_record_base& obj) {
   os << obj.to_string();
   return os;
}



std::list<ip_addr_t> const &
aresolve_record_host::addr_v4() const {
   return addr_v4_;
}

std::list<ip_addr_t> const &
aresolve_record_host::addr_v6() const {
   return addr_v6_;
}

uint32_t
aresolve_record_host::hash() const {
   hash_mix h;
   mix_me(h);
   return h.result();
}

void
aresolve_record_host::mix_me(hash_mix & h) const {
   for (auto it=addr_v4_.cbegin();
        it!=addr_v4_.cend(); ++it) {
      h.mix(*it); // ip_addr_t
   }
   for (auto it=addr_v6_.cbegin();
        it!=addr_v6_.cend(); ++it) {
      h.mix(*it); // ip_addr_t
   }
}

std::string
aresolve_record_host::to_string() const {
   std::ostringstream ss;
   ss << "aresolve_record_host(";
   ss << "addr_v4=" <<"'";
   bool first_addr_v4 = true;
   for (auto it=addr_v4_.cbegin();
        it!=addr_v4_.cend(); ++it) {
      if (first_addr_v4) {
         ss << (*it);
         first_addr_v4 = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ", addr_v6=" <<"'";
   bool first_addr_v6 = true;
   for (auto it=addr_v6_.cbegin();
        it!=addr_v6_.cend(); ++it) {
      if (first_addr_v6) {
         ss << (*it);
         first_addr_v6 = false;
      } else {
         ss << "," << (*it);
      }
   }
   ss << "'";
   ss << ")";
   return ss.str();
}

std::ostream&
operator<<(std::ostream& os, const aresolve_record_host& obj) {
   os << obj.to_string();
   return os;
}


}

#endif // EOS_INLINE_TYPES_ARESOLVE_H
