// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_TRACING_H
#define EOS_TRACING_H

#include <eos/base.h>

/**
 * @file
 * Tracing facilities.
 * 
 * This modules allows SDK programs to integrate with EOS's tracing
 * mechanisms. Tracing is useful for logging and debugging purposes,
 * and can be selectively enabled at various levels to gain insight on
 * a programs runtime behavior.
 *
 * Trace statements are formatted using a similar syntax to
 * printf. For example, the following lines create a trace facility 
 * called "MyDebugOutput" which can be used to print messages.
 * 
 * @code{.cpp}
 *    eos::tracer t("MyDebugOutput");
 *    t.trace0("%s World", "Hello");
 *    t.trace5("Good bye!%d!", 1);
 * @endcode

 * When running this program, you would now see the following output:
 *   2014-01-01 17:16:15.432110 26910 MyDebugOutput        0 Hello World
 *   2014-01-01 17:16:15.818181 26910 MyDebugOutput        5 Good bye!1!
 *
 * Tracing can be enabled via two main mechanisms. If running your
 * program under ProcMgr's control, using the daemon CLI, the
 * following CLI command will instantly enable tracing output for your
 * agent:
 *    switch(conf)# trace <AGENT_NAME> setting <TRACE_NAME>/<0-9>
 * 
 * Traditionally, lower trace numbers are reserved for more important
 * events, while higher numbers are used for events that happen
 * frequently, or are not particularly notable.
 * 
 * This will cause tracing output to appear in the
 * /var/log/agents/AGENT_NAME-### file. More information about the
 * trace command can be found in the EOS manual.
 * 
 * You can also control tracing using the TRACE environment variable,
 * which is useful when running your agent manually:
 *    bash# TRACE=MyDebugOutput/0-9 ./myAgentExecutable
 * 
 * This results in tracing output to be sent directly to stdout.
 *
 * Multiple tracers can be used in the same agent, and you can control
 * multiple trace facilities using comma separated entries. For
 * example,
 *    TRACE=MyDebugOutput/0-3,MyLogging* ./myAgentExecutable
 * results in all tracing from facilities whose name starts with
 * "MyLogging", as well as trace messages from MyDebugOutput at levels
 * 0, 1, 2, and 3.
 *
 * You can view tracing for the SDK module by tracing EosSdk*
 */

namespace eos {

/**
 * The level of the trace statement.
 * 
 * Lower numbers should be used for more important events, while
 * higher numbers should be used for events which occur frequently, or
 * which aren't as important.
 */
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

   /// Returns true if this tracer will output trace statements at the
   /// given level.
   bool enabled(trace_level level);
   /// Set whether this trace facility should print at the given level.
   void enabled_is(trace_level level, bool value);

   /** Trace a statement at the given level.
    *
    * The expression format and extra arguments follow printf's
    * syntax.
    */
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

