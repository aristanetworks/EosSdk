// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_PANIC_H
#define EOS_PANIC_H

#include <eos/base.h>
#include <stdarg.h> //= hide

namespace eos {

void panic( char const * fmt, ... ) __attribute__((noreturn)); //= hide
void vpanic( char const * fmt, va_list ap ) __attribute__((noreturn)); //= hide
typedef void (*panic_handler_t)(char const *);
void panic_handler_is(panic_handler_t) EOS_SDK_PUBLIC;


};

#endif // EOS_PANIC_H
