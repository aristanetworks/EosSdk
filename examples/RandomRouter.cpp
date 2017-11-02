// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/fd.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/ip_route.h>
#include <eos/sdk.h>

#include <assert.h>
#include <stdio.h>
#include <unistd.h>


#define BUF_SIZE 1024

// Our agent! This program listens to stdin, and when a route is
// entered, applies it as a static route pointing to a random
// interface that is operationally up. Additionally, whenever a link
// is administratively disabled (i.e. someone issued a "shutdown" from
// the CLI), move all routes pointing to that interface to some other
// connected interface.
class random_router : public eos::agent_handler,
                      public eos::intf_handler,
                      public eos::fd_handler {
 public:
   explicit random_router(eos::sdk & sdk)
      : eos::agent_handler(sdk.get_agent_mgr()),
        eos::intf_handler(sdk.get_intf_mgr()),
        tag_id(42) {
      printf("Initializing the Random Router...\n");
      fflush(stdout);
      route_mgr = sdk.get_ip_route_mgr();
      route_mgr->tag_is(tag_id);
   }

   void on_initialized() {
      printf("... and we're initialized!\n");
      fflush(stdout);
      // All state has been sync'd with Sysdb. We're good to go!
      // Watch stdin:
      watch_readable(0, true);
      watch_all_intfs(true);
   }

   void on_readable(int fd) {
      printf("Stdin (fd %d) is readable\n", fd);
      assert(fd == 0);
      char buf[BUF_SIZE];
      int bytes = read(0, buf, BUF_SIZE - 1);
      if(bytes > 0) {
         buf[bytes] = '\0';
         eos::ip_prefix_t new_prefix;
         bool valid_pfx = eos::parse_ip_prefix(buf, &new_prefix);
         if(!valid_pfx) {
            printf("! Invalid IP prefix specified.\n");
            fflush(stdout);
            return;
         }
         // Create a new ip_route for this prefix
         eos::ip_route_key_t key(new_prefix);
         eos::ip_route_t route(key);
         route.tag_is(tag_id);
         route_mgr->ip_route_set(route);

         // And set a random interface as its nexthop!
         eos::intf_id_t i = get_intf(last_used_intf);
         eos::ip_route_via_t via(key);
         via.intf_is(i);
         route_mgr->ip_route_via_set(via);
         printf( "Set route %s to have nexthop %s\n",
                 new_prefix.to_string().c_str(),
                 i.to_string().c_str() );
         fflush(stdout);
         last_used_intf = i;
      }
   }

   void on_admin_enabled(eos::intf_id_t intf, bool enabled) {
      printf("Interface %s changed state. Enabled: %d\n",
             intf.to_string().c_str(), enabled);
      fflush(stdout);
      if(enabled) return; // We don't care if a new intf was enabled.

      eos::intf_id_t next_intf = get_intf(intf);
      for(eos::ip_route_iter_t ri = route_mgr->ip_route_iter(); ri; ++ri) {
         for(eos::ip_route_via_iter_t vi = route_mgr->ip_route_via_iter((*ri).key());
             vi; ++vi) {
            if((*vi).intf() == intf) {
               // This via is pointing to the shutdown interface!
               eos::ip_route_via_t new_via(*vi);
               new_via.intf_is(next_intf);
               printf("Moving route %s to %s\n",
                      (*vi).route_key().prefix().to_string().c_str(),
                      new_via.intf().to_string().c_str());
               fflush(stdout);
               route_mgr->ip_route_via_del(*vi);
               route_mgr->ip_route_via_set(new_via);
            }
         }
      }
   }

   eos::intf_id_t get_intf(eos::intf_id_t cur_intf) {
      for(eos::intf_iter_t i = get_intf_mgr()->intf_iter(); i; ++i){
         if(*i == cur_intf ||
            get_intf_mgr()->oper_status(*i) != eos::INTF_OPER_UP ||
            !get_intf_mgr()->admin_enabled(*i)) {
            // Don't use the same interface or a down'd interface.
            continue;
         }
         return *i;
      }
      printf( "No other connected interfaces. Using the same interface.\n" );
      fflush(stdout);
      return cur_intf;
   }

 private:
   uint32_t tag_id;
   eos::intf_id_t last_used_intf;

   // EosSdk state managers:
   eos::ip_route_mgr * route_mgr;
};

int main(int argc, char ** argv) {
   eos::sdk sdk;
   random_router rr(sdk);
   sdk.main_loop(argc, argv);
}
