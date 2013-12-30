// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

%module(directors="1") EosSdk

%include "std_string.i"
%import "SwigUtils.i"

// Change all some_class_t names to just SomeClass:
 // The <<""< uses automatic string concatination to get around the
 // conflict marker limitation.
%rename("%(command:python $SRCDIR/SwigRenamer.py --classname <<""<)s", %$isclass) "";
// Rename all functions and variables to be lowerCamelCased:
%rename("%(command:python $SRCDIR/SwigRenamer.py <<""<)s", %$isfunction) "";
%rename("%(command:python $SRCDIR/SwigRenamer.py <<""<)s", %$isvariable) "";
// Don't do anything for enum values.

// Ignored conversions:
%ignore handle_agent_initialized;


#define SWIG_FILE_WITH_INIT
#define EOS_SDK_PUBLIC
#define EOS_SDK_PRIVATE
#define EOS_SDK_INTERNAL

typedef double seconds_t; // Tell swig about our custom seconds_t type

// generate directors for all classes that have virtual methods
%feature("director");

%include "eos/agent.h"
%include "eos/event_loop.h"
%include "eos/fd.h"
%include "eos/timer.h"
%include "eos/intf.h"


%{
#include "eos/agent.h"
#include "eos/event_loop.h"
#include "eos/fd.h"
#include "eos/timer.h"
#include "eos/intf.h"
#include "eos/inline/intf.h"
using namespace eos;
%}
