// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "eos/panic.h"
#include "eos/exception.h"

namespace eos {

static void throw_exception(error const & exception) {
   exception.raise();
}

auto exception_handler = throw_exception;

void panic(char const * fmt, ...) {
   va_list ap;
   va_start(ap, fmt);
   vpanic(fmt, ap);
   // not reached
}

void panic(error const & error) {
   if(exception_handler) {
      exception_handler(error);
   }
   fprintf(stderr, "%s\n", error.what());
   for(;;) {
      abort();
   }
}

struct legacy_exception : public error {
   virtual ~legacy_exception() noexcept {
   }
   explicit legacy_exception(std::string const & msg) noexcept : error(msg) {
   }
   virtual void raise() const {
      throw *this;
   }
};

void vpanic(char const * fmt, va_list ap) {
   char buf[1024];
   vsnprintf(buf, 1024, fmt, ap);
   panic(legacy_exception(buf));
}

void exception_handler_is(exception_handler_t h) {
   assert(h && "exception handler must not be null");
   exception_handler = h;
}

}
