// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

/*
  The EchoBot is a simple agent that runs on EOS
*/


#include <eos/agent.h>
#include <eos/timer.h>
#include <eos/file.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/unistd.h>

/* EchoBot is a friendly bot that opens up a socket on port
 * listen_port and echos anything sent to it, prefixed with "You said: ".
 * If nothing is heard from a client within idle_timeout_ seconds,
 * we close the connection to the client and start listening for new
 * incoming connections again. When a client sends us some data, we
 * attempt to write it all back into the socket. If we are unable to
 * write to the client due to some transient failure, we stop
 * receiving notifications about readability and instead subscribe to
 * notifications about writability until all data has been sucessfully
 * sent. After that finishes, we return to our normal state of getting
 * notified when the client sends us data. */
class echo_bot : public eos::timer_task,
                 public eos::file_handler {
 public:
   echo_bot() {
      printf( "initializing...\n" );
      buf_len_ = 0;
      buf_offset_ = 0;
      buf_size_ = sizeof( buf_ );
      connected_socket_ = -1;

      idle_timeout_ = 10;
      listen_port = 10000;
      listen_backlog = 5;

      snprintf( echo_msg_, sizeof(echo_msg_), "You said: " );
      echo_msg_len_ = strlen(echo_msg_);

      // Open up a socket for incoming connections
      listen_socket_ = socket(AF_INET, SOCK_STREAM, 0);

      // Make the socket non-blocking
      int flags = fcntl(listen_socket_, F_GETFL, 0);
      fcntl(listen_socket_, F_SETFL, flags | O_NONBLOCK);

      // Bind to our port
      struct sockaddr_in address;
      address.sin_family = AF_INET;
      address.sin_addr.s_addr = INADDR_ANY;
      address.sin_port = htons(listen_port);
      int result = bind(listen_socket_,(struct sockaddr *)&address,sizeof(address));
      assert(result == 0 && "Could not bind");

      result = listen(listen_socket_, listen_backlog);
      assert(result == 0 && "Could not listen on port");

      // Register for read events on the socket
      read_interest_is(listen_socket_, true);
      printf("initialized with listen_socket_=%d\n", listen_socket_);
   }

   ~echo_bot() {
   }

   bool accept_connection(){
      printf( "accept_connection" );
      assert(connected_socket_ == -1 && "Already handling a connection");
      // handle a new connection!
      struct sockaddr_storage their_addr;
      socklen_t addr_size = sizeof their_addr;
      int new_fd = accept(listen_socket_, (struct sockaddr *)&their_addr,
                          &addr_size);
      if( new_fd == -1 ){
         if( errno == EAGAIN ){
            // Nothing to accept on this connection
            return false;
         }
         assert("Unable to accept new connection");
      } 
      connected_socket_ = new_fd;
      read_interest_is(connected_socket_, true);

      // And let's stop listening on our server until we're done with
      // this connection
      read_interest_is(listen_socket_, false);
      wakeup_time_is( eos::now() + idle_timeout_ );
      return true;
   }

   void end_connection() {
      printf("end_connection to connected_socket_ %d\n", connected_socket_);
      assert(connected_socket_ != -1 && "No connection to close");
      read_interest_is(connected_socket_, false);
      write_interest_is(connected_socket_, false);
      exception_interest_is(connected_socket_, false);
      close(connected_socket_);
      connected_socket_ = -1;
      // Start listening for new connections again
      read_interest_is(listen_socket_, true);
   }

   void send_data(){
      printf( "send_data to connected_socket_ %d\n", connected_socket_);
      // Returns true if all data was sent to the connected_socket_
      int bytes_to_send = buf_len_ - buf_offset_;
      int bytes_written = send(connected_socket_, buf_ + buf_offset_,
                               bytes_to_send, 0);
      printf( "Sent %d of %d bytes\n", bytes_written, bytes_to_send );
      if(bytes_written == -1) {
         if(errno == EAGAIN) {
            read_interest_is(connected_socket_, false);
            write_interest_is(connected_socket_, true);
            return;
         } 
         if(errno == ECONNRESET) {
            // Connection closed by the other side while we were
            // busy getting through our buf_.
            end_connection();
            return;
         }
         assert("send unexpectedly failed");
      }
      buf_len_ = bytes_to_send - bytes_written;
      buf_offset_ += bytes_written;
      if( bytes_written < buf_len_ ) {
         // Stop getting data until we've sent everything.
         read_interest_is(connected_socket_, false);
         write_interest_is(connected_socket_, true);
         return;
      }
      // success!
      read_interest_is(connected_socket_, true);
      write_interest_is(connected_socket_, false);
      wakeup_time_is( eos::now() + idle_timeout_ );
   }

   void on_readable(int fd) {
      printf("on_readable called, fd=%d\n", fd);
      if(fd == listen_socket_) {
         assert(connected_socket_ == -1 &&
                "Should not be readable if we already have a connection" );
         bool success = accept_connection();
         assert(success && "Error accepting new connection");
      } else if(fd == connected_socket_) {
         // Our current connection said something to us.
         assert(buf_len_ == 0 && "Buffer should be empty");
         strcpy( buf_, echo_msg_ );
         int bytes_recvd = recv(fd, buf_ + echo_msg_len_,
                                buf_size_ - echo_msg_len_, 0);
         assert(bytes_recvd != -1 && "Recv unexpectedly failed");
         if(bytes_recvd == 0) {
            end_connection();
         }
         buf_offset_ = 0;
         buf_len_ = bytes_recvd + echo_msg_len_;
         send_data();
      }
   }

   void on_writeable(int fd) {
      printf( "on_writeable called, fd=%d\n", fd );
      assert( connected_socket_ != -1 );
      send_data();
   }

   void run() {
      printf( "Timer called\n" );
      // If we stop hearing anything on the connection for
      // more than the idle_timeout seconds, then we disconnect
      assert( connected_socket_ != -1 );
      end_connection();
   }
   
 private:
   // Number of seconds of idleness before we disconnect
   eos::seconds_t idle_timeout_;

   // Listen port
   int listen_port;
   int listen_backlog;

   int listen_socket_; // Socket listening for new connections
   int connected_socket_; // Socket we are communicating with. 0 if not connected
   
   int buf_size_;
   char buf_[1024];
   int buf_len_; // Size of remaining data in buffer
   int buf_offset_; // Offset of unsent data in buffer

   char echo_msg_[20];
   int echo_msg_len_;
};

int main(int argc, char ** argv) {
   echo_bot bot;
   eos::agent_main_loop("echo_bot", argc, argv);
}

