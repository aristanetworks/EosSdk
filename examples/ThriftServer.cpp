// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include <thrift/server/TNonblockingServer.h>

#include <eos/intf.h>
#include <eos/sdk.h>

#include "ThriftSdk.h"
#include "libevent.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace eos;

class ThriftSdkHandler : virtual public ThriftSdkIf {
 public:
  explicit ThriftSdkHandler(eos::intf_mgr * mgr) : intf_mgr(mgr) {
  }

  bool exists(const std::string& intf) {
    return intf_mgr->exists(intf_id_t(intf));
  }

  bool adminEnabled(const std::string& intf) {
    return intf_mgr->admin_enabled(intf_id_t(intf));
  }

  void adminEnabledIs(const std::string& intf, const bool enabled) {
    intf_mgr->admin_enabled_is(intf_id_t(intf), enabled);
  }

  void descriptionIs(const std::string& intf, const std::string& description) {
    intf_mgr->description_is(intf_id_t(intf), description.c_str());
  }

  OperStatus::type operStatus(const std::string& intf) {
    switch (intf_mgr->oper_status(intf_id_t(intf))) {
      case INTF_OPER_UP: return OperStatus::UP;
      case INTF_OPER_DOWN: return OperStatus::DOWN;
      case INTF_OPER_NULL:  // Fall through.
      default:
        return OperStatus::UNKNOWN;
    }
  }

 private:
  eos::intf_mgr * intf_mgr;
};

/// RAII holder for a libevent event_base.
class event_base_holder {
 public:
  event_base_holder() : base_(event_base_new()) {
  }

  ~event_base_holder() {
    event_base_free(base_);
  }

  event_base * ptr() const {
    return base_;
  }

 private:
  event_base * const base_;
};

int main(int argc, char **argv) {
  int port = 9090;
  sdk sdk;
  shared_ptr<ThriftSdkHandler> handler(new ThriftSdkHandler(sdk.get_intf_mgr()));
  event_base_holder base;
  libevent_loop loop(sdk, base.ptr());
  shared_ptr<TProcessor> processor(new ThriftSdkProcessor(handler));

  TNonblockingServer server(processor, port);
  loop.init();
  server.registerEvents(base.ptr());
  event_base_dispatch(base.ptr());
  return 0;
}

