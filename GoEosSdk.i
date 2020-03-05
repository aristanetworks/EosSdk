// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

%module(directors="1") eossdk

%include "stdint.i"
%include "std_list.i"
%include "std_map.i"
%include "std_pair.i"
//%include "std_set.i"
%include "std_string.i"
//%include "std_unordered_set.i"
%include "std_vector.i"
//%import "GoSwigUtils.i"
%include "typemaps.i"

// Change all some_class_t names to just SomeClass:
// The <<""< uses automatic string concatination to get around the
// conflict marker limitation.
%rename("%(command:python $SRCDIR/SwigRenamer.py --classname --go <<""<)s", %$isclass) "";
// Don't do anything for enum values, functions or variables.

// Cause SWIG to produce basic documentation in the generated eossdk.go
// For functions, the docstrings describe argument type and return types.
// All constructors are listed in the __init__ function for the type.
// These docstrings are later examined by sphinx.
%feature("autodoc", "1");

// Ignored conversions:

#define SWIG_FILE_WITH_INIT
%import "eos/base.h"

// Tell swig about our custom types (copied from base.h)
typedef double seconds_t;
typedef uint16_t uint16_be_t;
typedef uint32_t uint32_be_t;
typedef uint64_t uint64_be_t;

// %typemap(in) void *eossdk_context {
//    $1 = PyLong_AsVoidPtr($input);
// }

// To make sure instance of EosSdk types are hashable in python, this is important
// when the objects are used in sets, dicts, etc (as key).
// Three test cases added for this, one is in EthLagIntfTest.py, one in IntfTest.py
// and the third in IpAddrTest.py
%rename(__hash__) *::hash;

// for types:
%rename(IsEmpty) *::operator!;
%rename(IsEqual) *::operator==;
%rename(IsNotEqual) *::operator!=;
%rename(IsLessThan) *::operator<;

// generate directors for all classes that have virtual methods, except the managers
%feature("director");
%feature("nodirector") eos::acl_mgr;
%feature("nodirector") eos::agent_mgr;
%feature("nodirector") eos::aresolve_mgr;
%feature("nodirector") eos::bfd_session_mgr;
%feature("nodirector") eos::class_map_mgr;
%feature("nodirector") eos::decap_group_mgr;
%feature("nodirector") eos::directflow_mgr;
%feature("nodirector") eos::eapi_mgr;
%feature("nodirector") eos::eth_intf_mgr;
%feature("nodirector") eos::eth_lag_intf_mgr;
%feature("nodirector") eos::eth_phy_intf_mgr;
%feature("nodirector") eos::eth_phy_intf_counter_mgr;
%feature("nodirector") eos::fib_mgr;
%feature("nodirector") eos::hardware_table_mgr;
%feature("nodirector") eos::intf_mgr;
%feature("nodirector") eos::intf_counter_mgr;
%feature("nodirector") eos::ip_intf_mgr;
%feature("nodirector") eos::ip_route_mgr;
%feature("nodirector") eos::lldp_mgr;
%feature("nodirector") eos::macsec_mgr;
%feature("nodirector") eos::mac_table_mgr;
%feature("nodirector") eos::mlag_mgr;
%feature("nodirector") eos::mpls_route_mgr;
%feature("nodirector") eos::mpls_vrf_label_mgr;
%feature("nodirector") eos::neighbor_table_mgr;
%feature("nodirector") eos::nexthop_group_mgr;
%feature("nodirector") eos::nexthop_group_tunnel_mgr;
%feature("nodirector") eos::policy_map_mgr;
%feature("nodirector") eos::subintf_mgr;
%feature("nodirector") eos::system_mgr;
%feature("nodirector") eos::timeout_mgr;
%feature("nodirector") eos::vrf_mgr;

%{
//#include "eos/acl.h"
#include "eos/agent.h"
#include "eos/aresolve.h"
#include "eos/bfd.h"
#include "eos/event_loop.h"
#include "eos/class_map.h"
#include "eos/decap_group.h"
#include "eos/directflow.h"
#include "eos/eapi.h"
#include "eos/eth.h"
#include "eos/eth_intf.h"
#include "eos/eth_lag_intf.h"
#include "eos/eth_phy_intf.h"
#include "eos/exception.h"
#include "eos/fd.h"
#include "eos/fib.h"
#include "eos/hardware_table.h"
#include "eos/hash_mix.h"
#include "eos/intf.h"
#include "eos/ip.h"
#include "eos/ip_intf.h"
#include "eos/ip_route.h"
#include "eos/iterator.h"
#include "eos/lldp.h"
#include "eos/macsec.h"
#include "eos/mac_table.h"
#include "eos/mlag.h"
#include "eos/mpls.h"
#include "eos/mpls_route.h"
#include "eos/mpls_vrf_label.h"
#include "eos/neighbor_table.h"
#include "eos/nexthop_group.h"
#include "eos/nexthop_group_tunnel.h"
#include "eos/policy_map.h"
#include "eos/sdk.h"
#include "eos/subintf.h"
#include "eos/system.h"
#include "eos/timer.h"
#include "eos/tracing.h"
#include "eos/utility.h"
#include "eos/version.h"
#include "eos/vrf.h"

using namespace std;
using namespace eos;

%}

%include "eos/iterator.h"
//%include "GetAgentProcessName.cpp"

%typemap(throws) stop_iteration {
  (void)$1;
}

%define wrap_iterator(IteratorClass, IteratorImplClass, ReturnType)
   %ignore IteratorClass;
   %template() eos::iter_base<ReturnType, IteratorImplClass>;
   %extend IteratorClass {
      ReturnType next() {
         if(!*$self) {
            return ReturnType();
         }
         ReturnType result = $self->operator*();
         $self->operator++();
         return result;
      }
   }
%enddef

// Different stl containers used directly in our exposed headers
%template() std::map<uint32_t, eos::class_map_rule_t>;
%template() std::map<uint32_t, eos::policy_map_rule_t>;
%template() std::map<uint16_t, eos::ip_addr_t>;
//%template() std::set<eos::intf_id_t>;
//%template() std::set<eos::ip_addr_mask_t>;
%template() std::list<uint16_t>;
%template() std::list<eos::mpls_label_t>;
%template() std::map<uint16_t, eos::nexthop_group_mpls_action_t>;
%template() std::map<uint16_t, eos::nexthop_group_entry_t>;
%template() std::pair<uint32_t, eos::acl_rule_ip_t>;
%template() std::pair<uint32_t, eos::acl_rule_eth_t>;
//%template() std::unordered_set<eos::ip_addr_t>;
%template() std::map<eos::lldp_tlv_type_t, std::string>;
//%template() std::list<eos::lldp_management_address_t>;
%template() std::vector<std::string>;

// For vlan_set_t
// %template(_BitSet4096) std::bitset<4096>;

// Ignore the `raise' method of all exceptions.  `raise' is a Python keyword
// and also this method is used to throw the exception from C++ and is useless
// in Python.
//%ignore raise;
// Ignore the `what' method of all exceptions.  This method is redundant with
// the `msg' method (it's only provided for "compatibility" with standard
// exceptions).
//%ignore what;
// Python code should use Python exceptions, and not call panic().
//%ignore panic;
%ignore vpanic;
%include "Includes.i"

//%extend eos::error {
//   std::string const & __str__() {
//      return $self->msg();
//   }
//};

// Go nuts with our iterators.
wrap_iterator(eos::acl_iter_t, eos::acl_iter_impl, eos::acl_key_t);
wrap_iterator(eos::acl_rule_ip_iter_t, eos::acl_rule_ip_iter_impl, eos::acl_rule_ip_entry_t);
wrap_iterator(eos::acl_rule_eth_iter_t, eos::acl_rule_eth_iter_impl, eos::acl_rule_eth_entry_t);
wrap_iterator(eos::agent_option_iter_t, eos::agent_option_iter_impl, std::string);
wrap_iterator(eos::agent_status_iter_t, eos::agent_status_iter_impl, std::string);
wrap_iterator(eos::bfd_session_iter_t, eos::bfd_session_iter_impl, eos::bfd_session_key_t);
wrap_iterator(eos::class_map_iter_t, eos::class_map_iter_impl, eos::class_map_key_t);
wrap_iterator(eos::fib_fec_iter_t, eos::fib_fec_iter_impl, eos::fib_fec_t);
wrap_iterator(eos::fib_route_iter_t, eos::fib_route_iter_impl, eos::fib_route_t);
wrap_iterator(eos::flow_entry_iter_t, eos::flow_entry_iter_impl, eos::flow_entry_t);
wrap_iterator(eos::eth_intf_iter_t, eos::eth_intf_iter_impl, eos::intf_id_t);
wrap_iterator(eos::eth_lag_intf_iter_t, eos::eth_lag_intf_iter_impl, eos::intf_id_t);
wrap_iterator(eos::eth_lag_intf_member_iter_t, eos::eth_lag_intf_member_iter_impl, eos::intf_id_t);
wrap_iterator(eos::eth_phy_intf_iter_t, eos::eth_phy_intf_iter_impl, eos::intf_id_t);
wrap_iterator(eos::hardware_table_iter_t, eos::hardware_table_iter_impl, eos::hardware_table_key_t);
wrap_iterator(eos::intf_iter_t, eos::intf_iter_impl, eos::intf_id_t);
wrap_iterator(eos::ip_route_iter_t, eos::ip_route_iter_impl, eos::ip_route_t);
wrap_iterator(eos::ip_route_via_iter_t, eos::ip_route_via_iter_impl, eos::ip_route_via_t);
wrap_iterator(eos::decap_group_iter_t, eos::decap_group_iter_impl, eos::decap_group_t);
wrap_iterator(eos::lldp_remote_system_iter_t, eos::lldp_remote_system_iter_impl, lldp_remote_system_t);
wrap_iterator(eos::lldp_intf_iter_t, eos::lldp_intf_iter_impl, intf_id_t);
wrap_iterator(eos::lldp_neighbor_iter_t, eos::lldp_neighbor_iter_impl, lldp_neighbor_t);
wrap_iterator(eos::mac_table_iter_t, eos::mac_table_iter_impl, eos::mac_key_t);
wrap_iterator(eos::mac_table_status_iter_t, eos::mac_table_status_iter_impl, eos::mac_key_t);
wrap_iterator(eos::mpls_route_iter_t, eos::mpls_route_iter_impl, eos::mpls_route_t);
wrap_iterator(eos::mpls_route_status_iter_t, eos::mpls_route_status_iter_impl, eos::mpls_route_key_t);
wrap_iterator(eos::mpls_route_via_iter_t, eos::mpls_route_via_iter_impl, eos::mpls_route_via_t);
wrap_iterator(eos::mpls_route_via_status_iter_t, eos::mpls_route_via_status_iter_impl, eos::mpls_route_via_t);
wrap_iterator(eos::mpls_vrf_label_iter_t, eos::mpls_vrf_label_iter_impl, eos::mpls_vrf_label_t);
wrap_iterator(eos::neighbor_table_iter_t, eos::neighbor_table_iter_impl, eos::neighbor_key_t);
wrap_iterator(eos::neighbor_table_status_iter_t, eos::neighbor_table_status_iter_impl, eos::neighbor_key_t);
wrap_iterator(eos::nexthop_group_iter_t, eos::nexthop_group_iter_impl, eos::nexthop_group_t);
wrap_iterator(eos::nexthop_group_tunnel_iter_t, eos::nexthop_group_tunnel_iter_impl, eos::nexthop_group_tunnel_t);
wrap_iterator(eos::policy_map_iter_t, eos::policy_map_iter_impl, eos::policy_map_key_t);
wrap_iterator(eos::subintf_iter_t, eos::subintf_iter_impl, eos::intf_id_t);
wrap_iterator(eos::vrf_iter_t, eos::vrf_iter_impl, std::string);

/*
// Make managers themselves iterable, when it makes sense:
default_iterator(eos::directflow_mgr, flow_entry_iter);
default_iterator(eos::intf_mgr, intf_iter);
default_iterator(eos::ip_route_mgr, ip_route_iter);
default_iterator(eos::mpls_route_mgr, mpls_route_iter);
default_iterator(eos::subintf_mgr, subintf_iter);
*/
