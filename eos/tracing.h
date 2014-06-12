// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TRACING_H
#define EOS_TRACING_H

#include <eos/base.h>

namespace eos {

enum trace_level {
   Level0,
   Level1,
   Level2,
   Level3,
   Level4,
   Level5,
   Level6,
   Level7,
   Level8,
   Level9,
};

class tracer_internal;

/**
 * A tracer object.
 *
 * The traceN functions are just shortcuts for trace(N, expression, ...).
 * The supported formats are those of printf.
 */
class EOS_SDK_PUBLIC tracer {
 public:
   explicit tracer(char const * name);
   ~tracer();

   bool enabled(trace_level level);
   void enabled_is(trace_level level, bool value);

   void trace(trace_level level, char const * expression, ...)
      EOS_SDK_FORMAT_STRING_CHECK(3);
   void trace0(char const * expression, ...) EOS_SDK_FORMAT_STRING_CHECK(2);
   void trace1(char const * expression, ...) EOS_SDK_FORMAT_STRING_CHECK(2);
   void trace2(char const * expression, ...) EOS_SDK_FORMAT_STRING_CHECK(2);
   void trace3(char const * expression, ...) EOS_SDK_FORMAT_STRING_CHECK(2);
   void trace4(char const * expression, ...) EOS_SDK_FORMAT_STRING_CHECK(2);
   void trace5(char const * expression, ...) EOS_SDK_FORMAT_STRING_CHECK(2);
   void trace6(char const * expression, ...) EOS_SDK_FORMAT_STRING_CHECK(2);
   void trace7(char const * expression, ...) EOS_SDK_FORMAT_STRING_CHECK(2);
   void trace8(char const * expression, ...) EOS_SDK_FORMAT_STRING_CHECK(2);
   void trace9(char const * expression, ...) EOS_SDK_FORMAT_STRING_CHECK(2);
 private:
   tracer_internal * tracer_;
};

}

#endif // EOS_TRACING_H

