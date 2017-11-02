// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/fd.h>
#include <eos/tracing.h>

#include <assert.h>
#include <errno.h>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * This example library provides a custom handler for reading a stream
 * off of a file descriptor. Given either a message length or a string
 * delimeter, the `stream_handler` will call the users `on_message`
 * callback whenever a full message is received. If the file
 * descriptor is remotely closed, `on_connection_closed` will be
 * called.
 */

class stream_handler : private eos::fd_handler {
   // Inherit fd_handler privately so we don't polute the namespaces
   // of our children with on_readable/writable methods

 public:
   explicit stream_handler(size_t max_buf_size) :
         fd(), buf_size(max_buf_size),
         tracer("eossdk_stream") {
      tracer.trace0("New stream_handler constructed");
      read_buf = NULL;
      write_buf = NULL;
      bytes_read = 0;
      bytes_to_write = 0;
      fd = 0;
      next_message_length = 0;
      delimiter = NULL;
      delimiter_length = 0;
   }

   virtual ~stream_handler() {
      watch_stream(fd, false);
   }

   // Users of this library should override this function to receive a
   // callback when a full message has been received.
   virtual void on_message(char * buf, size_t length) = 0;

   // Callback triggered when the connection has been closed by the
   // remote side.
   virtual void on_connection_closed() = 0;


   // Start or stop watching a stream. At this time, the
   // stream_handler can only handle one stream at a time, and will
   // assert if you attempt to watch a new stream while one is
   // currently being monitored.
   void watch_stream(int file_descriptor, bool should_watch);

   // Send a message out on the current stream. If the stream is
   // currently blocked, the message is buffered until the stream is
   // writable again, or until buffer space runs out (at which point
   // we assert).
   void send_message(const char * buf, size_t length);

   // Update the expected length of the next message. When this
   // library has received this many bytes, it will call the
   // on_message callback.
   void next_message_length_is(size_t length);

   // Update the delimter used to seperate messages. When this library
   // sees this string on the stream, it will send all data up to the
   // delimiter to the on_message function. The delimiter is not sent
   // as part of the message.
   void delimiter_is(const char * delim, size_t length);

 private:
   int send_data(const char * buf, size_t length);
   int strnstr(char * source, const char * delim, int length, int delim_length);
   int next_message_break(char * buf, size_t length);
   void drain_read_buffer();

   // Overriden from fd_handler.
   void on_readable(int notifying_fd);
   void on_writable(int notifying_fd);

   int fd;
   size_t buf_size;
   char * read_buf;
   char * write_buf;
   
   eos::tracer tracer;

   // Tracker variables to determine how much of each buffer we have used.
   size_t bytes_read; // space we have used in the read_buf
   size_t bytes_to_write; // bytes in the write_buf we have left to send out

   size_t next_message_length;
   const char * delimiter;
   size_t delimiter_length;
};


// ----------------------
// Implementation details
// ----------------------

void 
stream_handler::watch_stream(int file_descriptor, bool should_watch) {
   if(fd && fd != file_descriptor) {
      assert(!"Only allowed to handle one stream at a time");
   }
   if(!should_watch) {
      if(fd) {
         tracer.trace0("Cleaning up");
         watch_readable(fd, false);
         watch_writable(fd, false);
         delete[] read_buf;
         delete[] write_buf;
         read_buf = NULL;
         write_buf = NULL;
         fd = 0;
         next_message_length = 0;
         delimiter = NULL;
         delimiter_length = 0;
      }
   } else {
      tracer.trace0("Watching stream %d", file_descriptor);
      fd = file_descriptor;
      watch_readable(fd, true);
      read_buf = new char[buf_size];
      write_buf = new char[buf_size];
      bytes_read = 0;
      bytes_to_write = 0;
   }
}

void 
stream_handler::delimiter_is(const char * delim, size_t length) {
   if(next_message_length) {
      assert(!"Unable to set a delimiter when a message length is specified");
   }
   tracer.trace4("Delimter set to '%s'", delim);
   delimiter = delim;
   delimiter_length = length;
   drain_read_buffer();
}


void 
stream_handler::next_message_length_is(size_t length) {
   if(delimiter_length) {
      assert(!"Unable to set a message length when a delimiter is specified");
   }
   tracer.trace4("Next messsage length set to %zu", length);
   next_message_length = length;
   drain_read_buffer();
}

void 
stream_handler::send_message(const char * buf, size_t length) {
   if(bytes_to_write == 0) {
      // Nothing is in our write buffer, try to send directly from
      // the user's buffer.
      int bytes_remaining = send_data(buf, length);
      if(!bytes_remaining) {
         // Sent everything!
         return;
      } else {
         length -= bytes_remaining;
         buf += bytes_remaining;
      }
   }
   // Store the message at the end of our write queue
   if(bytes_to_write + length > buf_size) {
      assert(!"Not enough internal buffers to store message");
   }
   memmove(write_buf + bytes_to_write, buf, length);
   bytes_to_write += length;
}

// Roll our own strnstr function: search `source` for `delim` up to
// `length` number of characters, and return the index of the first
// instance of where `delim` starts. If `delim` is not found within
// `length`, this returns -1. This function does not care about '\0'
// null characters, so delim + delimiter_length should not include a
// trailing null char
int
stream_handler::strnstr(char * source, const char * delim,
                        int length, int delimiter_length) {
   tracer.trace9("Searching %d bytes of read buffer for %d byte delim",
                 length, delimiter_length);
   for(char * c = source; (c - source) <= (length - delimiter_length); c++) {
      if(memcmp(c, delim, delimiter_length) == 0) {
         return c - source;
      }
   }
   return -1;
}

// Search for the index of the next message break in `buf`, up until
// `length` characters. If no message break is returned, return -1;
int
stream_handler::next_message_break(char * buf, size_t length) {
   if(next_message_length) {
      return next_message_length <= length ? next_message_length - 1 : -1;
   } else if(delimiter_length) {
      return strnstr(buf, delimiter, length, delimiter_length);
   }
   return -1;
}

void
stream_handler::drain_read_buffer() {
   tracer.trace8("Searching the read buffer for new messages");
   int bytes_passed_to_user = 0;
   while(true) {
      int msg_break = next_message_break(read_buf + bytes_passed_to_user,
                                         bytes_read - bytes_passed_to_user);
      if(msg_break == -1) {
         break;
      }
      tracer.trace8("Message of length %d received", msg_break);
      bytes_passed_to_user += next_message_length;
      on_message(read_buf + bytes_passed_to_user, msg_break);
      bytes_passed_to_user += msg_break;
      // Ignore the delimiter message
      bytes_passed_to_user += delimiter_length; 
   }      
   bytes_read = bytes_read - bytes_passed_to_user;
   if(bytes_read) {
      tracer.trace7("Saving %zu bytes for next message", bytes_read);
   }
   // A circular buffer (like boost::circular_buffer) would make
   // this more efficient, but let's not introduce dependencies for
   // this helper example library.
   memmove(read_buf, read_buf + bytes_passed_to_user, bytes_read);
}

// Helper method to send a number of bytes over fd. Returns the
// number of bytes that failed to send.
int 
stream_handler::send_data(const char * buf, size_t length) {
   int bytes_written = write(fd, buf, length);
   if(bytes_written == -1) {
      if(errno == EAGAIN) {
         tracer.trace5( "EAGAIN when trying to write %zu bytes to fd%d", length, fd);
         // The file descriptor is backed up! Try again when it
         // becomes writeable in the future.
         watch_writable(fd, true);
         return length;
      }
      if(errno == ECONNRESET) {
         // Connection closed by the other side while we were
         // busy getting through our buf_.
         tracer.trace0( "Connection closed when trying to write %zu bytes to fd%d",
                        length, fd);
         on_connection_closed();
         watch_stream(fd, false);
         return 0;
      }
      tracer.trace0( "Unexpected error code from send(): %d", errno);
      assert("send unexpectedly failed");
   } else if((size_t) bytes_written < length) {
      watch_writable(fd, true);
   } else {
      // The fd is sending all data, no need to get alerts on when
      // it is writable.
      watch_writable(fd, false);
   }
   tracer.trace8("Sent %d of %zu bytes", bytes_written, length);
   return length - bytes_written;
}

void 
stream_handler::on_readable(int notifying_fd) {
   if(notifying_fd != fd) {
      return;
   }
   // Read as many bytes as we can off of the socket
   int bytes_recvd = recv(fd, read_buf + bytes_read,
                          buf_size - bytes_read, 0);
   if(bytes_recvd == -1) {
      tracer.trace0("Recv unexpectedly failed");
      return;
   }
   if(bytes_recvd == 0) {
      tracer.trace0("Connection to %d closed", fd);
      on_connection_closed();
      watch_stream(fd, false);
      return;
   }
   bytes_read += bytes_recvd;
   drain_read_buffer();
}

void
stream_handler::on_writable(int notifying_fd) {
   if(notifying_fd != fd) {
      return;
   }
   if(!bytes_to_write) {
      // If we somehow get called but have nothing to write,
      // unregister our interest in this notification.
      watch_writable(fd, false);
      return;
   }
   tracer.trace7("Buffer is writable, attempting to send %zu bytes",
                 bytes_to_write);
   int bytes_remaining = send_data(write_buf, bytes_to_write);
   if(bytes_remaining) {
      memmove(write_buf, write_buf + bytes_to_write - bytes_remaining,
              bytes_remaining);
   }
   bytes_to_write = bytes_remaining;
}
