// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_PANIC_H
#define EOS_PANIC_H

#include <eos/base.h>
#include <cstdarg>

/**
 * Panic handling framework.
 *
 * A 'panic' is raised by the EOS SDK to signal a programming error on
 * behalf of the SDK user. A regular 'assert' is used by the SDK to
 * signal an Arista error which should be reported for correction.
 *
 * Panics occur under a number of conditions, such as an invalid
 * string format for an IP address when using ip_addr_t's constructor
 * to checks of incompatible type attributes during manager calls.
 * The panic message passed to the panic_handler_t callback describes
 * the fault condition observed.
 *
 * During a panic call, any panic handler set with panic_handler_is is
 * called with the message, and then the panic message is also written
 * to stderr and a SIGABRT raised. The SIGABRT will also cause a stack
 * trace to be dumped.
 */

namespace eos {

void panic(char const * fmt, ...)
   __attribute__((noreturn)) __attribute__((format(printf, 1, 2))) EOS_SDK_PUBLIC;
void vpanic(char const * fmt, va_list ap) __attribute__((noreturn)) EOS_SDK_PUBLIC;
/**
 * The panic handler callback definition.
 *
 * @param message The error message
 */
typedef void (*panic_handler_t)(char const * message);
/**
 * Sets a custom panic handler.
 *
 * @param panic_handler_t A panic handler callback
 */
void panic_handler_is(panic_handler_t) EOS_SDK_PUBLIC;

}

#endif // EOS_PANIC_H
