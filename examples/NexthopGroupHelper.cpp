// Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <eos/nexthop_group.h>
#include <unordered_set>

class NexthopGroupSyncer : public eos::nexthop_group_handler {
 public:
   explicit NexthopGroupSyncer(eos::nexthop_group_mgr * nhgm)
         : eos::nexthop_group_handler(nhgm),
           in_resync_mode_(false) {
      // Register to be notified about all group changes
      watch_all_nexthop_groups(true);
   }
   
   void resync_init() {
      seen_groups_.clear();
      in_resync_mode_ = true;
   }
      
   void resync_complete() {
      assert(in_resync_mode_);
      for (auto i = get_nexthop_group_mgr()->nexthop_group_iter(); i; ++i) {
         if (seen_groups_.count(i->name()) == 0) {
            // Group exists, but has not been added by the user. Delete
            // it once it is no longer active
            nexthop_group_del(i->name());
         }
      }
      seen_groups_.clear();
      in_resync_mode_ = false;
   }
   
   void nexthop_group_set(eos::nexthop_group_t const & nexthop_group) {
      // Remove the group from our list to delete
      groups_to_delete_.erase(nexthop_group.name());
      get_nexthop_group_mgr()->nexthop_group_set(nexthop_group);
      if (in_resync_mode_) {
         seen_groups_.insert(nexthop_group.name());
      }
   }
   
   void nexthop_group_del(std::string const & nexthop_group_name) {
      if (!get_nexthop_group_mgr()->active(nexthop_group_name)) {
         // Nexthop group is not active, can delete immediately
         get_nexthop_group_mgr()->nexthop_group_del(nexthop_group_name);
      } else {
         // Nexthop group still in use, wait for it to become inactive
         // before deleting
         groups_to_delete_.insert(nexthop_group_name);
      }
      if (in_resync_mode_) {
         seen_groups_.erase(nexthop_group_name);
      }
   }
   
 private:
   void on_nexthop_group_active(std::string const & nexthop_group_name,
                                bool active) {
      if(!active && (groups_to_delete_.count(nexthop_group_name))) {
         // Nexthop group is no longer active, delete it
         get_nexthop_group_mgr()->nexthop_group_del(nexthop_group_name);
         groups_to_delete_.erase(nexthop_group_name);
      }
   }
   
   bool in_resync_mode_;
   // Set of nexthop group names we've seen during resync
   std::unordered_set<std::string> seen_groups_;
   // Set of nexthop groups to delete at the point that they
   // are no longer active
   std::unordered_set<std::string> groups_to_delete_;

};
