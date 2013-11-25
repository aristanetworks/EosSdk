// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_FILE_H
#define EOS_FILE_H

namespace eos {

/* This class manages file descriptors within the eventloop
context. There are two main components to handling file
descriptors. *_interest_is() methods register a file descriptor to
handle events. Meanwhile, the on_* methods should be overridden to
handle these changes to the file descriptor's state. For example if
you're managing a network connection with a client, overriding
handle_readable will let you to receive updates when data has been
received. Note that on certain file descriptors */
class fd_handler {
 public:
   fd_handler();
   ~fd_handler();

   virtual void on_readable(int fd) {};
   virtual void on_writable(int fd) {};
   virtual void on_exception(int fd) {};
   void watch_readable(int fd, bool);
   void watch_writable(int fd, bool);
   void watch_exception(int fd, bool);
};

};

#endif // EOS_FILE_H
