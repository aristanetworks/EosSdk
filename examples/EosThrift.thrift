#!/usr/bin/thrift --gen cpp
# Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
# Arista Networks, Inc. Confidential and Proprietary.

namespace cpp eos

enum OperStatus {
  UNKNOWN,
  UP,
  DOWN,
}

/// The interface's type
enum InterfaceType {
   UNKNOWN,
   OTHER,
   ETH,
   VLAN,
   MANAGEMENT,
   LOOPBACK,
   LAG,
   NULL0,
}

// XXX exceptions.

service ThriftSdk {
  // intf_mgr
  bool exists(1:string intf),
  bool adminEnabled(1:string intf),
  void adminEnabledIs(1:string intf, 2:bool enabled),
  void descriptionIs(1:string intf, 2:string description),
  OperStatus operStatus(1:string intf),
}
