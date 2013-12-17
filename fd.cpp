// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#include "eos/fd.h"

namespace eos {

fd_handler::fd_handler() {
}

fd_handler::~fd_handler() {
}

void
fd_handler::on_readable(int fd) {
   // TODO: No op impl.
}

void
fd_handler::on_writable(int fd) {
   // TODO: No op impl.
}

void
fd_handler::on_exception(int fd) {
   // TODO: No op impl.
}

void
fd_handler::watch_readable(int fd, bool) {
   // TODO: No op impl.
}

void
fd_handler::watch_writable(int fd, bool) {
   // TODO: No op impl.
}

void
fd_handler::watch_exception(int fd, bool) {
   // TODO: No op impl.
}

}
