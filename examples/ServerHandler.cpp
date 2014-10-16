// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/fd.h>
#include <eos/tracing.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/unistd.h>

/**
 * This example handler builds on top of fd's fd_handler to provide an
 * asynchronous server. It opens a socket and listens on the provided
 * port. When a client connects to the server, it calls the
 * on_connection callback, which subclasses should override to receive
 * notifications on new connections.
 */

class server_handler : private eos::fd_handler {
   // Inherit fd_handler privately so we don't polute the namespaces
   // of our children with on_readable/writable methods

 public:
   server_handler(int port, int backlog) :
         tracer("eossdk_server") {
      tracer.trace0("New server constructed, serving on %d", port);
      serve(port, backlog);
   }

   virtual ~server_handler() {
   }

   // Callback triggered when a new client connects to this
   // server. Users should override this method and expect a file
   // descriptor number for the new socket along with the requester's
   // sockaddr details. The `request_socket` will be set as
   // non-blocking so it can be properly integrated in the event loop.
   virtual void on_connection(int request_socket,
                              sockaddr_storage & requester_addr) = 0;

 private:
   void serve(int port, int backlog);
   void on_readable(int);

   eos::tracer tracer;
   int server_socket;
};

void
server_handler::serve(int port, int backlog) {
   // Open up a socket for incoming connections
   server_socket = socket(AF_INET, SOCK_STREAM, 0);
   
   int yes = 1;
   setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
   
   // Bind to our port
   struct sockaddr_in address;
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(port);
   int result = bind(server_socket, (sockaddr *) &address, sizeof(address));
   assert(result == 0 && "Could not bind to port");
   
   result = listen(server_socket, backlog);
   assert(result == 0 && "Could not listen on port");
   watch_readable(server_socket, true);
}

void
server_handler::on_readable(int fd) {
   if(fd != server_socket) {
      return;
   }
   tracer.trace0("New connection on fd %d", fd);
   struct sockaddr_storage their_addr;
   socklen_t addr_size = sizeof(their_addr);
   int new_fd = accept(server_socket, (sockaddr *) &their_addr,
                       &addr_size);
   if(new_fd == -1) {
      tracer.trace1("accept() unexpectedly returned -1 ");
      return;
   }
   // Set the new socket to be nonblocking
   int flags = fcntl(new_fd, F_GETFL, 0);
   fcntl(new_fd, F_SETFL, flags | O_NONBLOCK);

   on_connection(new_fd, their_addr);
}
