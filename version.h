// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_VERSION_H
#define EOSSDK_VERSION_H

#include <eos/base.h>

namespace eos {

// Version string, at least of the form "X.Y.Z", but possibly followed by a
// dash and more characters (e.g. "X.Y.Z-rc1").
extern const char * const version EOS_SDK_PUBLIC;

}

#endif // EOSSDK_VERSION_H
