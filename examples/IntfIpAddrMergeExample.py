#!/usr/bin/env python3
# Copyright (c) 2019 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

import eossdk
import sys

# This example shows how to merge IP address configuration for a
# given interface from more than one agent.
# IP address is configured for an interface through both eAPI and EosSdk.
# When merge is enabled, IP address configuration from both eAPI and EosSdk
# is merged to derive the operational set of IP addresses of the interface.
# When merge is disabled, only the IP address configuration from the higher
# priority source (in this case eAPI) becomes the operational IP address
# configuration of the interface.


class IntfIpAddrMergeAgent(eossdk.AgentHandler, eossdk.IpIntfHandler):
   def __init__(self, sdk):
      self.agentMgr = sdk.get_agent_mgr()
      self.ipIntfMgr = sdk.get_ip_intf_mgr()
      self.eapiMgr = sdk.get_eapi_mgr()
      eossdk.AgentHandler.__init__(self, self.agentMgr)
      eossdk.IpIntfHandler.__init__(self, self.ipIntfMgr)
      self.tracer = eossdk.Tracer("IntfIpAddrMergeAgent")

      self.intfId = eossdk.IntfId("Ethernet1")
      self.ip1 = eossdk.IpAddrMask(eossdk.IpAddr("1.1.1.1"), 24)
      self.ip2 = eossdk.IpAddrMask(eossdk.IpAddr("2.2.2.2"), 24)

      self.merge_expected_add_callbacks = []
      self.unmerge_expected_del_callbacks = []

      self.tracer.trace0("Agent constructed")

   def on_initialized(self):
      """ Callback provided by AgentHandler when all state is synchronized """
      self.tracer.trace0("Initialized")
      # Watch the interface to recieve callbacks when an IP address is
      # added or deleted from the interface
      self.watch_ip_intf(self.intfId, True)

      # Configure IP address through eAPI
      self.configure_eapi_ip_addrs()
      # Configure IP address through EosSdk
      self.configure_ip_addrs()
      # Enable IP address merge
      self.merge_ip_addrs_on()

   def configure_eapi_ip_addrs(self):
      self.tracer.trace0("Configure IP address on " + self.intfId.to_string() +
                         " through eAPI")
      self.eapiMgr.run_config_cmds([
         "interface " + self.intfId.to_string(),
         "no switchport",
         "ip address " + self.ip1.to_string()])

   def configure_ip_addrs(self):
      self.tracer.trace0("Configure IP address on " + self.intfId.to_string() +
                         " through EosSdk")
      self.ipIntfMgr.ip_addr_add(self.intfId, self.ip2)

   def merge_ip_addrs_on(self):
      self.tracer.trace0("Enable IP address merge on " + self.intfId.to_string())
      self.ipIntfMgr.ip_addr_merge_mode_is(self.intfId, True)
      assert self.ipIntfMgr.ip_addr_merge_mode(self.intfId)

      # Since IP address merge is enabled on the interface,
      # we expect to see add callbacks for IP addresses configured
      # by both eAPI and EosSdk.
      self.merge_expected_add_callbacks.extend([self.ip1, self.ip2])

   def merge_ip_addrs_off(self):
      self.tracer.trace0("Disable IP address merge on " + self.intfId.to_string())
      self.ipIntfMgr.ip_addr_merge_mode_is(self.intfId, False)
      assert not self.ipIntfMgr.ip_addr_merge_mode(self.intfId)

      # IP address merge is now disabled on the interface,
      # Since eAPI has higher priority than EosSdk, only the IP address
      # configured by eAPI should remain configured on the interface and we
      # expect to see del callbacks for the IP address configured by EosSdk.
      self.unmerge_expected_del_callbacks.append(self.ip2)

   def on_ip_addr_add(self, intfId, addr):
      """ Callback provided by IpIntfHandler when an IP address is added
          to the interface """
      self.tracer.trace0("IP address " + addr.to_string() + " added to " +
                         intfId.to_string())

      if addr in self.merge_expected_add_callbacks:
         self.merge_expected_add_callbacks.remove(addr)
      else:
         self.tracer.trace0("Unexpected IP address " + addr.to_string() +
                            " add callback for " + intfId.to_string())

      if not self.merge_expected_add_callbacks:
         self.tracer.trace0("Expected add callbacks received for " +
                            self.intfId.to_string())
         # Getter should return IP addresses configured by both eAPI
         # and EosSdk.
         intf_addrs = self.ipIntfMgr.ip_addrs(self.intfId)
         assert sorted(intf_addrs) == sorted((self.ip1, self.ip2))

         # Now disable IP address merge so that the interface will only
         # have the IP address configured by eAPI.
         self.merge_ip_addrs_off()

   def on_ip_addr_del(self, intfId, addr):
      """ Callback provided by IpIntfHandler when an IP address is deleted
          from the interface """
      self.tracer.trace0("IP address " + addr.to_string() + " deleted from " +
                         intfId.to_string())

      if addr in self.unmerge_expected_del_callbacks:
         self.unmerge_expected_del_callbacks.remove(addr)
      else:
         self.tracer.trace0("Unexpected IP address " + addr.to_string() +
                            " del callback for " + intfId.to_string())

      if not self.unmerge_expected_del_callbacks:
         self.tracer.trace0("Expected del callbacks received for " +
                            self.intfId.to_string())
         # Getter should return only the IP address configured by eAPI.
         assert self.ipIntfMgr.ip_addrs(self.intfId) == (self.ip1,)

if __name__ == "__main__":
   sdk_ = eossdk.Sdk()
   # Assign the agent instance to a variable so it remains in scope and
   # is not deleted:
   _ = IntfIpAddrMergeAgent(sdk_)
   sdk_.main_loop(sys.argv)
