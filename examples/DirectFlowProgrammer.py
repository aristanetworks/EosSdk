#!/usr/bin/env python3
# Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import eossdk

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
   match = eossdk.FlowMatch()
   matchFieldSet = eossdk.FlowMatchFieldSet()
   if inputIntfs is not None:
      # Until we have correct swig support for std::set,
      # need to add each interface individually
      matchFieldSet.input_intfs_is(True)
      match.input_intfs_is(tuple([intfId for intfId in inputIntfs]))
   if ethSrc is not None:
      matchFieldSet.eth_src_is(True)
      ethSrc = eossdk.EthAddr(ethSrc)
      ethSrcMask = eossdk.EthAddr(ethSrcMask)
      match.eth_src_is(ethSrc, ethSrcMask)
   if ethDst is not None:
      matchFieldSet.eth_dst_is(True)
      ethDst = eossdk.EthAddr(ethDst)
      ethDstMask = eossdk.EthAddr(ethDstMask)
      match.eth_dst_is(ethDst, ethDstMask)
   if ethType is not None:
      matchFieldSet.eth_type_is(True)
      match.eth_type_is(ethType)
   if ipSrc is not None:
      matchFieldSet.ip_src_is(True)
      ipSrc = eossdk.IpAddr(ipSrc)
      ipSrcMask = eossdk.IpAddr(ipSrcMask)
      match.ip_src_is(ipSrc, ipSrcMask)
   if ipDst is not None:
      matchFieldSet.ip_dst_is(True)
      ipDst = eossdk.IpAddr(ipDst)
      ipDstMask = eossdk.IpAddr(ipDstMask)
      match.ip_dst_is(ipDst, ipDstMask)
   match.match_field_set_is(matchFieldSet)
   return match


def createAction(outputIntfs=None,
                 ethSrc=None,
                 ethDst=None,
                 ipSrc=None,
                 ipDst=None):
   action = eossdk.FlowAction()
   actionSet = eossdk.FlowActionSet()
   if outputIntfs is not None:
      # Until we have correct swig support for std::set,
      # need to add each interface individually
      actionSet.set_output_intfs_is(True)
      action.output_intfs_is(tuple([intfId for intfId in outputIntfs]))
   if ethSrc is not None:
      actionSet.set_eth_src_is(True)
      newEthSrc = eossdk.EthAddr(ethSrc)
      action.eth_src_is(newEthSrc)
   if ethDst is not None:
      actionSet.set_eth_dst_is(True)
      newEthDst = eossdk.EthAddr(ethDst)
      action.eth_dst_is(newEthDst)
   if ipSrc is not None:
      actionSet.set_ip_src_is(True)
      newIpSrc = eossdk.IpAddr(ipSrc)
      action.ip_src_is(newIpSrc)
   if ipDst is not None:
      actionSet.set_ip_dst_is(True)
      newIpDst = eossdk.IpAddr(ipDst)
      action.ip_dst_is(newIpDst)
   action.action_set_is(actionSet)
   return action


class DirectFlowProgrammer(eossdk.AgentHandler,
                           eossdk.FdHandler,
                           eossdk.FlowHandler):

   def __init__(self, agentMgr, directFlowMgr):
      self.agentMgr_ = agentMgr
      self.directFlowMgr_ = directFlowMgr
      eossdk.AgentHandler.__init__(self, agentMgr)
      eossdk.FdHandler.__init__(self)
      eossdk.FlowHandler.__init__(self, directFlowMgr)
      self.changes = 0

   def on_initialized(self):
      # Resynchronize initial flows
      # Uncomment once we've added hitless resync support to the API:
      # self.directFlowMgr_.resync_init()
      # Add default flow entry. In this case, drop all IPv4 traffic.
      defaultEntry = eossdk.FlowEntry("DefaultFlow",
                                      createMatch(ipDst="0.0.0.0",
                                                  ipDstMask="0.0.0.0"),
                                      createAction(outputIntfs=[]),
                                      0)
      self.directFlowMgr_.flow_entry_set(defaultEntry)
      # Uncomment once we've added hitless resync support to the API:
      # self.directFlowMgr_.resync_complete()

      # Now start accepting input on stdin
      self.watch_all_flows(True)
      self.watch_readable(sys.stdin.fileno(), True)

   def on_readable(self, fd):
      # Handle input on stdin of the format:
      # NAME (add|delete) IPADDR INTERFACE
      # and adds/deletes a flow that matches on that destination ip address
      # and outputs that flow on the given interface
      buf = os.read( fd, 4096 ).decode().strip()
      if not buf:
         self.agentMgr_.exit()
      for line in buf.split("\n"):
         if not line:
            continue
         m = re.search(r"(\S+) (add|delete) (\d+.\d+.\d+.\d+) +(\S+)", line)
         if not m:
            print( "Could not match line:", line )
            continue
         name = m.group(1)
         operation = m.group(2)
         if operation == "add":
            match = createMatch(ipDst=m.group(3),
                                ipDstMask="255.255.255.255")
            outputIntf = eossdk.IntfId(m.group(4))
            action = createAction(outputIntfs=[ outputIntf ])
            priority = 100
            entry = eossdk.FlowEntry(name,
                                     match,
                                     action,
                                     priority)
            self.directFlowMgr_.flow_entry_set(entry)
         else:
            assert operation == "delete"
            self.directFlowMgr_.flow_entry_del(name)

   def on_flow_status(self, name, status):
      print( "Flow", name, "status changed to", status )
      self.changes += 1


def main(args):
   sdk = eossdk.Sdk("DirectFlowProgrammer")
   programmer = DirectFlowProgrammer(sdk.get_agent_mgr(), sdk.get_directflow_mgr())
   sdk.main_loop(sys.argv)
   print( "Saw %d flow status changes" % programmer.changes )


if __name__ == '__main__':
   sys.exit(main(sys.argv))
