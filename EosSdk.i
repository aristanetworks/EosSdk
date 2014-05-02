// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

%module(directors="1") eossdk

%include "std_string.i"
%import "SwigUtils.i"

// Change all some_class_t names to just SomeClass:
 // The <<""< uses automatic string concatination to get around the
 // conflict marker limitation.
%rename("%(command:python $SRCDIR/SwigRenamer.py --classname <<""<)s", %$isclass) "";
// Don't do anything for enum values, functions or variables.

// Ignored conversions:

#define SWIG_FILE_WITH_INIT
%import "eos/base.h"

// Tell swig about uint8/16/32/64_t
typedef unsigned short uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
// Tell swig about our custom types (copied from base.h)
typedef double seconds_t;
typedef uint16_t uint16_be_t;
typedef uint32_t uint32_be_t;
typedef uint64_t uint64_be_t;

// generate directors for all classes that have virtual methods, except the managers
%feature("director");
%feature("nodirector") eos::acl_mgr;
%feature("nodirector") eos::agent_mgr;
%feature("nodirector") eos::decap_group_mgr;
%feature("nodirector") eos::directflow_mgr;
%feature("nodirector") eos::eth_intf_mgr;
%feature("nodirector") eos::eth_phy_intf_mgr;
%feature("nodirector") eos::fib_mgr;
%feature("nodirector") eos::intf_mgr;
%feature("nodirector") eos::ip_route_mgr;
%feature("nodirector") eos::mac_table_mgr;
%feature("nodirector") eos::mlag_mgr;
%feature("nodirector") eos::mpls_route_mgr;
%feature("nodirector") eos::neighbor_table_mgr;
%feature("nodirector") eos::nexthop_group_mgr;
%feature("nodirector") eos::policy_map_mgr;
%feature("nodirector") eos::system_mgr;

%{
#include "eos/agent.h"
#include "eos/event_loop.h"
#include "eos/exception.h"
#include "eos/fd.h"
#include "eos/timer.h"
#include "eos/iterator.h"
#include "eos/intf.h"
#include "eos/ip.h"
#include "eos/eth.h"
#include "eos/eth_intf.h"
#include "eos/directflow.h"
#include "eos/ip_route.h"
#include "eos/neighbor_table.h"
#include "eos/mac_table.h"
#include "eos/mlag.h"
#include "eos/sdk.h"
#include "eos/system.h"

using namespace eos;

struct stop_iteration {};
%}

%define translate_exception(ExceptionClass)
   catch(ExceptionClass const & e) {
      ExceptionClass * exc = new ExceptionClass(e);
      PyObject * obj = SWIG_NewPointerObj(exc, SWIGTYPE_p_eos__##ExceptionClass, 1);
      PyErr_SetObject(SWIG_Python_ExceptionType(SWIGTYPE_p_eos__##ExceptionClass), obj);
      SWIG_fail;
   }
%enddef

%exceptionclass error;

%exception {
   try {
      $action
   }
   // translate_exception(invalid_argument_error)
   translate_exception(invalid_range_error)
   translate_exception(no_such_interface_error)
   translate_exception(not_switchport_eligible_error)
   translate_exception(invalid_vlan_error)
   translate_exception(internal_vlan_error)
   // TODO(tsuna): Add a catch-all case for the base type `exception'.
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

// For vlan_set
%template(_BitSet4096) std::bitset<4096>;

// Ignore all the old-style iterators.
%ignore eos::acl_mgr::acl_foreach;
%ignore eos::acl_mgr::acl_rule_eth_foreach;
%ignore eos::acl_mgr::acl_rule_ip_foreach;
%ignore eos::decap_group_mgr::decap_group_foreach;
%ignore eos::eth_intf_mgr::eth_intf_foreach;
%ignore eos::eth_phy_intf_mgr::eth_phy_intf_foreach;
%ignore eos::intf_mgr::intf_foreach;
%ignore eos::ip_route_mgr::ip_route_foreach;
%ignore eos::ip_route_mgr::ip_route_via_foreach;
%ignore eos::mpls_route_mgr::mpls_route_foreach;
%ignore eos::mpls_route_mgr::mpls_route_via_foreach;

%include "eos/agent.h"
// Ignore the `raise' method of all exceptions.  `raise' is a Python keyword
// and also this method is used to throw the exception from C++ and is useless
// in Python.
%ignore raise;
// Ignore the `what' method of all exceptions.  This method is redundant with
// the `msg' method (it's only provided for "compatibility" with standard
// exceptions).
%ignore what;
%include "eos/exception.h"
%include "eos/eth.h"
%include "eos/event_loop.h"
%include "eos/fd.h"
%include "eos/intf.h"
%include "eos/eth_intf.h"
%include "eos/ip.h"
%include "eos/timer.h"
%include "eos/directflow.h"
%include "eos/ip_route.h"
%include "eos/neighbor_table.h"
%include "eos/mac_table.h"
%include "eos/mlag.h"
%include "eos/sdk.h"
%include "eos/system.h"

// Pythonify our iterators.
wrap_iterator(eos::flow_entry_iter_t, eos::flow_entry_iter_impl, eos::flow_entry_t);
wrap_iterator(eos::intf_iter_t, eos::intf_iter_impl, eos::intf_id_t);
wrap_iterator(eos::eth_intf_iter_t, eos::eth_intf_iter_impl, eos::intf_id_t);
wrap_iterator(eos::ip_route_iter_t, eos::ip_route_iter_impl, eos::ip_route_t);
wrap_iterator(eos::ip_route_via_iter_t, eos::ip_route_via_iter_impl, eos::ip_route_via_t);

// Make managers themselves iterable, when it makes sense:
default_iterator(eos::directflow_mgr, flow_entry_iter);
default_iterator(eos::intf_mgr, intf_iter);
default_iterator(eos::ip_route_mgr, ip_route_iter);
