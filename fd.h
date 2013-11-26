// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_FILE_H
#define EOS_FILE_H

namespace eos {

/* This class manages file descriptors within the event loop
context. There are two main components to handling file
descriptors. The 'watch_*()' register a file descriptor to react to
events on the descriptor state. The 'on_*()' methods should be
overridden to actually handle these changes to the file descriptor's
state. For example if you're managing a network connection with a
client, invoking 'watch_readable(fd, true)' will cause
'on_readable(fd)' to be called whenever data has been received.

Note that it is not necessary to always watch_*() attributes of a file
descriptor, that is, you are free to write to write to a socket even
if watch_writeable has not been set. Continuing with the network
connection example, on_writeable will be continuously called when
'watch_writeable(fd, true)' is set, as the descriptor is almost always
writeable. If the other side of the connection overruns its TCP
backlog, though, your descriptor will return an error on write,
indicating that the socket is no longer writeable, and it is at that
point that 'watch_writeable(fd, true)' should be invoked. When the
other end of the connection */
class fd_handler {
 public:
   fd_handler();
   ~fd_handler();

   virtual void on_readable(int fd);
   virtual void on_writable(int fd);
   virtual void on_exception(int fd);
   void watch_readable(int fd, bool);
   void watch_writable(int fd, bool);
   void watch_exception(int fd, bool);
};

};

#endif // EOS_FILE_H
