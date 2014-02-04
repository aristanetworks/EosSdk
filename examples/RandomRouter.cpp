// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/agent.h>
#include <eos/fd.h>
#include <eos/intf.h>
#include <eos/ip.h>
#include <eos/ip_route.h>

#include <assert.h>
#include <stdio.h>
#include <unistd.h>


#define BUF_SIZE 1024
#define APP_ID 123


// Structures for iterator storage:
struct intf_holder {
   bool stop_on_seen_intf;
   eos::intf_id_t intf;
};
struct route_holder {
   eos::ip_route_t route;
   eos::intf_id_t original_intf;
   eos::intf_id_t new_intf;
};

// EosSdk state managers:
eos::intf_mgr * intf_mgr;
eos::ip_route_mgr * route_mgr;

// Our agent! This program listens to stdin, and when a route is
// entered, applies it as a static route pointing to a random
// interface that is operationally up. Additionally, whenever a link
// is administratively disabled (i.e. someone issued a "shutdown" from
// the CLI), move all routes pointing to that interface to some other
// interface.
class random_router : public eos::agent_handler,
                      public eos::intf_handler,
                      public eos::fd_handler {
 public:
   random_router() {
      printf("Initializing the Random Router...\n");
   }

   void on_initialized() {
      printf("... and we're initialized!\n");
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
            return;
         }
         // Create a new ip_route for this prefix
         eos::ip_route_key_t key(new_prefix);
         eos::ip_route_t route(key);
         route.tag = APP_ID;
         route.persistent = true;
         route_mgr->ip_route_set(route);

         // And set a random interface as its nexthop!
         eos::intf_id_t i = get_intf(last_used_intf);
         eos::ip_route_via_t via(key);
         via.intf = i;
         route_mgr->ip_route_via_set(via);
         printf( "Set route %s to have nexthop %s\n",
                 new_prefix.to_string().c_str(),
                 i.to_string().c_str() );
         last_used_intf = i;
      }
   }

   static bool update_via_nexthops(const eos::ip_route_via_t &via, void * rh_void) {
      route_holder * rh = static_cast<route_holder*>(rh_void);
      if(via.intf == rh->original_intf) {
         eos::ip_route_via_t new_via(via);
         new_via.intf = rh->new_intf;
         printf("Moving route %s to %s\n",
                via.route_key.prefix.to_string().c_str(),
                new_via.intf.to_string().c_str());
         route_mgr->ip_route_via_set(new_via);
      }
      return true;
   }

   static bool check_route(const eos::ip_route_t &route, void * rh_void) {
      if(route.tag != APP_ID) {
         // Ignore routes not installed by this agent
         return true;
      }
      route_holder * rh = static_cast<route_holder*>(rh_void);
      rh->route = route;
      route_mgr->ip_route_via_foreach(route.key, update_via_nexthops, rh_void);
      return true;
   }

   void on_admin_enabled(eos::intf_id_t intf, bool enabled) {
      printf("Interface %s changed state. Enabled: %d\n",
             intf.to_string().c_str(), enabled);
      if(enabled) return; // We don't care if a new intf was enabled.

      eos::intf_id_t next_intf = get_intf(intf);
      route_holder rh;
      rh.original_intf = intf;
      rh.new_intf = next_intf;
      route_mgr->ip_route_foreach(check_route, &rh);
   }


   static bool find_connected_intf(eos::intf_id_t i, void * ih_void) {
      intf_holder * ih = static_cast<intf_holder*>(ih_void);
      if(intf_mgr->oper_status(i) == eos::INTF_OPER_UP && ih->intf != i) {
         ih->intf = i;
         return false;
      }
      return !ih->stop_on_seen_intf || ih->intf != i;
   }

   eos::intf_id_t get_intf(eos::intf_id_t cur_intf) {
      intf_holder ih;
      ih.stop_on_seen_intf = false;
      ih.intf = cur_intf;
      // Look for a connected interfaces, starting at the last interface
      intf_mgr->intf_foreach(find_connected_intf, &ih, cur_intf);

      if(cur_intf == ih.intf) {
         // We got to the end without finding an interface. Let's
         // start again from the beginning.
         ih.stop_on_seen_intf = true;
         intf_mgr->intf_foreach(find_connected_intf, &ih);
      }
      if(cur_intf == ih.intf) {
         printf( "No other connected interfaces. Using the same interface.\n" );
      }
      return ih.intf;
   }

 private:
   eos::intf_id_t last_used_intf;
};

int main(int argc, char ** argv) {
   intf_mgr = eos::get_intf_mgr();
   route_mgr = eos::get_ip_route_mgr();
   random_router rr;
   eos::agent_main_loop("RandomRouter", argc, argv);
}
