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

class error;  // Forward declaration.

/**
 * Reports an exception from the SDK.
 * Internal errors and programming errors are reported via subclasses of
 * exception.  See eos/exception.h for possible exceptions.
 */
void panic(error const & exception) EOS_SDK_NORETURN EOS_SDK_PUBLIC;

/// @deprecated Obsolete, replaced with panic(error).
void panic(char const * fmt, ...)
   EOS_SDK_NORETURN __attribute__((format(printf, 1, 2)))
   EOS_SDK_PUBLIC;

/// @deprecated Obsolete, replaced with panic(error).
void vpanic(char const * fmt, va_list ap)
   EOS_SDK_NORETURN EOS_SDK_PUBLIC;

/**
 * The obsolete panic handler callback definition.
 * This has been replaced with exception_handler_t.
 *
 * @param message The error message
 */
typedef void (*panic_handler_t)(char const * message);

/**
 * The exception handler callback definition.
 *
 * @param exception The exception that needs to be handled.
 */
typedef void (*exception_handler_t)(error const & exception);

/**
 * Sets an obsolete custom panic handler.
 *
 * @param panic_handler_t A panic handler callback
 * @deprecated This has been replaced with exception_handler_is.
 */
void panic_handler_is(panic_handler_t) EOS_SDK_PUBLIC EOS_SDK_DEPRECATED;

/**
 * Sets a custom panic handler.
 *
 * @param exception_handler_t An exception handler callback
 */
void exception_handler_is(exception_handler_t) EOS_SDK_PUBLIC;

}

#endif // EOS_PANIC_H
