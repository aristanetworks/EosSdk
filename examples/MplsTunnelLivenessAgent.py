#!/usr/bin/env python
# Copyright (c) 2015 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

""" This program provides an agent that sends and responds to
health-check packets in order to determine the liveliness of the
configured MPLS tunnels. """

import eossdk
import eossdk_utils

import functools
import json
import os
import pyinotify
import scapy
import scapy.fields
import scapy.layers.l2
import scapy.layers.inet
import scapy.packet
import scapy.route
import scapy.sendrecv
import socket
import struct
import sys
import time

# Requires: RPMs for scapy and EosSdk, as well as the eossdk_utils.py
# script (for debugging). Tunnel configuration is done at the bottom
# of this file in the main function.

# The main agent is located in the MplsTunnelLivenessAgent class below.

POLL_TIME = 1  # how often to send a liveness packet in seconds
TIMEOUT_TIME = 5  # seconds before a tunnel is declared dead
STARTUP_GRACEPERIOD = 0  # seconds after startup before we start checking a tunnel

# Make sure your IP tables are up to date on the switch:
#   > sudo iptables -I INPUT -p UDP --dport 17171 -j ACCEPT
UDP_PORT = 17171

MAX_PKT_SIZE = 2048  # The maximum payload size of our packet
MAX_INT = 0xffffffff  # The maximum size of a 4 byte unsigned int


class Message(object):
   """ A Message is the payload of the health-check packets that this
   agent sends out and receives. It consists of two parts. The first
   is a header that contains an number that identifies which tunnel
   the sender sent this message out of. The header also contains a
   numeric id of the packet, and finally, a number describing how many
   'entries' are in the second part of the packet. This second part is
   a list of 0 or more 'tunnel status entries'. Each entry contains a
   numeric tunnel identifier and a boolean describing whether the
   sending switch thinks that tunnel is alive or not."""

   # Header consists of (version, pid, sender's tunnel key, msg id,
   # num status entries), as integers, in little-endian:
   header_format = '<IIIII'
   header_len = struct.calcsize(header_format)
   tunnel_entry_format = '<I?'  # tunnel_key, bool
   tunnel_entry_len = struct.calcsize(tunnel_entry_format)

   def __init__(self, pid, egress_tunnel_key, msg_id, tunnel_liveness):
      self.pid = pid
      self.egress_tunnel_key = egress_tunnel_key
      self.msg_id = msg_id
      # Mapping from tunnel_key to boolean whether this is alive or not
      self.tunnel_liveness = tunnel_liveness

   def serialize(self):
      # First put the length of this packet
      ret = struct.pack(Message.header_format, 1, self.pid, self.egress_tunnel_key,
                        self.msg_id, len(self.tunnel_liveness))
      for tunnel_key, is_alive in self.tunnel_liveness.iteritems():
         ret += struct.pack(Message.tunnel_entry_format, tunnel_key, is_alive)
      if len(ret) > MAX_PKT_SIZE:
         assert False, "Packet %s too large to send!" % self.__str__()
      return ret

   def __str__(self):
      return "Message(sender_pid=%d, egress_tunnel_key=%d, id=%d, %r)" % (
         self.pid, self.egress_tunnel_key, self.msg_id, self.tunnel_liveness)

   @staticmethod
   def deserialize(buf):
      """ Given a buffer, create and return a Message from the
      buffer's contents. If the buffer does not contain a valid
      Message, this returns None.
      """
      if len(buf) < Message.header_len:
         return None
      version, pid, egress_tunnel_key, msg_id, num_entries = struct.unpack(
         Message.header_format, buf[:Message.header_len])
      if version != 1:
         return None
      msg_len = Message.header_len + Message.tunnel_entry_len * num_entries
      if len(buf) < msg_len:
         return None

      liveness = {}
      for i in xrange(Message.header_len, msg_len,
                      Message.tunnel_entry_len):
         # Unpack each status entry reported in this packet
         key, is_alive = struct.unpack(Message.tunnel_entry_format,
                                       buf[i: i + Message.tunnel_entry_len])
         liveness[key] = is_alive
      return Message(pid, egress_tunnel_key, msg_id, liveness)


class EgressTunnel(object):
   """ Contains the configuration and status of this switch's outgoing
   tunnels. """
   def __init__(self, label, nexthop_ip_addr):
      # Configurable attributes
      self.mpls_label = label
      self.nexthop_ip = nexthop_ip_addr

      # Dynamic attributes:
      # The bridging MAC of the nexthop:
      self.nexthop_eth_addr = None
      # The interface the nexthop_eth_addr lives on:
      self.egress_intf = None
      # ... and the MAC address of that interface:
      self.egress_intf_eth_addr = None
      self.last_update_time = 0
      self.is_alive = True


class RemoteTunnelStatus(object):
   """ Tracks the status of a remote tunnel (a tunnel where the packet
   sender is the remote switch). """
   def __init__(self):
      self.last_rx_msg_id = 0
      self.last_update_time = time.time()


class RemoteSwitch(object):
   """ This object stores the configuration for our outgoing tunnels to
   this remote switch, as well as a status collection containing our view on
   the liveness of that switch's tunnels to us. """
   def __init__(self, dest_ip):
      # Configuration
      # The IP address of the remote switch
      self.destination_ip = dest_ip
      # The following dictionary keeps track of our outgoing tunnels
      # to this switch. It is a mapping from integer tunnel_key to a
      # EgressTunnel()
      self.egress_tunnels = {}

      # Status
      self.last_tx_msg_id = 0
      self.last_rx_msg_id = 0
      self.pid = 0

      # The `remote_tunnel_status` variable keeps track of whether their
      # tunnels are alive or not. It is a mapping from an integer
      # tunnel_key to a RemoteTunnelStatus() object. Note that these
      # keys correspond to the remote switche's tunnel collection, and
      # is not the same as the keys for the `tunnels` variable above.
      self.remote_tunnel_status = {}

   def liveness_dict(self, cur_time):
      ret = {}
      for key, tunnel_status in self.remote_tunnel_status.items():
         time_delta = cur_time - tunnel_status.last_update_time
         if time_delta > (TIMEOUT_TIME * 10):
            # Stop sending tunnels that we haven't heard from in a
            # really long time.
            del self.remote_tunnel_status[key]
         elif time_delta > TIMEOUT_TIME:
            # Tunnel is dead!
            ret[key] = False
         else:
            ret[key] = True
      return ret


class MPLS(scapy.packet.Packet):
   """ Create an MPLS header that can be used with scapy packets """
   name = "MPLS"
   fields_desc = [ scapy.fields.BitField("label", 9, 20),
                   scapy.fields.BitField("cos", 0, 3),
                   scapy.fields.BitField("s", 1, 1),
                   scapy.fields.ByteField("ttl", 0) ]
scapy.packet.bind_layers(scapy.layers.l2.Ether, MPLS, type=0x8847)


class InotifyHandler(pyinotify.ProcessEvent):
   """ A helper class handles inotify updates """
   parent = None

   def my_init(self, **kwargs):
      self.parent = kwargs['parent']

   def process_IN_MODIFY(self, event):
      self.parent.process_config()


class MplsTunnelLivenessAgent(eossdk_utils.EosSdkAgent,
                              eossdk.AgentHandler,
                              eossdk.FdHandler,
                              eossdk.TimeoutHandler):
   """ This agent is responsible for tracking the liveness of specified
   MPLS tunnels. """
   def __init__(self, sdk, config_file="MplsTunnelLivenessConfig.json"):
      """ Create the agent. Requires an eossdk handle, as well as the
      input configuration """
      self.agent_mgr = sdk.get_agent_mgr()
      self.eth_intf_mgr = sdk.get_eth_intf_mgr()
      self.ip_intf_mgr = sdk.get_ip_intf_mgr()
      self.mac_table_mgr = sdk.get_mac_table_mgr()
      self.neighbor_table_mgr = sdk.get_neighbor_table_mgr()
      self.tracer = eossdk.Tracer("MplsTunnelLivenessAgent")
      eossdk_utils.EosSdkAgent.__init__(self)
      eossdk.AgentHandler.__init__(self, self.agent_mgr)
      eossdk.TimeoutHandler.__init__(self, sdk.get_timeout_mgr())
      eossdk.FdHandler.__init__(self)
      self.tracer.trace0("MPLS tunnel liveness agent constructed")

      self.initialized = False
      self.pid = os.getpid()

      # The l3 interface we should grab our "SRC IP" from. Read from
      # the config:
      self.src_intf = None
      self.src_ip = None  # Resolved after reading from config

      # A UDP socket that receives liveness packets from other
      # agents. Created during on_initialized
      self.rx_sock = None

      # A mapping from remote switch IP to RemoteSwitch()
      self.remote_switches = {}

      self.config_file = config_file
      self.wm = pyinotify.WatchManager()
      handler = functools.partial(InotifyHandler, parent=self)
      # pylint: disable-msg=E1101
      self.wm.watch_transient_file(config_file, pyinotify.IN_MODIFY, handler)
      # pylint: enable-msg=E1101
      self.notifier = pyinotify.AsyncNotifier(self.wm,
                                              InotifyHandler(parent=self))
      self.notifier.coalesce_events(True)
      self.inotify_fd = self.wm.get_fd()
      self.watch_readable(self.inotify_fd, True)

      # Read our initial configuration
      self.process_config()

   def on_initialized(self):
      """ Update our configured egress tunnels. Start all tunnels as
      alive, with a last_update_time of now + any grace
      period. Calculate the output interfaces for each tunnel based
      off of that tunnel's nexthop MAC address. """
      self.initialized = True
      self.tracer.trace2("Looking up the IP address for interface  " + self.src_intf)
      src_ips = self.ip_intf_mgr.ip_addrs(eossdk.IntfId(self.src_intf))
      if not src_ips:
         assert False, "No IP addresses assigned to %s" % self.src_intf
      self.src_ip = src_ips[0].addr().to_string()
      self.tracer.trace2("Using src IP address " + self.src_ip)

      self.tracer.trace2("Create the socket that receives remote probes")
      self.rx_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
      self.rx_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
      self.rx_sock.bind((self.src_ip, UDP_PORT))
      self.rx_sock.setblocking(0)
      self.watch_readable(self.rx_sock.fileno(), True)

      self.resolve_config()

   def handle_tunnel_alive(self, dst_ip, tunnel_key, tunnel):
      self.tracer.trace3("Tunnel %d to %s came back!" % (tunnel_key, dst_ip))
      # Do any other logic (a.k.a. alert another agent that
      # tunnel.mpls_label is usable again)

   def handle_tunnel_death(self, dst_ip, tunnel_key, tunnel):
      self.tracer.trace3("Tunnel %d to %s died!" % (tunnel_key, dst_ip))
      # Do any other logic (a.k.a. alert another agent that
      # tunnel.mpls_label is no longer a valid tunnel)

   def on_timeout(self):
      """ Time to send some packets to our neighbors! Our poller
      fired, so we should send out our heartbeat packets. We also
      check if we haven't heard about any of our tunnels recently, and
      if so, mark them as dead. """
      cur_time = time.time()
      for host in self.remote_switches.itervalues():
         liveness_dict = host.liveness_dict(cur_time)
         host.last_tx_msg_id += 1
         if host.last_tx_msg_id > MAX_INT:
            host.last_tx_msg_id = 1
         for key, tunnel in host.egress_tunnels.iteritems():
            msg = Message(self.pid, key, host.last_tx_msg_id, liveness_dict)
            self.send_packet(host.destination_ip, tunnel, msg)
            if tunnel.is_alive and (
               time.time() - tunnel.last_update_time > TIMEOUT_TIME):
               # There has been no updates to this tunnel at all
               # within our timeout period.
               tunnel.is_alive = False
               self.handle_tunnel_death(host.destination_ip, key, tunnel)
      # Schedule us to be called again in the future
      self.timeout_time_is(eossdk.now() + POLL_TIME)

   def on_readable(self, fd):
      """ We got a packet on our UDP port! Read the packet, update our
      views of the remote tunnel's liveness, and then parse the
      packet's payload to inspect what the remote packet thinks of
      *our* tunnel liveness. If any liveness changed, then fire our
      handlers. """
      if fd == self.inotify_fd:
         self.tracer.trace6("Inotify fd %d is readable" % self.inotify_fd)
         self.notifier.handle_read()
         return

      if fd != self.rx_sock.fileno():
         assert False, "Unknown socket became readable %d" % fd

      data, addr = self.rx_sock.recvfrom(MAX_PKT_SIZE)
      src_ip = addr[0]
      self.tracer.trace6("Received message from %r" % src_ip)
      if not data:
         self.tracer.trace7("Received empty message, ignoring.")
         return

      msg = Message.deserialize(data)
      if not msg:
         self.tracer.trace7("Received invalid message, ignoring! "
                            "First 500 bytes of pkt: %r" % data[:500])
         return

      self.tracer.trace8("Got message %s" % str(msg))

      if src_ip not in self.remote_switches:
         self.tracer.trace7("Got packet from unknown host: %r" % src_ip)
         return

      remote_switch = self.remote_switches[src_ip]
      remote_tunnel_status = remote_switch.remote_tunnel_status.setdefault(
         msg.egress_tunnel_key, RemoteTunnelStatus())

      if msg.pid != remote_switch.pid:
         # This is the either the first message we've received from
         # them, or their remote switch restarted. In any case, the
         # msg IDs they are sending will have been reset.
         remote_switch.pid = msg.pid
         remote_switch.last_rx_msg_id = 0
         remote_tunnel_status.last_rx_msg_id = 0

      # First track we got a packet from the sender's tunnel named
      # in the packet.
      if self.is_new_id(remote_tunnel_status.last_rx_msg_id, msg.msg_id):
         # Do we care about packets coming in out of order?
         remote_tunnel_status.last_update_time = time.time()
         remote_tunnel_status.last_rx_msg_id = msg.msg_id

      # Then inspect the body of the packet that tells me which of
      # my tunnel statuses the remote switch has seen.

      if not self.is_new_id(remote_switch.last_rx_msg_id, msg.msg_id):
         # We've already seen newer messages. Ignore the this.
         self.tracer.trace7("Got old message with id: %d (currently at %d)"
                            % (msg.msg_id, remote_switch.last_rx_msg_id))
         return

      remote_switch.last_rx_msg_id = msg.msg_id
      for tunnel_key, is_alive in msg.tunnel_liveness.iteritems():
         if tunnel_key not in remote_switch.egress_tunnels:
            # They are telling us about one of our egress tunnels that
            # we have no record of...
            self.tracer.trace0("Got tunnel status for an unknown key: %r" %
                               tunnel_key)
            continue
         tunnel = remote_switch.egress_tunnels[tunnel_key]
         tunnel.last_update_time = time.time()
         # Check if the remote switch thinks our egress tunnel is
         # up or down. If it changed, call our handlers!
         if tunnel.is_alive == is_alive:
            self.tracer.trace9("No change to liveness for tunnel %d" % tunnel_key)
            continue
         elif is_alive:
            tunnel.is_alive = True
            self.handle_tunnel_alive(src_ip, tunnel_key, tunnel)
         else:
            tunnel.is_alive = False
            self.handle_tunnel_death(src_ip, tunnel_key, tunnel)

   def resolve_egress_tunnel(self, tunnel):
      self.tracer.trace8("Resolve the nexthop IP %s to an ethernet address" %
                         tunnel.nexthop_ip)
      neighbor_key = eossdk.NeighborKey(
         eossdk.IpAddr(tunnel.nexthop_ip), eossdk.IntfId())
      neighbor_entry = self.neighbor_table_mgr.neighbor_entry_status(neighbor_key)
      if neighbor_entry == eossdk.NeighborEntry():
         self.tracer.trace8("Checking static ARP entries")
         neighbor_entry = self.neighbor_table_mgr.neighbor_entry(neighbor_key)
      if neighbor_entry == eossdk.NeighborEntry():
         self.tracer.trace0("IP address %r has no ARP entry" %
                            tunnel.nexthop_ip)
         assert False, "Unlearned nexthop IP %s" % tunnel.nexthop_ip
      nexthop_eth_addr = neighbor_entry.eth_addr()
      self.tracer.trace5("IP %s lives on %s" %
                         (tunnel.nexthop_ip, nexthop_eth_addr.to_string()))
      tunnel.nexthop_eth_addr = nexthop_eth_addr.to_string()

      self.tracer.trace8("Now resolving that MAC entry to an interface.")
      # TODO: Is this necessary if we send it out of the "fabric"
      # interface?
      vlan_id = 1
      mac_entry = self.mac_table_mgr.mac_entry(vlan_id, nexthop_eth_addr)
      if mac_entry.intf() == eossdk.IntfId():
         self.tracer.trace0("Mac entry %r not on any interface" %
                            tunnel.nexthop_eth_addr)
         assert False, "Unlearned nexthop MAC %s" % tunnel.nexthop_eth_addr
      intf = mac_entry.intf().to_string()
      # Convert the interface names to the kernel interface names
      intf = intf.replace("Ethernet", "et")
      intf = intf.replace("Port-Channel", "po")
      self.tracer.trace5("MAC entry %s is learned on inteface %r" %
                         (tunnel.nexthop_eth_addr, intf))
      tunnel.egress_intf = intf

      self.tracer.trace8("Looking up that interface's MAC address")
      egress_eth_addr = self.eth_intf_mgr.eth_addr(mac_entry.intf())
      if egress_eth_addr == eossdk.EthAddr():
         assert False, "Interface %s has no MAC address" % intf
      self.tracer.trace5("Intf %s has MAC address %s" %
                         (intf, egress_eth_addr.to_string()))
      tunnel.egress_intf_eth_addr = egress_eth_addr.to_string()

   def send_packet(self, dst_ip, tunnel, msg):
      """ Wrap `msg` in a UDP-over-MPLS packet, using `dst_ip` and the tunnel's
      MPLS label, and send the packet out of the tunnel's egress interface."""
      self.tracer.trace8("Sending message %s" % str(msg))
      payload = msg.serialize()
      pkt = scapy.layers.l2.Ether(src=tunnel.egress_intf_eth_addr,
                                  dst=tunnel.nexthop_eth_addr)
      pkt = (pkt / MPLS(label=tunnel.mpls_label, ttl=64) /
             scapy.layers.inet.IP(src=self.src_ip,
                                  dst=dst_ip) /
             scapy.layers.inet.UDP(dport=UDP_PORT) /
             (payload))

      # In the real world we might make this non-blocking, but for now
      # we assume packet always get sent in one go. Also, it might be
      # worth maintaining our own socket to the egress interface to
      # save us the work of creating/tearing down raw sockets
      # constantly.
      scapy.sendrecv.sendp(pkt, iface=tunnel.egress_intf, verbose=0)

   def process_config(self):
      self.tracer.trace1("Processing configuration change on %s" %
                         self.config_file)
      with open(self.config_file) as f:
         cfg = json.loads(f.read())

      if not self.initialized:
         # Write the src_intf only once.
         self.src_intf = cfg["src_intf"]

      # Clear out the previous config:
      self.remote_switches = {}
      # And signify that we are a new process by changing our
      # advertised pid. It would be preferable to just only update the
      # newly configured tunnels, but that's more complicated for now.
      self.pid -= 1
      for rs in cfg["remote_switches"]:
         dst_ip = rs["destination_ip"]
         dst = RemoteSwitch(dst_ip)
         for tunnel_key_str, tunnel_info in rs["tunnels"].iteritems():
            tunnel_key = int(tunnel_key_str)
            dst.egress_tunnels[tunnel_key] = EgressTunnel(
               tunnel_info["label"], tunnel_info["nexthop_ip"])
      self.remote_switches[dst_ip] = dst

      if self.initialized:
         self.resolve_config()

   def resolve_config(self):
      self.tracer.trace2("Resolving all of our configured tunnels")
      for host in self.remote_switches.itervalues():
         for tunnel in host.egress_tunnels.itervalues():
            tunnel.last_update_time = time.time() + STARTUP_GRACEPERIOD
            self.resolve_egress_tunnel(tunnel)
      self.timeout_time_is(eossdk.now() + POLL_TIME)

   def is_new_id(self, last_seen_id, new_id):
      # Returns True if the new_id is larger than the last_seen_id, or
      # the new_id has wrapped around.
      return (last_seen_id < new_id) or ((last_seen_id - new_id) > (MAX_INT / 2))


def main(args):
   sdk = eossdk.Sdk()
   _ = MplsTunnelLivenessAgent(sdk)
   sdk.main_loop(args)

if __name__ == "__main__":
   main(sys.argv)
