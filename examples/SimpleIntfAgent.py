#!/usr/bin/env python
# Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import sys

import EosSdk

# Listens to standard input and shuts down an interface when it
# receives a "shutdown" message. To exit, enter a blank line.
class MyTestAgent(EosSdk.AgentHandler, EosSdk.FdHandler):
   def __init__(self, intfMgr, interfaceName):
      print "This program controls the admin enabled state of the given interface"
      print " - 'shutdown' will disable the interface"
      print " - any other text will enable the interface"
      print " - an empty line will quit this program"
      self.intfMgr_ = intfMgr
      self.intfObj_ = EosSdk.IntfId(interfaceName)
      EosSdk.AgentHandler.__init__(self)
      EosSdk.FdHandler.__init__(self)  # pylint: disable-msg=W0233
      self.eventCount = 0

   def onInitialized(self):
      print "Initialized!"
      self.watchReadable(0, True)
      self.intfMgr_.adminEnabledIs(self.intfObj_, True)
      self._printPrompt()

   def onReadable(self, fd):
      print "- Fd %d is readable" % fd
      curEnabledStatus = ("enabled" if self.intfMgr_.adminEnabled(self.intfObj_)
                          else "disabled")
      print "- %s is currently %s" % (self.intfObj_.toString(), curEnabledStatus)
      msg = sys.stdin.readline()
      if msg.startswith("shut"):
         print "Shutting down %s" % self.intfObj_.toString()
         self.intfMgr_.adminEnabledIs(self.intfObj_, False)
         self.eventCount += 1
      elif msg.strip():
         print "Enabling %s" % self.intfObj_.toString()
         self.intfMgr_.adminEnabledIs(self.intfObj_, True)
         self.eventCount += 1
      else:
         print "Exiting!"
         EosSdk.agentExit()
      self._printPrompt()

   def _printPrompt(self):
      print '> ',
      sys.stdout.flush()


def main(args):
   intfMgr = EosSdk.getIntfMgr()
   testAgent = MyTestAgent(intfMgr, "Ethernet1")
   args = ["MyTestAgent"]
   EosSdk.agentMainLoop(args[0], len(args), args)
   print "Handled %d events" % testAgent.eventCount


if __name__ == '__main__':
   sys.exit(main(sys.argv))
