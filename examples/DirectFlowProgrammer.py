#!/usr/bin/env python
# Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import EosSdk
import re
import os
import sys

def createMatch(inputIntfs=None,
                ethSrc=None,
                ethSrcMask="ff:ff:ff:ff:ff:ff",
                ethDst=None,
                ethDstMask="ff:ff:ff:ff:ff:ff",
                ethType=None,
                ipSrc=None,
                ipSrcMask="255.255.255.255",
                ipDst=None,
                ipDstMask="255.255.255.255"):
   match = EosSdk.FlowMatch()
   matchFieldSet = EosSdk.FlowMatchFieldSet()
   if inputIntfs is not None:
      # Until we have correct swig support for std::set,
      # need to add each interface individually
      matchFieldSet.inputIntfsIs(True)
      for intfId in inputIntfs:
         match.inputIntfSet(intfId)
   if ethSrc is not None:
      matchFieldSet.ethSrcIs(True)
      ethSrc = EosSdk.EthAddr(ethSrc)
      ethSrcMask = EosSdk.EthAddr(ethSrcMask)
      match.ethSrcIs(ethSrc, ethSrcMask)
   if ethDst is not None:
      matchFieldSet.ethDstIs(True)
      ethDst = EosSdk.EthAddr(ethDst)
      ethDstMask = EosSdk.EthAddr(ethDstMask)
      match.ethDstIs(ethDst, ethDstMask)
   if ethType is not None:
      matchFieldSet.ethTypeIs(True)
      match.ethTypeIs(ethType)
   if ipSrc is not None:
      matchFieldSet.ipSrcIs(True)
      ipSrc = EosSdk.IpAddr(ipSrc)
      ipSrcMask = EosSdk.IpAddr(ipSrcMask)
      match.ipSrcIs(ipSrc, ipSrcMask)
   if ipDst is not None:
      matchFieldSet.ipDstIs(True)
      ipDst = EosSdk.IpAddr(ipDst)
      ipDstMask = EosSdk.IpAddr(ipDstMask)
      match.ipDstIs(ipDst, ipDstMask)
   match.matchFieldSetIs(matchFieldSet)
   return match

def createAction(outputIntfs=None,
                 ethSrc=None,
                 ethDst=None,
                 ipSrc=None,
                 ipDst=None):
   action = EosSdk.FlowAction()
   actionSet = EosSdk.FlowActionSet()
   if outputIntfs is not None:
      # Until we have correct swig support for std::set,
      # need to add each interface individually
      actionSet.setOutputIntfsIs(True)
      for intfId in outputIntfs:
         action.outputIntfSet(intfId)
   if ethSrc is not None:
      actionSet.setEthSrcIs(True)
      newEthSrc = EosSdk.EthAddr(ethSrc)
      action.ethSrcIs(newEthSrc)
   if ethDst is not None:
      actionSet.setEthDstIs(True)
      newEthDst = EosSdk.EthAddr(ethDst)
      action.ethDstIs(newEthDst)
   if ipSrc is not None:
      actionSet.setIpSrcIs(True)
      newIpSrc = EosSdk.IpAddr(ipSrc)
      action.ipSrcIs(newIpSrc)
   if ipDst is not None:
      actionSet.setIpDstIs(True)
      newIpDst = EosSdk.IpAddr(ipDst)
      action.ipDstIs(newIpDst)
   action.actionSetIs(actionSet)
   return action

class FlowHandlerTrampoline(EosSdk.FlowHandler):
   # Multiple inheritance doesn't work great with our python bindings
   # at this point, so we have to use a trampoline class
   # to be notified of changes to flows, instead of just having
   # the DirectFlowProgrammer also inhering from EosSdk.FlowHandler

   def __init__(self, parent):
      self.parent_ = parent
      EosSdk.FlowHandler.__init__(self)
      # Register callback for the status of all flows
      EosSdk.FlowHandler.watchAllFlows(self, True)
      
   def onFlowStatus(self, name, status):        # pylint: disable-msg=W0221
      self.parent_.onFlowStatus(name, status)

class DirectFlowProgrammer(EosSdk.AgentHandler,
                           EosSdk.FdHandler):
   
   def __init__(self):
      self.directFlowMgr_ = EosSdk.getDirectflowMgr()
      self.flowHandlerTrampoline_ = None
      EosSdk.AgentHandler.__init__(self)
      EosSdk.FdHandler.__init__(self)           # pylint: disable-msg=W0233
   
   def onInitialized(self):
      # Resynchronize initial flows
      # Uncomment once we've added hitless resync support to the API:
      # self.directFlowMgr_.resyncInit()
      # Add default flow entry. In this case, drop all IPv4 traffic.
      defaultEntry = EosSdk.FlowEntry("DefaultFlow",
                                      createMatch(ipDst="0.0.0.0",
                                                  ipDstMask="0.0.0.0"),
                                      createAction(outputIntfs=[]),
                                      0)
      self.directFlowMgr_.flowEntrySet(defaultEntry)
      # Uncomment once we've added hitless resync support to the API:
      # self.directFlowMgr_.resyncComplete()

      # Set up the FlowHandlerTrampoline to be notified of flow
      # status changes
      self.flowHandlerTrampoline_ = FlowHandlerTrampoline(self)
      self.watchAllFlows(True)
      
      # Now start accepting input on stdin
      self.watchReadable(sys.stdin.fileno(), True)
   
   def onReadable(self, fd):
      # Handle input on stdin of the format:
      # NAME (add|delete) IPADDR INTERFACE
      # and adds/deletes a flow that matches on that destination ip address
      # and outputs that flow on the given interface
      buf = os.read(fd, 4096)
      for line in buf.split("\n"):
         if not line:
            continue
         m = re.search("(\S+) (add|delete) (\d+.\d+.\d+.\d+) +(\S+)", line)
         if not m:
            print "Could not match line:", line
            continue
         name = m.group(1)
         operation = m.group(2)
         if operation == "add":
            match = createMatch(ipDst=m.group(3),
                                ipDstMask="255.255.255.255")
            outputIntf = EosSdk.IntfId(m.group(4))
            action = createAction(outputIntfs=[ outputIntf ])
            priority = 100
            entry = EosSdk.FlowEntry(name,
                                     match,
                                     action,
                                     priority)
            self.directFlowMgr_.flowEntrySet(entry)
         else:
            assert operation == "delete"
            self.directFlowMgr_.flowEntryDel(name)
      
   def onFlowStatus(self, name, status):
      print "Flow", name, "status changed to", status

programmer = DirectFlowProgrammer()
EosSdk.agentMainLoop("DirectFlowProgrammer", len(sys.argv), sys.argv)
