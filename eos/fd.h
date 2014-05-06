// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_FILE_H
#define EOS_FILE_H

#include <eos/base.h>

/**
 * File descriptor support module.
 *
 * The handler within this module allows you to react to events
 * on file descriptors created in your application. Set up a
 * network socket and then watch the fd number with the watch_*
 * methods of the fd_handler. Watched sockets cause reaction
 * events within the EOS agent asynchronous event loop.
 */

namespace eos {

class fd_internal;

/**
 * This class manages file descriptors within the event loop context.
 *
 * There are two main components to handling file* descriptors. The
 * 'watch_*()' register a file descriptor to react to events on the
 * descriptor state. The 'on_*()' methods should be overridden to
 * actually handle these changes to the file descriptor's state. For
 * example if you're managing a network connection with a client,
 * invoking 'watch_readable(fd, true)' will cause 'on_readable(fd)' to
 * be called whenever data has been received.
 *
 * Note that it is not necessary to always watch_*() attributes of a
 * file descriptor, that is, you are free to write to a socket even if
 * watch_writeable has not been set. Continuing with the network
 * connection example, on_writeable will be continuously called when
 * 'watch_writeable(fd, true)' is set, as the descriptor is almost
 * always writeable. If the other side of the connection overruns its
 * TCP backlog, though, your descriptor will return an error on write,
 * indicating that the socket is no longer writeable, and it is at
 * that point that 'watch_writeable(fd, true)' should be invoked. When
 * the other end of the connection
 */
class EOS_SDK_PUBLIC fd_handler {
 public:
   /// Creates a file descriptor handler, which can react to any number of FDs.
   fd_handler();
   virtual ~fd_handler();

   /// Called when the file descriptor number is readable.
   virtual void on_readable(int fd);
   /// Called when the file descriptor number is writable.
   virtual void on_writable(int fd);
   /// Called when the file descriptor number has exceptions.
   virtual void on_exception(int fd);

   /// Notifies this handler when the passed file descriptor is readable.
   void watch_readable(int fd, bool);
   /// Notifies this handler when the passed file descriptor is writable.
   void watch_writable(int fd, bool);
   /// Notifies this handler when the passed file descriptor has exceptions.
   void watch_exception(int fd, bool);

 private:
   fd_internal * fd_;
};

}

#endif // EOS_FILE_H
