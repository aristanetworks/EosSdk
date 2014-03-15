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

// generate directors for all classes that have virtual methods
%feature("director");

#define SWIG_FILE_WITH_INIT
%include "eos/base.h"

%{
#include "eos/base.h"
#include "eos/agent.h"
#include "eos/event_loop.h"
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
using namespace eos;

struct stop_iteration {};
%}

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

%include "eos/agent.h"
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

// Pythonify our iterators.
wrap_iterator(eos::flow_entry_iter_t, eos::flow_entry_iter_impl, eos::flow_entry_t);
wrap_iterator(eos::intf_iter_t, eos::intf_iter_impl, eos::intf_id_t);
wrap_iterator(eos::ip_route_iter_t, eos::ip_route_iter_impl, eos::ip_route_t);
wrap_iterator(eos::ip_route_via_iter_t, eos::ip_route_via_iter_impl, eos::ip_route_via_t);

// Make managers themselves iterable, when it makes sense:
default_iterator(eos::directflow_mgr, flow_entry_iter);
default_iterator(eos::intf_mgr, intf_iter);
default_iterator(eos::ip_route_mgr, ip_route_iter);
