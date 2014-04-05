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

void (*panic_handler)(char const *);
auto exception_handler = throw_exception;

void panic(char const * fmt, ...) {
   va_list ap;
   va_start(ap, fmt);
   vpanic(fmt, ap);
   // not reached
}

void panic(error const & error) {
   if(panic_handler) {  // Check the legacy handler first (will be removed).
      panic_handler(error.what());
   } else if(exception_handler) {
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

void panic_handler_is(panic_handler_t h) {
   assert(h && "Panic handler must not be null");
   panic_handler = h;
}

void exception_handler_is(exception_handler_t h) {
   assert(h && "exception handler must not be null");
   exception_handler = h;
}

}
