// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/fd.h"
#include "impl.h"

namespace eos {

fd_handler::fd_handler() {
   impl.register_fd_handler(this);
}

fd_handler::~fd_handler() {
   impl.unregister_fd_handler(this);
}

void
fd_handler::on_readable(int fd) {
   // Default implementation: do nothing.
}

void
fd_handler::on_writable(int fd) {
   // Default implementation: do nothing.
}

void
fd_handler::on_exception(int fd) {
   // Default implementation: do nothing.
}

void
fd_handler::watch_readable(int fd, bool interest) {
   impl.get_fd_sm(this)->watch_readable(fd, interest);
}

void
fd_handler::watch_writable(int fd, bool interest) {
   impl.get_fd_sm(this)->watch_writable(fd, interest);
}

void
fd_handler::watch_exception(int fd, bool interest) {
   impl.get_fd_sm(this)->watch_exception(fd, interest);
}

}
