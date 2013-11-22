// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_FILE_H
#define EOSSDK_FILE_H

namespace eos {

class file_handler {
 public:
   file_handler();
   ~file_handler();
   virtual void on_readable(int fd) {};
   virtual void on_writable(int fd) {};
   virtual void on_exception(int fd) {};
   void read_interest_is(int fd, bool);
   void write_interest_is(int fd, bool);
   void exception_interest_is(int fd, bool);
};

};

#endif // EOSSDK_FILE_H
