// Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOSSDK_VERSION_H
#define EOSSDK_VERSION_H

#include <eos/base.h>

namespace eos {

// Version string, at least of the form "X.Y.Z", but possibly followed by a
// dash and more characters (e.g. "X.Y.Z-rc1").
extern const char * const version EOS_SDK_PUBLIC;

// Major version number (i.e. the "X" in "X.Y.Z")
extern const uint8_t version_major EOS_SDK_PUBLIC;

// Minor version number (i.e. the "Y" in "X.Y.Z")
extern const uint8_t version_minor EOS_SDK_PUBLIC;

// Patch version number (i.e. the "Z" in "X.Y.Z", regardless of any trailing
// characters followed by the dash optional)
extern const uint8_t version_patch EOS_SDK_PUBLIC;

// Arista project name used to build the EOS SDK.
extern const char * const build_project EOS_SDK_PUBLIC;

// User that built the EOS SDK.
extern const char * const build_user EOS_SDK_PUBLIC;

// Path under which the EOS SDK was built.
extern const char * const build_path EOS_SDK_PUBLIC;

// Source control system revision number at which the EOS SDK was built.
extern const uint32_t build_cl EOS_SDK_PUBLIC;

// UNIX timestamp at which the EOS SDK was built.
extern const uint64_t build_timestamp EOS_SDK_PUBLIC;

}

#endif // EOSSDK_VERSION_H
