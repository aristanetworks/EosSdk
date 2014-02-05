// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_PANIC_H
#define EOS_PANIC_H

#include <eos/base.h>
#include <cstdarg>

namespace eos {

void panic(char const * fmt, ...)
   __attribute__((noreturn)) __attribute__((format(printf, 1, 2))) EOS_SDK_PUBLIC;
void vpanic(char const * fmt, va_list ap) __attribute__((noreturn)) EOS_SDK_PUBLIC;
typedef void (*panic_handler_t)(char const *);
void panic_handler_is(panic_handler_t) EOS_SDK_PUBLIC;

}

#endif // EOS_PANIC_H
