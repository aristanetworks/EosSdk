// Copyright (c) 2017 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "MplsTunnelLivenessAgent.hpp"

uint32_t CRC_32_POLY = 0x82608edb;

uint32_t crc_table[256] = {
   0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
   0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
   0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
   0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
   0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
   0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
   0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
   0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
   0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
   0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
   0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
   0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
   0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
   0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
   0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
   0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,

   0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
   0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
   0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
   0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
   0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
   0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
   0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
   0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
   0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
   0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
   0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
   0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
   0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
   0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
   0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
   0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,

   0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
   0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
   0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
   0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
   0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
   0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
   0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
   0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
   0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
   0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
   0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
   0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
   0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
   0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
   0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
   0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,

   0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
   0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
   0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
   0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
   0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
   0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
   0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
   0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
   0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
   0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
   0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
   0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
   0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
   0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
   0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
   0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D };

MplsTunnelLivenessAgent::MplsTunnelLivenessAgent(eos::sdk & sdk) :
      eos::agent_handler(sdk.get_agent_mgr()),
      eos::fd_handler(),
      eos::ip_intf_handler(sdk.get_ip_intf_mgr()),
      eos::timeout_handler(sdk.get_timeout_mgr()),
      ip_intf_mgr_(sdk.get_ip_intf_mgr()),
      eth_intf_mgr_(sdk.get_eth_intf_mgr()),
      t("MplsTunnelLivenessAgent"),
      src_ip(0),
      MAJOR_VERSION("1"),
      MINOR_VERSION("0"),
      PATCH_VERSION("0"),
      VERSION(MAJOR_VERSION + "." + MINOR_VERSION + "." + PATCH_VERSION) {
   // Set sockets to invalid until used.
   sock_send = -1;
   sock_recv = -1;
   read_buf = new char[READ_BUF_SIZE];

   // Assert that size constants correctly add up.
   assert(MPLS_HDR_LEN * BITS_PER_BYTE == MPLS_BOS_LEN_BITS + MPLS_COS_LEN_BITS
          + MPLS_LABEL_LEN_BITS + MPLS_TTL_LEN_BITS);
   assert(VLAN_HDR_LEN * BITS_PER_BYTE ==
          (ETHER_TYPE_LEN * BITS_PER_BYTE) +
          VLAN_DEI_LEN_BITS +
          VLAN_PCP_LEN_BITS +
          VLAN_VID_LEN_BITS);
}

MplsTunnelLivenessAgent::~MplsTunnelLivenessAgent() {
   // Free memory used by read_buf;
   delete read_buf;

   // Free memory used by egress_info.
   for (auto it = egress_info.begin(); it != egress_info.end(); ++it) {
      std::map<uint32_t, tl_egress_t *> *egress_tunnels = it->second;
      auto ite = egress_tunnels->begin();
      for (; ite != egress_tunnels->end(); ++ite) {
         delete ite->second;
      }
      delete egress_tunnels;
   }
   egress_info.clear();

   // Free memory used by ingress_info.
   for (auto it = ingress_info.begin(); it != ingress_info.end(); ++it) {
      std::map<uint32_t, tl_ingress_t *> *ingress_tunnels = it->second;
      auto iti = ingress_tunnels->begin();
      for (; iti != ingress_tunnels->end(); ++iti) {
         delete iti->second;
      }
      delete ingress_tunnels;
   }
   ingress_info.clear();

   // Close any open sockets.
   if (sock_send != -1 && close(sock_send)) {
      t.trace0("ERROR: Failed to close sock_send!");
   }
   if (sock_recv != -1 && close(sock_recv)) {
      t.trace0("ERROR: Failed to close sock_recv!");
   }
}

void MplsTunnelLivenessAgent::print_egress_tunnels(uint32_t remote_ip) {
   std::map<uint32_t, tl_egress_t *> *egress_tunnels =
       get_egress_tunnels(remote_ip);

   t.trace0("TEST: printing all egress tunnels for remote ip: %s",
            format_ip(remote_ip).c_str());
   for (auto ite = egress_tunnels->cbegin(); ite != egress_tunnels->cend(); ++ite) {
      uint32_t tunnel_key = ite->first;
      tl_egress_t *tle = ite->second;
      t.trace0("TEST: tunnel_key:    %d", tunnel_key);
      t.trace0("          pid_local:     %d", tle->pid_local);
      t.trace0("          pid_remote:    %d", tle->pid_remote);
      t.trace0("          msg_id_local:  %d", tle->msg_id_local);
      t.trace0("          msg_id_remote: %d", tle->msg_id_remote);
      t.trace0("          mpls_tag:      %d", tle->mpls_tag);
   }
}

void MplsTunnelLivenessAgent::print_ingress_tunnels(uint32_t remote_ip) {
   std::map<uint32_t, tl_ingress_t *> *ingress_tunnels =
      get_ingress_tunnels(remote_ip);

   t.trace0("TEST: printing all ingress tunnels for remote ip: %s",
            format_ip(remote_ip).c_str());
   auto iti = ingress_tunnels->cbegin();
   for (; iti != ingress_tunnels->cend(); ++iti) {
      uint32_t tunnel_key = iti->first;
      tl_ingress_t *tli = iti->second;
      t.trace0("TEST: tunnel_key: %d", tunnel_key);
      t.trace0("          pid:    %d", tli->pid);
      t.trace0("          msg_id: %d", tli->msg_id);
   }
}

void MplsTunnelLivenessAgent::panic_handler(eos::error const & exception) {
   std::raise(SIGINT);
   exception.raise();
}

void MplsTunnelLivenessAgent::set_src_ip(const std::string src_ip) {
   struct in_addr saddr;
   int ret = inet_pton(AF_INET, src_ip.c_str(), &saddr);
   assert(ret == 1);
   this->src_ip = saddr.s_addr;
}

std::map<uint32_t, tl_egress_t *> *
MplsTunnelLivenessAgent::get_egress_tunnels(uint32_t dst_ip) {
   auto it = egress_info.find(dst_ip);
   if (it != egress_info.end()) {
      return it->second;
   } else {
      std::map<uint32_t, tl_egress_t *> *egress_tunnels =
         new std::map<uint32_t, tl_egress_t *>;
      egress_info[dst_ip] = egress_tunnels;

      return egress_tunnels;
   }
}

std::map<uint32_t, tl_ingress_t *> *
MplsTunnelLivenessAgent::get_ingress_tunnels(uint32_t dst_ip) {
   auto it = ingress_info.find(dst_ip);
   if (it != ingress_info.end()) {
      return it->second;
   } else {
      std::map<uint32_t, tl_ingress_t *> *ingress_tunnels =
         new std::map<uint32_t, tl_ingress_t *>;
      ingress_info[dst_ip] = ingress_tunnels;
      return ingress_tunnels;
   }
}

void MplsTunnelLivenessAgent::update_egress_tunnel(
      std::map<uint32_t, tl_egress_t *> *egress_tunnels,
      tl_entry_t *tle_remote) {
   // Convert the tl_entry_t fields to host-ordering.
   uint32_t pid = ntohl(tle_remote->pid);
   uint32_t msg_id = ntohl(tle_remote->msg_id);
   uint32_t tunnel_key = ntohl(tle_remote->tunnel_key);

   // Ensure that tunnel_key exists in egress_tunnels.
   auto ite = egress_tunnels->find(tunnel_key);
   if (ite == egress_tunnels->end()) {
      // TODO: determine how to handle this.
      t.trace0("ERROR: Egress tunnel does not exist: %d", tunnel_key);
      return;
   }

   tl_egress_t *tle = ite->second;

   // TODO: add the __likely compiler flag to the first if statement?
   if (pid == tle->pid_local) {
      // Update pid_remote in case this is the first acknowlegement received for
      // the current PID.
      tle->pid_remote = pid;

      // Update remote's view of the tunnel if necessary. Do not return from
      // function even if we are receiving an old update. We still should check to
      // see if the remote view has expired.
      if (msg_id > tle->msg_id_remote) {
         tle->msg_id_remote = msg_id;
      }
   } else {
      t.trace7("Received an update with old PID: %d", pid);
      // Updates with the wrong PID means the remote is out of date or we received
      // an out-of-order update.

      // If pid_remote is stale, update it to pid_local, and reset msg_id_remote.
      // Do not reset msg_id_remote for any reason besides this because we may
      // have received an out-of-order message.
      if (tle->pid_remote != tle->pid_local) {
         tle->pid_remote = tle->pid_local;
         tle->msg_id_remote = 0;
      }
   }

   // TODO: figure out how to handle looping/restart behavior.

   // Sanity check for message IDs.
   if (tle->msg_id_local < tle->msg_id_remote) {
      // TODO: make more descriptive error message here.
      t.trace0("WARNING: invalid msg_id - msg_id_local: %d, msg_id_remote: %d",
               tle->msg_id_local, tle->msg_id_remote);
   }
}

void MplsTunnelLivenessAgent::update_ingress_tunnel(
      std::map<uint32_t, tl_ingress_t *> *ingress_tunnels,
      tl_pkt_t *tlp) {
   // Convert the tl_pkt_t fields to host-ordering.
   uint32_t pid = ntohl(tlp->pid);
   uint32_t msg_id = ntohl(tlp->msg_id);
   uint32_t tunnel_key = ntohl(tlp->tunnel_key);

   // Add tunnel_key entry in ingress_tunnels if it does not yet exist.
   auto iti = ingress_tunnels->find(tunnel_key);
   if (iti == ingress_tunnels->end()) {
      tl_ingress_t *tli_new = new tl_ingress_t();
      tli_new->msg_id = 0;
      tli_new->pid = 0;
      ingress_tunnels->insert(std::make_pair(tunnel_key, tli_new));
      iti = ingress_tunnels->find(tunnel_key);
   }

   // Update tunnel information.
   //
   // If we have the same PID view as the remote, only store the new msg_id if it
   // is larger than the current one. This prevents problems with out of ordering
   // reception when both ends view the same PID.
   //
   // If we have a different PID than the remote, take both the new PID and the
   // corresponding message ID. There is not necessarily a guarantee on the order
   // of PIDs, so currently there is no way to determine if an unseen PID is new
   // or old.
   tl_ingress_t *tli = iti->second;
   if (tli->pid == pid) {
      if (msg_id > tli->msg_id) {
         tli->msg_id = msg_id;
      }
   } else {
      tli->pid = pid;
      tli->msg_id = msg_id;
   }
}

bool
MplsTunnelLivenessAgent::add_session(const char *dst_ip, uint32_t tunnel_key,
                                     uint32_t mpls_tag, const char *src_mac,
                                     const char *dst_mac, const char *intf_eos) {
   // TODO: Verify arguments
   struct in_addr d_in_addr;
   if (inet_pton(AF_INET, dst_ip, &d_in_addr) != 1) {
      // TODO: improve error message.
      t.trace0("ERROR: inet_pton failed.");
      return false;
   }
   // TODO: validate intf_eos.

   uint32_t daddr = ntohl(d_in_addr.s_addr);

   // Get egress mappings for daddr.
   std::map<uint32_t, tl_egress_t *> *egress_tunnels = get_egress_tunnels(daddr);

   // Fill tl_egress_t with information and insert it into egress_tunnels.
   tl_egress_t *tle = new tl_egress_t();
   tle->pid_local = new_pid();
   tle->msg_id_local = 0;
   tle->msg_id_remote = 0;
   tle->mpls_tag = mpls_tag;
   tle->vlan_id = ip_intf_mgr_->internal_vlan_id(eos::intf_id_t(intf_eos));
   tle->status = TL_STATUS_DEFAULT;
   bool ret_1 = mac_string_to_bytes(src_mac, (uint8_t *) &tle->src_mac);
   bool ret_2 = mac_string_to_bytes(dst_mac, (uint8_t *) &tle->dst_mac);
   assert(ret_1 && ret_2);

   // Add mapping to egress_tunnels.
   egress_tunnels->insert(std::make_pair(tunnel_key, tle));

   return true;
}

bool
MplsTunnelLivenessAgent::remove_session(const char *dst_ip, uint32_t tunnel_key) {
   struct in_addr d_in_addr;
   if (inet_pton(AF_INET, dst_ip, &d_in_addr) != 1) {
      t.trace0("ERROR: remove_session: dst_ip %s is invalid!", dst_ip);
      return false;
   }
   uint32_t daddr = ntohl(d_in_addr.s_addr);

   auto it = egress_info.find(daddr);
   if (it == egress_info.end()) {
      t.trace0("no tunnels found for dst_ip %s", dst_ip);
      return false;
   }

   // TODO: memory management when deleting a session.

   return it->second->erase(tunnel_key) == 1;
}

void
MplsTunnelLivenessAgent::on_tunnel_status(uint32_t tunnel_key, tl_status_t status) {
   // ADD YOUR CODE HERE.

   t.trace0("----------------------------------------------------------");
   t.trace0("Tunnel %d is now %s", tunnel_key,
            (status == tl_status_t::UP) ? "UP" : "DOWN");
   t.trace0("----------------------------------------------------------");
}

bool
MplsTunnelLivenessAgent::parse_next_msg(uint32_t remote_ip, uint32_t bytes_recvd) {
   t.trace7("Received %d bytes from %s", bytes_recvd, format_ip(remote_ip).c_str());

   if (bytes_recvd < sizeof(tl_pkt_t)) {
      t.trace7("ERROR: read_buf contains less bytes than a tl_pkt_t");
      return false;
   }

   tl_pkt_t *tlp = (tl_pkt_t *) read_buf;
   uint32_t num_entries = ntohl(tlp->num_entries);
   size_t msg_size = sizeof(tl_pkt_t) + num_entries * sizeof(tl_entry_t);
   t.trace7("Received %d entries for message size %zd", num_entries, msg_size);
   if (bytes_recvd < msg_size) {
      t.trace7("ERROR: read_buf contains (%d) bytes; full message = %zd bytes",
               bytes_recvd, msg_size);
      return false;
   } else if (bytes_recvd > msg_size) {
      t.trace7("read_buf contains (%d) bytes; full message = %zd bytes",
               bytes_recvd, msg_size);
      // Do not return false because we can still parse a valid packet.
   }

   // Update information for ingress tunnel.
   std::map<uint32_t, tl_ingress_t *> *ingress_tunnels =
      get_ingress_tunnels(remote_ip);
   update_ingress_tunnel(ingress_tunnels, tlp);

   // Parse data from message.
   std::map<uint32_t, tl_egress_t *> *egress_tunnels = get_egress_tunnels(remote_ip);
   for (uint32_t i = 0; i < num_entries; ++i) {
      tl_entry_t *tle = &tlp->entries[i];
      update_egress_tunnel(egress_tunnels, tle);
   }

   return true;
}

void MplsTunnelLivenessAgent::on_initialized() {
   t.trace7("MplsTunnelLivenessAgent (ver %s) initialized.", VERSION.c_str());

   // Register the panic handler.
   eos::exception_handler_is(panic_handler);

   // Create a socket for the fabric interface.
   //   - PF_PACKET indicates that this will be a "packet socket". This type of
   //     socket bypasses the kernel networking stack. User has to write the
   //     packet from scratch.
   //   - SOCK_RAW tells the library to deliver the entire packet to the
   //     application including the Ethernet header. Note: SOCK_DGRAM tells the
   //     library to automatically strip the layer 2 header. We may want this.
   //   - ETH_P_ALL shows we want to receive every type of protocol. Note: we may
   //     want to make this more specific later.
   sock_send = socket(PF_PACKET, SOCK_RAW, ETH_P_ALL);
   if (sock_send == -1) {
      t.trace0("ERROR: Failed to create sock_send!");
      exit(-1);
   }

   // Set up name and index for the interface.
   //   - IFNAMSIZ = 16; defined by if.h.
   //   - SIOCGIFINDEX: retrieve the interface of the interface.
   struct ifreq ifr;
   strncpy((char *) ifr.ifr_name, "fabric", IFNAMSIZ-1); // Skip trailing '\0'.
   ioctl(sock_send, SIOCGIFINDEX, &ifr);

   // Bind the socket to the fabric interface.
   struct sockaddr_ll sll_send;
   memset(&sll_send, 0, sizeof(struct sockaddr_ll));
   sll_send.sll_family = AF_PACKET;
   sll_send.sll_protocol = htons(ETH_P_ALL);
   sll_send.sll_ifindex = ifr.ifr_ifindex;
   bind(sock_send, (struct sockaddr *) &sll_send, sizeof(struct sockaddr_ll));

   // Create receiving socket.
   sock_recv = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   if (sock_recv == -1) {
      t.trace0("ERROR: Failed to create sock_recv!");
      exit(-1);
   }

   // Bind sock_recv to UDP_PORT.
   struct sockaddr_in sin_recv;
   memset(&sin_recv, 0, sizeof(struct sockaddr_in));
   sin_recv.sin_family = AF_INET;
   sin_recv.sin_port = htons(UDP_PORT);
   sin_recv.sin_addr.s_addr = INADDR_ANY;
   if (bind(sock_recv, (struct sockaddr *) &sin_recv,
            sizeof(struct sockaddr_in)) == -1) {
      t.trace0("ERROR: Failed to bind sock_recv!");
      exit(-1);
   }

   // Watch receiving socket for incoming packets.
   watch_readable(sock_recv, true);

   // Set next timeout time.
   timeout_time_is(eos::now() + TIMEOUT_LENGTH);
}

void MplsTunnelLivenessAgent::on_internal_vlan_id(eos::intf_id_t const & intf_id,
                                                  eos::vlan_id_t vlan_id) {
   t.trace0("on_internal_vlan_id: intf_id %s vlan_id %d",
            intf_id.to_string().c_str(), vlan_id);
   // ADD YOUR CODE HERE.
}

void MplsTunnelLivenessAgent::send_packet(uint32_t dst_ip, uint32_t tunnel_key,
                                          tl_egress_t *tle) {
   // Calculate the number of entries.
   uint32_t num_entries = 0;
   std::map<uint32_t, tl_ingress_t *> *ingress_tunnels = NULL;
   auto it = ingress_info.find(dst_ip);
   if (it != ingress_info.end()) {
      ingress_tunnels = it->second;
      num_entries = ingress_tunnels->size();
   }

   // Useful lengths.
   uint32_t data_len = sizeof(tl_pkt_t) + num_entries * sizeof(tl_entry_t);
   uint32_t packet_len = sizeof(vlan_ethhdr_t) + MPLS_HDR_LEN +
      sizeof(struct iphdr) + sizeof(struct udphdr) + data_len + CRC_32_LEN;
   size_t packet_len_no_crc = packet_len - CRC_32_LEN;

   // Build VLAN (802.1Q) Ethernet header:
   //
   //   8 bytes    6 bytes   6 bytes   4 bytes
   //  ---------- --------- --------- ---------- ------------
   // | preamble | dst_mac | src_mac |  802.1Q  | ether_type | ...
   //  ---------- --------- --------- ---------- ------------
   //                                     ||                       |
   //                                    /  \                      |
   //                                   /    \                     |
   //                                                              v
   //                     16 bits    3 bits   1 bit   12 bits
   //                  ------------ -------- ------- ---------
   //                 |    TPID    |   PCP  |  DEI  |   VID   |
   //                  ------------ -------- ------- ---------
   //
   //   - TPID (tag protocol identifier): 0x8100. Indicates this is an extended
   //     IEEE 802.1Q frame.
   //   - PCP (priority code point): priority level of packet from 0 to 7 (lowest
   //     priority to highest priority).
   //   - DEI (drop eligible identifier): set this to 1 when the packet should be
   //     one of the first to be dropped if there is congestion.
   //   - VID (VLAN identifier): specifies which VLAN the packet belongs to.
   //   - PCP, DEI, and VID combine to form 16 bit TCI (tag control information).
   char buf[MAX_ETHER_LEN];
   vlan_ethhdr_t *vlan = (vlan_ethhdr_t *) buf;
   memcpy(vlan->h_source, tle->src_mac, ETH_ALEN);
   memcpy(vlan->h_dest, tle->dst_mac, ETH_ALEN);
   vlan->h_vlan_proto = htons(ETH_P_8021Q);
   uint32_t pcp = 0;
   uint32_t dei = 0;
   uint32_t vid = tle->vlan_id;
   vlan->h_vlan_TCI = htons(create_vlan_tci(pcp, dei, vid));
   vlan->h_vlan_encapsulated_proto = htons(ETH_P_MPLS_UC);

   // Build MPLS header.
   //   TODO: fill in comment with field descriptions.
   uint32_t *mpls_hdr = (uint32_t *) ptr_to_off(vlan, sizeof(vlan_ethhdr_t));
   uint32_t label = tle->mpls_tag;
   uint32_t cos = MPLS_COS_DEFAULT;
   uint32_t bos = MPLS_BOS_DEFAULT;
   uint32_t ttl = MPLS_TTL_DEFAULT;
   *mpls_hdr = htonl(create_mpls_hdr(label, cos, bos, ttl));

   // Build IP header.
   //   - IP_PROTO_UDP = 17; from linux.in.h.
   //   - TODO: fill in rest of fields (add diagram).
   struct iphdr *ip = (struct iphdr *) ptr_to_off(mpls_hdr, MPLS_HDR_LEN);
   ip->version = 0x04;
   ip->ihl = 0x05;
   ip->tos = 0;
   ip->id = 0;
   ip->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + data_len);
   ip->frag_off = 0;
   ip->ttl = 64;
   ip->saddr = this->src_ip;
   ip->daddr = htonl(dst_ip);
   ip->protocol = IPPROTO_UDP;
   ip->check = 0; // Zero out checksum field before running checksum algorithm.
   ip->check = in_cksum((uint16_t *) ip, sizeof(struct iphdr));

   // Build UDP header.
   // TODO: fill in fields.
   // TODO: add IPv6 checksum handling if IPv6 is a possibility.
   struct udphdr *udp = (struct udphdr *) ptr_to_off(ip, sizeof(struct iphdr));
   udp->source = htons(UDP_PORT);
   udp->dest = htons(UDP_PORT);
   udp->len = htons(sizeof(struct udphdr) + data_len);
   udp->check = 0;

   // Build payload packet.
   tl_pkt_t *tlp = (tl_pkt_t *) ptr_to_off(udp, sizeof(struct udphdr));
   // TODO: figure out how to encode version correctly.
   tlp->version = htonl(1);
   tlp->pid = htonl(tle->pid_local);
   tlp->tunnel_key = htonl(tunnel_key);
   tlp->num_entries = htonl(num_entries);
   // Increment local message ID before sending out liveness packet. Do this as
   // close as possible to where we use its value in the new packet.
   // TODO: does this create a race condition?
   tle->msg_id_local = tle->msg_id_local + 1;
   tlp->msg_id = htonl(tle->msg_id_local);

   // Build payload body.
   tl_entry_t *entries = tlp->entries;
   uint32_t idx = 0;
   if (ingress_tunnels) {
      for (auto iti = ingress_tunnels->begin(); iti != ingress_tunnels->end();
           ++iti) {
         // TODO: should the above iterator be const?
         entries[idx].tunnel_key = htonl(iti->first);
         entries[idx].pid = htonl(iti->second->pid);
         entries[idx].msg_id = htonl(iti->second->msg_id);
         idx++;
      }
   }

   // Calculate the final CRC for the Ethernet packet, including the payload.
   uint8_t * crc_addr = ptr_to_off(vlan, packet_len_no_crc);
   memset(crc_addr, 0, CRC_32_LEN);
   uint32_t crc = crc32((uint8_t *) vlan, packet_len);
   *((uint32_t *) crc_addr) = crc;

   // Send the packet.
   ssize_t bytes_to_write = packet_len;
   int bytes_written = write(sock_send, (uint8_t *) vlan, bytes_to_write);
   if (bytes_written < 0) {
      t.trace0("ERROR: write() failed with error: %s", strerror(errno));
   } else if (bytes_written != bytes_to_write) {
      t.trace0("ERROR: write() expected to write %zd bytes, but wrote %d bytes",
               bytes_to_write, bytes_written);
   } else {
      t.trace9("write() successfully wrote %d bytes", bytes_written);
   }
}

void MplsTunnelLivenessAgent::on_timeout() {
   t.trace7("on_timeout");

   // Iterate through all egress tunnels.
   for (auto it = egress_info.cbegin(); it != egress_info.cend(); ++it) {
      uint32_t dst_ip = it->first;
      std::map<uint32_t, tl_egress_t *> *egress_tunnels = it->second;
      auto ite = egress_tunnels->cbegin();
      for (; ite != egress_tunnels->cend(); ++ite) {
         uint32_t tunnel_key = ite->first;
         tl_egress_t *tle = ite->second;
         send_packet(dst_ip, tunnel_key, tle);

         // Check current egress tunnel to see if the remote view has gone stale.
         //
         // If pid_remote is not up to date, count this as a new tunnel, i.e.,
         // count msg_id_remote as zero. Do not touch the state of tle: leave this
         // to update_tunnel_* and send_packet.
         uint32_t msg_id_diff = (tle->pid_remote == tle->pid_local)
            ? tle->msg_id_local - tle->msg_id_remote
            : tle->msg_id_local;
         if (tle->status == tl_status_t::UP && msg_id_diff > MSG_ID_THRESH) {
            tle->status = tl_status_t::DOWN;
            on_tunnel_status(tunnel_key, tl_status_t::DOWN);
         } else if (tle->status == tl_status_t::DOWN &&
                    msg_id_diff <= MSG_ID_THRESH) {
            tle->status = tl_status_t::UP;
            on_tunnel_status(tunnel_key, tl_status_t::UP);
         }
      }
   }

   // Set next update timeout.
   timeout_time_is(eos::now() + TIMEOUT_LENGTH);
}

void MplsTunnelLivenessAgent::on_readable(int fd) {
   if (fd != sock_recv) {
      t.trace0("ERROR: on_readable: unknown socket became readable %d", fd);
      // TODO: in this case, don't we need to empty the buffer?
      // assert false;
      exit(-1);
   }

   // TODO: Can we embed a way to avoid UDP port overlap? I.e., if another
   //       protocol uses UDP_PORT, can we filter this out?

   t.trace7("on_readable: fd %d", fd);

   // For now, we assume a 1:1 mapping of inbound packets to on_readable calls.
   struct sockaddr_storage src_addr;
   socklen_t sock_len = sizeof(struct sockaddr_storage);
   int bytes_recvd = recvfrom(sock_recv, read_buf, READ_BUF_SIZE, 0,
                              (struct sockaddr *) &src_addr, &sock_len);

   if (bytes_recvd == -1) {
      t.trace0("ERROR: Recv unexpectedly failed");
      return;
   } else if (bytes_recvd == 0) {
      t.trace0("No bytes read!");
      // TODO: do I have to do anything with closed connecitons?
      // I don't think so. This socket does not use connect.
      return;
   }

   // Parse IP address of the datagram we received.
   struct sockaddr_in *sin = (struct sockaddr_in *) &src_addr;
   uint32_t remote_ip = ntohl(sin->sin_addr.s_addr);

   // Parse next message from remote_ip.
   if (!parse_next_msg(remote_ip, bytes_recvd)) {
      t.trace7("Error while parsing message...");
   }
}

inline uint32_t MplsTunnelLivenessAgent::new_pid() {
   return time(NULL);
}

inline uint8_t *MplsTunnelLivenessAgent::ptr_to_off(void * buf, uint32_t off) {
   return ((uint8_t *) buf) + off;
}

inline bool MplsTunnelLivenessAgent::mac_string_to_bytes(const char *mac_string,
                                                         uint8_t *mac_bytes) {
   // This char allows us to check if there any any excess characters after parsing
   // the MAC address. Any excess characters mean that the MAC address is malformed.
   char overflow = 0;

   // Use sscanf to parse mac_string directly into mac_bytes.
   // '%2hhx' tells sscanf to parse up to 2 digits into an 'unsigned char *' with the
   // characters interpreted as hexidecimal digits.
   return sscanf(mac_string, "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx%c",
                 &mac_bytes[0], &mac_bytes[1], &mac_bytes[2],
                 &mac_bytes[3], &mac_bytes[4], &mac_bytes[5],
                 &overflow) == ETH_ALEN;
}

inline uint16_t MplsTunnelLivenessAgent::in_cksum(uint16_t *addr, int len) {
   int sum = 0;
   u_short answer = 0;
   u_short *w = addr;
   int nleft = len;
   /*
    * Our algorithm is simple, using a 32 bit accumulator (sum), we add
    * sequential 16 bit words to it, and at the end, fold back all the
    * carry bits from the top 16 bits into the lower 16 bits.
    */
   while (nleft > 1) {
      sum += *w++;
      nleft -= 2;
   }
   /* mop up an odd byte, if necessary */
   if (nleft == 1) {
      *(u_char *) (&answer) = *(u_char *) w;
      sum += answer;
   }
   /* add back carry outs from top 16 bits to low 16 bits */
   sum = (sum >> 16) + (sum & 0xffff);     /* add hi 16 to low 16 */
   sum += (sum >> 16);             /* add carry */
   answer = ~sum;              /* trunca1te to 16 bits */

   return (answer);
}

inline uint32_t update_crc32(uint32_t crc, uint8_t next_byte) {
   uint32_t long_next_byte = 0x000000FFL & (uint32_t) next_byte;
   crc = (crc >> 8) ^ crc_table[(crc ^ long_next_byte) & 0xFF];

   return crc;
}

inline uint32_t MplsTunnelLivenessAgent::crc32(uint8_t *msg, uint32_t len) {
   uint32_t crc = 0xFFFFFFFFL;
   while (len--) {
      uint8_t next_byte = *msg;
      crc = update_crc32(crc, next_byte);
      msg++;
   }

   return crc ^ 0xFFFFFFFFL;
}

inline uint16_t MplsTunnelLivenessAgent::create_vlan_tci(uint16_t pcp, uint16_t dei,
                                                         uint16_t vid) {
   // Combine all parameters into a single 16 bit variable.
   uint16_t vlan_tci = pcp;
   vlan_tci = (vlan_tci << VLAN_DEI_LEN_BITS) | dei;
   vlan_tci = (vlan_tci << VLAN_VID_LEN_BITS) | vid;

   return vlan_tci;
}

inline uint32_t
MplsTunnelLivenessAgent::create_mpls_hdr(uint32_t label, uint32_t cos, uint32_t bos,
                                         uint32_t ttl) {
   // Combine all of the fields into a single 32 bit variable.
   uint32_t mpls_hdr = label;
   mpls_hdr = (mpls_hdr << MPLS_COS_LEN_BITS) | cos;
   mpls_hdr = (mpls_hdr << MPLS_BOS_LEN_BITS) | bos;
   mpls_hdr = (mpls_hdr << MPLS_TTL_LEN_BITS) | ttl;

   return mpls_hdr;
}

inline std::string MplsTunnelLivenessAgent::format_ip(uint32_t ip) {
   eos::ip_addr_t ip_addr(htonl(ip));
   return ip_addr.to_string();
}
