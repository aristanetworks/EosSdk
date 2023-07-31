#!/usr/bin/env python3
# Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import eossdk
import eossdk_utils

import argparse
import functools
import pyinotify
import sys

# The following example shows how to integrate pyinotify with an EOS
# SDK agent and react to a file changing on disk. Here as an example
# of the agent's usage (where lines starting with " >" are operations
# that were performed in a different shell):

#  bash# TRACE=FileWatcher*,EosSdkFd* ./InotifyExample.py /tmp/foobar.txt
#  [Warning] AGENT_PROCESS_NAME is not set; using agent name 'f'
#  2015-06-17 11:49:31.009714 27441 FileWatcher          0 Watching '/tmp/foobar.txt'
#  2015-06-17 11:49:31.065377 27441 FileWatcher          0 Watching inotify fd: 4
#     > echo "test1" > /tmp/foobar.txt
#  File created
#  2015-06-17 11:53:21.456473 27441 FileWatcher          0 Re-processing config
#  File changed
#  2015-06-17 11:53:21.456667 27441 FileWatcher          0 Re-processing config
#     > rm /tmp/foobar.txt
#  File deleted
#     > touch /tmp/foobar.txt
#  File created
#  2015-06-17 11:55:01.329015 27441 FileWatcher          0 Re-processing config
#     > echo "test2" >> /tmp/foobar.txt
#  File changed
#  2015-06-17 11:55:39.751967 27441 FileWatcher          0 Re-processing config


class InotifyHandler(pyinotify.ProcessEvent):
   def my_init(self, parent):  # pylint: disable-msg=W0221
      # We have to ignore some pylint messages because the pyinotify
      # library defines classes in a funky manner.
      self.p = parent  # pylint: disable-msg=W0201

   def process_IN_MODIFY(self, event):
      print( "File changed" )
      self.p.process_file()

   def process_IN_CREATE(self, event):
      print( "File created" )
      self.p.process_file()

   def process_IN_DELETE(self, event):
      # In this example, we don't take an action on file deletion.
      print( "File deleted" )


class FileWatcher(eossdk_utils.EosSdkAgent,
                  eossdk.AgentHandler,
                  eossdk.FdHandler):
   def __init__(self, filename):
      self.agent_mgr = sdk.get_agent_mgr()
      self.tracer = eossdk.Tracer("FileWatcher")
      eossdk_utils.EosSdkAgent.__init__(self)
      eossdk.AgentHandler.__init__(self, self.agent_mgr)
      eossdk.FdHandler.__init__(self)
      self.tracer.trace0("Watching %r" % filename)

      self.wm = pyinotify.WatchManager()
      # Pass the InotifyHandler's that wille be created a pointer to
      # ourselves by wrapping it in functools.partial:
      handler = functools.partial(InotifyHandler, parent=self)

      # pylint: disable-msg=E1101
      self.wm.watch_transient_file(filename, pyinotify.IN_MODIFY, handler)
      # pylint: enable-msg=E1101
      self.inotifier = pyinotify.AsyncNotifier(self.wm,
                                               InotifyHandler(parent=self))
      # We coalesce events because some editors (or unix operations) cause
      # multiple changes on one save.
      self.inotifier.coalesce_events(True)

      # Now that we've set up our inotify watcher and notifier, grab
      # the underlying file descriptor and pass it to the SDK to be
      # watched. When the OS detects a change to the file, we'll
      self.inotify_fd = self.wm.get_fd()
      self.tracer.trace0("Watching inotify fd: %d" % self.inotify_fd)
      self.watch_readable(self.inotify_fd, True)

   def on_readable(self, fd):
      if fd == self.inotify_fd:
         self.inotifier.handle_read()

   def process_file(self):
      self.tracer.trace0("Re-processing config")

if __name__ == "__main__":
   sdk = eossdk.Sdk()
   parser = argparse.ArgumentParser(
      description="Watch a file for changes using EOS SDK's `fd` module.")
   parser.add_argument("filename", help="the file to watch")
   args = parser.parse_args()
   _ = FileWatcher(args.filename)
   sdk.main_loop(sys.argv)
