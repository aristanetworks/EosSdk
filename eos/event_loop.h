// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_EVENT_LOOP_H
#define EOS_EVENT_LOOP_H

#include <sys/time.h>

#include <eos/base.h>

namespace eos {

/**
 * Adapter to integrate the EOS event loop with an external event loop.
 * Subclass this class to be able to handle the file descriptors and
 * timers that the EOS code needs to dispatch to your event loop
 * implementation.
 *
 * When you provide your implementation of event_loop_handler to the
 * event_loop, EOS code will start calling the watch_* methods to
 * (un)register its interest in various file descriptors, so that you
 * can hook them up into your event loop implementation.  When those
 * file descriptors become ready, you must call the corresponding on_*()
 * method in a timely fashion for the EOS code to run.
 *
 * The on_*() methods are all non-blocking methods.
 */
class EOS_SDK_PUBLIC event_loop_handler {
 public:
   virtual ~event_loop_handler();

   /// Notifies the EOS event loop that the file descriptor is readable.
   void on_readable(int fd);
   /// Notifies the EOS event loop that the file descriptor is writable.
   void on_writable(int fd);
   /// Notifies the EOS event loop that the file descriptor has exceptions.
   void on_exception(int fd);
   /// Notifies the EOS event loop that its next timer has expired.
   void on_timeout();

   /// Called by EOS to (un)register its interest in a fd being readable.
   virtual void watch_readable(int fd, bool interested) = 0;
   /// Called by EOS to (un)register its interest in a fd being writable.
   virtual void watch_writable(int fd, bool interested) = 0;
   /// Called by EOS to (un)register its interest in a fd having exceptions.
   virtual void watch_exception(int fd, bool interested) = 0;
   /**
    * Called to register when is the next timeout that EOS code must handle.
    * The deadline passed in argument is relative to now (so for instance if
    * the next timer the EOS code need to handle is in 5 seconds from now,
    * then the deadline will be 5 seconds, not "now + 5s").
    * If this function is called multiple times, subsequent calls should
    * override the timeout set by previous calls.  In other words, there is
    * only one timeout associated with this function, instead of each call
    * creating a new timeout.
    */
   virtual void timeout_time_is(struct timeval deadline) = 0;
};

/**
 * The EOS event loop.
 *
 * This class represents the event loop that is built into EOS code.
 * It can be used to run this loop on demand, or to integrate this
 * event loop with an external event loop, such as that provided by
 * libevent or other third-party code.
 */
class EOS_SDK_PUBLIC event_loop {
 public:
   event_loop();
   ~event_loop();

   /**
    * Wait for all managers to be initialized. Generally called right
    * after creating the event_loop, as an alternative to creating an
    * agent_handler and then waiting for on_initialized to be called.
    *
    * This method is a blocking method.  It may block for any amount
    * of time that is necessary to wait for the initial state sync
    * from Sysdb.
    */
   void wait_for_initialized() const;

   /**
    * Run the event loop for `duration` seconds. If no duration is
    * specified, all pending events will be executed and control will
    * be returned to the caller.
    */
   void run(seconds_t duration=0) const;

   /**
    * Registers an external event loop to use instead of EOS's.
    *
    * Upon calling this function, the EOS code will start registering its file
    * descriptors and its next timeout with the given handler, and will start
    * expecting that an external event loop will deliver events to the handler
    * in a timely fashion.
    *
    * If wait_for_initialized() hasn't been called already, this method is a
    * blocking method.  It may block for any amount of time that is necessary
    * to wait for the initial state sync from Sysdb.
    */
   void external_loop_is(event_loop_handler * loop);

 private:
   EOS_SDK_DISALLOW_COPY_CTOR(event_loop);
   event_loop_handler * loop_;
};

}

#include <eos/inline/event_loop.h>

#endif // EOS_EVENT_LOOP_H
