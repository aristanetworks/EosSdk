// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <eos/tracing.h>

namespace eos {

struct tracer_internal {
   explicit tracer_internal(char const * name_)
      : name(name_), levelEnabled(9, true) {
   }

   void trace(trace_level level, char const * expression, va_list args) const {
      char * expandedExpression = NULL;
      if (vasprintf(&expandedExpression, expression, args) != -1) {
         fprintf(stderr, "[%s]\t%s\n", name, expandedExpression);
         free(expandedExpression);
      }
   }

   char const * name;
   std::vector<bool> levelEnabled;
};

tracer::tracer(char const * name) : tracer_(new tracer_internal(name)) {
}

tracer::~tracer() {
   delete tracer_;
}

bool tracer::enabled(trace_level level) const {
   return tracer_->levelEnabled[level];
}

void tracer::enabled_is(trace_level level, bool value) {
   tracer_->levelEnabled[level] = value;
}

void tracer::trace(trace_level level, char const * expression, ...) const {
   if (enabled(level)) {
      va_list args;
      va_start(args, expression);
      tracer_->trace(level, expression, args);
      va_end(args);
   }
}

#define TRACE(level) void                                               \
   tracer::trace ## level (char const * expression, ...) const {        \
      if (enabled(static_cast<trace_level>(level))) {                   \
         va_list args;                                                  \
         va_start(args, expression);                                    \
         tracer_->trace(static_cast<trace_level>(level), expression, args); \
         va_end(args);                                                  \
      }                                                                 \
   }

TRACE(0)
TRACE(1)
TRACE(2)
TRACE(3)
TRACE(4)
TRACE(5)
TRACE(6)
TRACE(7)
TRACE(8)
TRACE(9)

#undef TRACE

}
