// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

%module(directors="1") eossdk

%include "stdint.i"
%include "std_list.i"
%include "std_map.i"
%include "std_set.i"
%include "std_string.i"
%include "std_vector.i"
%import "SwigUtils.i"

// Change all some_class_t names to just SomeClass:
 // The <<""< uses automatic string concatination to get around the
 // conflict marker limitation.
%rename("%(command:python $SRCDIR/SwigRenamer.py --classname <<""<)s", %$isclass) "";
// Don't do anything for enum values, functions or variables.

// Cause SWIG to produce basic documentation in the generated eossdk.py
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

// generate directors for all classes that have virtual methods, except the managers
%feature("director");
%feature("nodirector") eos::acl_mgr;
%feature("nodirector") eos::agent_mgr;
%feature("nodirector") eos::aresolve_mgr;
%feature("nodirector") eos::class_map_mgr;
%feature("nodirector") eos::decap_group_mgr;
%feature("nodirector") eos::directflow_mgr;
%feature("nodirector") eos::eth_intf_mgr;
%feature("nodirector") eos::eth_lag_intf_mgr;
%feature("nodirector") eos::eth_phy_intf_mgr;
%feature("nodirector") eos::eth_phy_intf_counter_mgr;
%feature("nodirector") eos::fib_mgr;
%feature("nodirector") eos::intf_mgr;
%feature("nodirector") eos::intf_counter_mgr;
%feature("nodirector") eos::ip_intf_mgr;
%feature("nodirector") eos::ip_route_mgr;
%feature("nodirector") eos::mac_table_mgr;
%feature("nodirector") eos::mlag_mgr;
%feature("nodirector") eos::mpls_route_mgr;
%feature("nodirector") eos::neighbor_table_mgr;
%feature("nodirector") eos::nexthop_group_mgr;
%feature("nodirector") eos::policy_map_mgr;
%feature("nodirector") eos::system_mgr;
%feature("nodirector") eos::timeout_mgr;

%{
#include "eos/acl.h"
#include "eos/agent.h"
#include "eos/aresolve.h"
#include "eos/event_loop.h"
#include "eos/class_map.h"
#include "eos/decap_group.h"
#include "eos/directflow.h"
#include "eos/eth.h"
#include "eos/eth_intf.h"
#include "eos/eth_lag_intf.h"
#include "eos/eth_phy_intf.h"
#include "eos/exception.h"
#include "eos/fd.h"
#include "eos/fib.h"
#include "eos/hash_mix.h"
#include "eos/intf.h"
#include "eos/ip.h"
#include "eos/ip_intf.h"
#include "eos/ip_route.h"
#include "eos/iterator.h"
#include "eos/neighbor_table.h"
#include "eos/nexthop_group.h"
#include "eos/mac_table.h"
#include "eos/mlag.h"
#include "eos/mpls.h"
#include "eos/mpls_route.h"
#include "eos/policy_map.h"
#include "eos/sdk.h"
#include "eos/system.h"
#include "eos/timer.h"
#include "eos/tracing.h"
#include "eos/utility.h"
#include "eos/version.h"

using namespace eos;

/// Used to convert uncaught exceptions into Python exceptions.
class misc_error : public error {
 public:
   virtual ~misc_error() noexcept {
   }
   explicit misc_error(std::string const & msg) noexcept : error(msg) {
   }
   virtual void raise() const EOS_SDK_NORETURN {
      throw *this;
   }
};

struct stop_iteration {};

#define TRANSLATE_EXCEPTION(ExceptionClass)\
   catch(ExceptionClass const & e) {\
      ExceptionClass * exc = new ExceptionClass(e);\
      PyObject * obj = SWIG_NewPointerObj(exc, SWIGTYPE_p_eos__##ExceptionClass,\
                                          SWIG_POINTER_OWN);\
      PyErr_SetObject(SWIG_Python_ExceptionType(SWIGTYPE_p_eos__##ExceptionClass), obj);\
   }

void throw_py_error(error const& err) {
   try {
      err.raise();
   }
   TRANSLATE_EXCEPTION(invalid_range_error)
   TRANSLATE_EXCEPTION(invalid_argument_error)
   TRANSLATE_EXCEPTION(no_such_interface_error)
   TRANSLATE_EXCEPTION(not_switchport_eligible_error)
   TRANSLATE_EXCEPTION(invalid_vlan_error)
   TRANSLATE_EXCEPTION(internal_vlan_error)
   TRANSLATE_EXCEPTION(unsupported_policy_feature_error)
   TRANSLATE_EXCEPTION(address_overlap_error)
   catch(error const & e) {
      misc_error * exc = new misc_error(e.msg());
      PyObject * obj = SWIG_NewPointerObj(exc, SWIGTYPE_p_eos__error,
                                          SWIG_POINTER_OWN);
      PyErr_SetObject(SWIG_Python_ExceptionType(SWIGTYPE_p_eos__error), obj);
   }
}

%}

%exceptionclass error;

%exception {
   try {
      $action
   } catch (error const & e) {
      throw_py_error(e);
      SWIG_fail;
   }
}

%typemap(throws) stop_iteration {
  (void)$1;
  SWIG_SetErrorObj(PyExc_StopIteration, SWIG_Py_Void());
  SWIG_fail;
}

%include "eos/iterator.h"

%define wrap_iterator(IteratorClass, IteratorImplClass, ReturnType)
   %template() eos::iter_base<ReturnType, IteratorImplClass>;
   %extend IteratorClass {
      // Note: __next__() is needed for Python 3.x, so we alias it to next().
      %pythoncode {
         def __iter__(self): return self
         def __next__(self): return self.next()
      }
      ReturnType next() throw(stop_iteration) {
         SWIG_PYTHON_THREAD_BEGIN_BLOCK;
         if(!*$self) {
            throw stop_iteration();
         }
         ReturnType result = $self->operator*();
         $self->operator++();
         SWIG_PYTHON_THREAD_END_BLOCK;
         return result;
      }
   }
%enddef

%define default_iterator(ManagerClass, IteratorMethod)
   %extend ManagerClass {
      %pythoncode {
         def __iter__(self): return self.IteratorMethod()
      }
   }
%enddef

// Different stl containers used directly in our exposed headers
%template() std::map<uint32_t, eos::class_map_rule_t>;
%template() std::map<uint32_t, eos::policy_map_rule_t>;
%template() std::map<uint16_t, eos::ip_addr_t>;
%template() std::set<eos::intf_id_t>;
%template() std::set<eos::ip_addr_mask_t>;
%template() std::list<uint16_t>;
%template() std::list<eos::mpls_label_t>;
%template() std::map<uint16_t, eos::nexthop_group_mpls_action_t>;
%template() std::map<uint16_t, eos::nexthop_group_entry_t>;

// For vlan_set
%template(_BitSet4096) std::bitset<4096>;

// Ignore the `raise' method of all exceptions.  `raise' is a Python keyword
// and also this method is used to throw the exception from C++ and is useless
// in Python.
%ignore raise;
// Ignore the `what' method of all exceptions.  This method is redundant with
// the `msg' method (it's only provided for "compatibility" with standard
// exceptions).
%ignore what;
// THIS LIST IS IN A TOPOLOGICAL ORDER. DO NOT ALPHABETIZE.
%include "eos/agent.h"
%include "eos/hash_mix.h"
%include "eos/exception.h"
%include "eos/types/eth.h"
%include "eos/eth.h"
%include "eos/event_loop.h"
%include "eos/fd.h"
%include "eos/iterator.h"
%include "eos/types/intf.h"
%include "eos/intf.h"
%include "eos/types/ip.h"
%include "eos/ip.h"
%include "eos/types/acl.h"
%include "eos/acl.h"
%include "eos/types/aresolve.h"
%include "eos/aresolve.h"
%include "eos/types/directflow.h"
%include "eos/directflow.h"
%include "eos/ip_intf.h"
%include "eos/types/decap_group.h"
%include "eos/decap_group.h"
%include "eos/eth_intf.h"
%include "eos/types/eth_lag_intf.h"
%include "eos/eth_lag_intf.h"
%include "eos/types/eth_phy_intf.h"
%include "eos/eth_phy_intf.h"
%include "eos/types/fib.h"
%include "eos/fib.h"
%include "eos/types/neighbor_table.h"
%include "eos/neighbor_table.h"
%include "eos/types/nexthop_group.h"
%include "eos/nexthop_group.h"
%include "eos/types/mac_table.h"
%include "eos/mac_table.h"
%include "eos/types/mlag.h"
%include "eos/mlag.h"
%include "eos/types/mpls.h"
%include "eos/mpls.h"
%include "eos/types/ip_route.h"
%include "eos/ip_route.h"
%include "eos/types/mpls_route.h"
%include "eos/mpls_route.h"
%include "eos/types/policy_map.h"
%include "eos/policy_map.h"
%include "eos/types/class_map.h"
%include "eos/class_map.h"
%include "eos/sdk.h"
%include "eos/system.h"
%include "eos/timer.h"
%include "eos/tracing.h"
%include "eos/utility.h"
%include "eos/version.h"


%extend eos::error {
   std::string const & __str__() {
      return $self->msg();
   }
};

// Pythonify our iterators.
wrap_iterator(eos::acl_iter_t, eos::acl_iter_impl, eos::acl_key_t);
wrap_iterator(eos::acl_rule_ip_iter_t, eos::acl_rule_ip_iter_impl, eos::acl_rule_ip_entry_t);
wrap_iterator(eos::acl_rule_eth_iter_t, eos::acl_rule_eth_iter_impl, eos::acl_rule_eth_entry_t);
wrap_iterator(eos::class_map_iter_t, eos::class_map_iter_impl, eos::class_map_key_t);
wrap_iterator(eos::flow_entry_iter_t, eos::flow_entry_iter_impl, eos::flow_entry_t);
wrap_iterator(eos::eth_intf_iter_t, eos::eth_intf_iter_impl, eos::intf_id_t);
wrap_iterator(eos::eth_lag_intf_iter_t, eos::eth_lag_intf_iter_impl, eos::intf_id_t);
wrap_iterator(eos::eth_lag_intf_member_iter_t, eos::eth_lag_intf_member_iter_impl, eos::intf_id_t);
wrap_iterator(eos::eth_phy_intf_iter_t, eos::eth_phy_intf_iter_impl, eos::intf_id_t);
wrap_iterator(eos::intf_iter_t, eos::intf_iter_impl, eos::intf_id_t);
wrap_iterator(eos::ip_route_iter_t, eos::ip_route_iter_impl, eos::ip_route_t);
wrap_iterator(eos::ip_route_via_iter_t, eos::ip_route_via_iter_impl, eos::ip_route_via_t);
wrap_iterator(eos::decap_group_iter_t, eos::decap_group_iter_impl, eos::decap_group_t);
wrap_iterator(eos::mpls_route_iter_t, eos::mpls_route_iter_impl, eos::mpls_route_t);
wrap_iterator(eos::mpls_route_via_iter_t, eos::mpls_route_via_iter_impl, eos::mpls_route_via_t);
wrap_iterator(eos::nexthop_group_iter_t, eos::nexthop_group_iter_impl, eos::nexthop_group_t);
wrap_iterator(eos::policy_map_iter_t, eos::policy_map_iter_impl, eos::policy_map_key_t);

// Make managers themselves iterable, when it makes sense:
default_iterator(eos::directflow_mgr, flow_entry_iter);
default_iterator(eos::intf_mgr, intf_iter);
default_iterator(eos::ip_route_mgr, ip_route_iter);
default_iterator(eos::mpls_route_mgr, mpls_route_iter);
