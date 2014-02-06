#!/usr/bin/env python
# Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import sys

import EosSdk

INTF = "Ethernet1"

# Listens to standard input and shuts down an interface when it
# receives a "shutdown" message. To exit, enter a blank line.
class MyTestAgent(EosSdk.AgentHandler, EosSdk.FdHandler):
   def __init__(self, intfMgr):
      print "This program controls the admin enabled state of Ethernet1"
      print " - 'shutdown' will disable the interface"
      print " - any other text will enable the interface"
      print " - an empty line will quit this program"
      self.intfMgr_ = intfMgr
      self.intfObj_ = EosSdk.IntfId(INTF)
      EosSdk.AgentHandler.__init__(self)
      EosSdk.FdHandler.__init__(self)

   def onInitialized(self):
      print "Initialized!"
      self.watchReadable(0, True)
      self.intfMgr_.adminEnabledIs(self.intfObj_, True)
      self._printPrompt()

   def onReadable(self, fd):
      print "- Fd %d is readable" % fd
      curEnabledStatus = ("enabled" if self.intfMgr_.adminEnabled(self.intfObj_)
                          else "disabled")
      print "- Ethernet1 is currently", curEnabledStatus
      msg = sys.stdin.readline()
      if msg.startswith("shut"):
         print "Shutting down Ethernet1"
         self.intfMgr_.adminEnabledIs(self.intfObj_, False)
      elif msg.strip():
         print "Enabling Ethernet1"
         self.intfMgr_.adminEnabledIs(self.intfObj_, True)
      else:
         print "Exiting!"
         EosSdk.agentExit()
      self._printPrompt()

   def _printPrompt(self):
      print '> ',
      sys.stdout.flush()


def main(args):
   intfMgr = EosSdk.getIntfMgr()
   testAgent = MyTestAgent(intfMgr)
   args = ["MyTestAgent"]
   EosSdk.agentMainLoop(args[0], len(args), args)


if __name__ == '__main__':
   sys.exit(main(sys.argv))
