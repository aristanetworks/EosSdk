// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/sdk.h>
#include <eos/timer.h>
#include <eos/tracing.h>

#include <cstring>
#include <unordered_map>

#include "StreamHandler.cpp"
#include "ServerHandler.cpp"

/* EchoBot is a friendly agent that opens up a socket on port
 * SERVER_PORT and listens for messages delimited with the string
 * "EOF". When it receives a message, it echos back the message
 * prefixed with "You said: ".  If nothing is heard from a client
 * within IDLE_CONNECTION_TIMEOUT seconds, we close the connection to
 * the client. All of these operations are done in a completely
 * asynchrounous manner, so if one client blocks, no other clients are
 * affected. */

// Worker constants
static const int MAX_BUF_SIZE = 4096 * 2;
static const char GREETING[] = "You said: ";
static const int IDLE_CONNECTION_TIMEOUT = 10;
static const char DELIM[] = "EOF";

// Server constants
static const int SERVER_PORT = 10000;
static const int SERVER_BACKLOG = 10;

class echobot_server;

// An echobot_worker is responsible for handling one connection, and
// replying to anything said on the supplied file descriptor.
class echobot_worker : public stream_handler,
                       public eos::timeout_handler {
 public:
   echobot_worker(eos::sdk & sdk, echobot_server * parent, int fd) : 
         stream_handler(MAX_BUF_SIZE),
         eos::timeout_handler(sdk.get_timeout_mgr()),
         t("echobot_worker"), parent(parent), fd(fd) {
      delimiter_is(DELIM, sizeof(DELIM) - 1);
      watch_stream(fd, true);
      timeout_time_is(eos::now() + IDLE_CONNECTION_TIMEOUT);
   }

   void on_message(char * msg, size_t length) {
      t.trace0("Msg received of length %zu", length);
      send_message(GREETING, sizeof(GREETING) - 1);
      send_message(msg, length);
      // Reset the idle timer
      timeout_time_is(eos::now() + IDLE_CONNECTION_TIMEOUT);
   }

   // Defined later, as the following methods require a callback to
   // the parent server for cleanup..
   void on_connection_closed();
   void on_timeout();

 private:
   eos::tracer t;
   echobot_server * parent;
   int fd;
};

// Opens a server on SERVER_PORT and creates a new echobot_worker
// whenever a new connections is forged.
class echobot_server : public eos::agent_handler,
                       public server_handler {
 public:
   eos::tracer t;
   std::unordered_map<int, echobot_worker *> workers;
   eos::sdk & sdk;

   explicit echobot_server(eos::sdk & sdk) :
         agent_handler(sdk.get_agent_mgr()),
         server_handler(SERVER_PORT, SERVER_BACKLOG),
         t("echobot_server"), workers(), sdk(sdk) {
   }

   void on_initialized() {
      t.trace0("initialized");
   }

   void on_connection(int fd, sockaddr_storage &) {
      workers.insert({{fd, new echobot_worker(sdk, this, fd)}});
   }
   
   void on_worker_complete(int fd) {
      delete workers[fd];
      workers.erase(fd);
      close(fd);
   }
};

void
echobot_worker::on_connection_closed() {
   t.trace0("Connection closed");
   // No need to worry about multiple workers accessing the
   // parent's data structure, EOS SDK agents are single threaded!
   parent->on_worker_complete(fd);
}

void
echobot_worker::on_timeout()  {
   t.trace0("Timer called");
   // If we stop hearing anything on the connection for
   // more than the IDLE_CONNECTION_TIMEOUT, then we disconnect.
   parent->on_worker_complete(fd);
}


int main(int argc, char ** argv) {
   eos::sdk sdk;
   echobot_server s(sdk);
   sdk.main_loop(argc, argv);
}
