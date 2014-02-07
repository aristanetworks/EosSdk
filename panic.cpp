// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "eos/panic.h"

namespace eos {

void (*panic_handler)(char const *);

void panic(char const * fmt, ...) {
   va_list ap;
   va_start(ap, fmt);
   vpanic(fmt, ap);
   // not reached
}

void vpanic(char const * fmt, va_list ap) {
   char buf[1024];
   vsnprintf(buf, 1024, fmt, ap);
   if(panic_handler) {
      panic_handler(buf);
   }
   fprintf(stderr, "%s\n", buf);
   for(;;) {
      abort();
   }
}

void panic_handler_is(panic_handler_t h) {
   assert(h && "Panic handler must not be null");
   panic_handler = h;
}

}
