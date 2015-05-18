# Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import eossdk

class NexthopGroupSyncer( eossdk.NexthopGroupHandler ):
   """
   The NexthopGroupSyncer class helps hitlessly manage nexthop
   group deletion by ensuring that we never delete a nexthop group
   that is still active. It exposes a similar interface to the
   nexthop_group_mgr for creating and deleting nexthop groups.
   """
   
   def __init__( self, nexthop_group_mgr ):
      self.nexthop_group_mgr_ = nexthop_group_mgr
      # Whether or not we're in resync mode
      self.in_resync_mode_ = False
      # Set of nexthop group names we've seen during resync
      self.seen_groups_ = set()
      # Set of nexthop groups to delete at the point that they
      # are no longer active
      self.groups_to_delete_ = set()
      eossdk.NexthopGroupHandler.__init__( self, nexthop_group_mgr )
      self.watch_all_nexthop_groups(True)

   #
   # Public Methods - see the nexthop_group module for descriptions
   #
      
   def resync_init( self ):
      self.seen_groups_ = set()
      self.in_resync_mode_ = True

   def resync_complete( self ):
      assert self.in_resync_mode_
      for nexthop_group in self.nexthop_group_mgr_.nexthop_group_iter():
         if nexthop_group.name() not in self.seen_groups_:
            # Nexthop group no longer exists, delete it (once it is no
            # longer active)
            self.nexthop_group_del( nexthop_group.name() )
      self.seen_groups_ = set()
      self.in_resync_mode_ = False

   def nexthop_group_set( self, nexthop_group ):
      # Remove the nexthop group from our list to delete
      self.groups_to_delete_.remove( nexthop_group.name() )
      self.nexthop_group_mgr_.nexthop_group_set( nexthop_group )
      if self.in_resync_mode_:
         self.seen_groups_.add( nexthop_group.name() )

   def nexthop_group_del( self, nexthop_group_name ):
      if not self.nexthop_group_mgr_.active( nexthop_group_name ):
         # Nexthop group is not active, can delete immediately
         self.nexthop_group_mgr_.nexthop_group_del( nexthop_group_name )
      else:
         # Nexthop group still in use, wait for it to become inactive
         # before deleting
         self.groups_to_delete_.add( nexthop_group_name )
      if self.in_resync_mode_:
         self.seen_groups_.remove( nexthop_group_name )

   #
   # Private Methods
   #

   def on_nexthop_group_active( self, nexthop_group_name, active ):
      if not active and ( nexthop_group_name in self.groups_to_delete_ ):
         self.nexthop_group_mgr_.nexthop_group_del( nexthop_group_name )
         self.groups_to_delete_.remove( nexthop_group_name )
