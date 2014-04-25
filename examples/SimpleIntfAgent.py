#!/usr/bin/env python
# Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import eossdk

import sys

# Listens to standard input and shuts down an interface when it
# receives a "shutdown" message. To exit, enter a blank line.
class MyTestAgent(eossdk.AgentHandler, eossdk.FdHandler):
   def __init__(self, agentMgr, intfMgr, interfaceName):
      print "This program controls the admin enabled state of the given interface"
      print " - 'shutdown' will disable the interface"
      print " - any other text will enable the interface"
      print " - an empty line will quit this program"
      self.agentMgr_ = agentMgr
      self.intfMgr_ = intfMgr
      self.intfObj_ = eossdk.IntfId(interfaceName)
      eossdk.AgentHandler.__init__(self, agentMgr)
      eossdk.FdHandler.__init__(self)  # pylint: disable-msg=W0233
      self.eventCount = 0

   def on_initialized(self):
      print "Initialized!"
      self.watch_readable(0, True)
      self.intfMgr_.admin_enabled_is(self.intfObj_, True)
      self._printPrompt()

   def on_readable(self, fd):
      print "- Fd %d is readable" % fd
      curEnabledStatus = ("enabled" if self.intfMgr_.admin_enabled(self.intfObj_)
                          else "disabled")
      print "- %s is currently %s" % (self.intfObj_.to_string(), curEnabledStatus)
      msg = sys.stdin.readline()
      if msg.startswith("shut"):
         print "Shutting down %s" % self.intfObj_.to_string()
         self.intfMgr_.admin_enabled_is(self.intfObj_, False)
         self.eventCount += 1
      elif msg.strip():
         print "Enabling %s" % self.intfObj_.to_string()
         self.intfMgr_.admin_enabled_is(self.intfObj_, True)
         self.eventCount += 1
      else:
         print "Exiting!"
         self.agentMgr_.exit()
      self._printPrompt()

   def _printPrompt(self):
      print '> ',
      sys.stdout.flush()


def main(args):
   sdk = eossdk.Sdk()
   testAgent = MyTestAgent(sdk.get_agent_mgr(), sdk.get_intf_mgr(), "Ethernet1")
   args = ["MyTestAgent"]
   sdk.main_loop(args[0], args)
   print "Handled %d events" % testAgent.eventCount


if __name__ == '__main__':
   sys.exit(main(sys.argv))
