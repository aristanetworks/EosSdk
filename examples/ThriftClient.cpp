// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <string>
#include <iostream>
#include <boost/program_options.hpp>

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "ThriftSdk.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
namespace po = boost::program_options;

using namespace eos;

int main(int argc, char **argv) {
  po::options_description desc("Program options");
  int port;
  std::string server;
  std::string intf;
  desc.add_options()
    ("help,h", "Prints this help message")
    ("server", po::value(&server)->default_value("localhost"),
     "IP or hostname of the server")
    ("port", po::value(&port)->default_value(9090), "Port of the server")
    // Operations:
    ("interface", po::value(&intf)->required(),
     "Interface on which to carry the operation")
    ("exists", "Checks whether the given interface exists")
    ("set-description", po::value<std::string>(),
     "Sets the interface description")
  ;
  po::variables_map flags;
  po::store(po::parse_command_line(argc, argv, desc), flags);
  if(flags.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }
  po::notify(flags);

  boost::shared_ptr<TSocket> socket(new TSocket(server, port));
  boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  ThriftSdkClient client(protocol);
  transport->open();
  if(flags.count("exists")) {
     bool res = client.exists(intf);
     std::cout << "exists(" << intf << "): " << res << std::endl;
  }
  if(flags.count("set-description")) {
     std::string description = flags["set-description"].as<std::string>();
     client.descriptionIs(intf, description);
  }
  transport->close();

  return 0;
}
