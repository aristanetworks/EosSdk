// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <cassert>
#include <iostream>
#include <pthread.h>
#include <string>
#include <sstream>
#include <unistd.h>

#include <eos/agent.h>
#include <eos/sdk.h>


// This simple program tests how the SDK deals with multiple
// threads. In it, we start the main loop, and once on_initialized is
// called, we start a thread (via the function run_child). If no lock
// is used, the the program will likely crash due to multiple threads
// writing to the Sysdb connection simultaneously. No crashes are
// observed when the sdk_scoped_lock is used.

// If the following #define is set, we will use the SDK lock. 
#define USE_SDK_LOCK 1


static pthread_t thread;

void *run_child(void *mgr) {
   std::cout << "[child] Starting iterations!" << std::endl;
   for(int i = 0; i < 1000; i++) {
#if USE_SDK_LOCK
      eos::sdk_scoped_lock ssl;
#endif
      std::stringstream ss;
      ss << "Iteration #" << i;
      std::string status = ss.str();
      ((eos::agent_mgr *) mgr)->status_set("index", status);
      std::cout << "[child] " << status << std::endl;
   }
   std::cout << "[child] Done!" << std::endl;
   sleep(2);
   pthread_exit(NULL);
}


class parent_handler_agent : public eos::agent_handler {
 public:
   explicit parent_handler_agent(eos::agent_mgr * mgr)
         : eos::agent_handler(mgr) {
      std::cout << "[parent_handler] Constructing" << std::endl;
   }

   void on_initialized() {
      std::cout << "[parent_handler] Initialized" << std::endl;
      int rc = pthread_create(& thread, NULL, 
                              run_child, (void *)get_agent_mgr());
      if (rc){
         std::cout << "Error:unable to create thread," << rc << std::endl;
      }
   }
};


int main(int argc, char ** argv) {
   eos::sdk sdk;
   eos::agent_mgr * mgr = sdk.get_agent_mgr();
   parent_handler_agent hwa(mgr);
   std::cout << "[parent] I'm the parent process" << std::endl;
   std::cout << "[parent] Starting main loop" << std::endl;
   sdk.main_loop(argc, argv);
}
