# 1 "eos/version.h.template"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4

# 17 "/usr/include/stdc-predef.h" 3 4























# 32 "<command-line>" 2
# 1 "eos/version.h.template"

# 1 "./config.h" 1





















































































# 2 "eos/version.h.template" 2
// This is the template from which version.h is generated through preprocessing.
// Through preprocessing things like 2 get resolved.
// We do want to keep the #if and other defines, so we prefix each line with "_-_ ",
// which also helps later removing extra gunk the pre-processor adds.
// Note that because include of base.h was neutered by the _-_, EOS_SDK_PUBLIC will
// not be substituted, which is crucial since it evaluates differently under SWIG.
// The "_-_ " is removed post pre-processing, as well as neutered "pounddefined"
// is later replaced with the final "#define".
// The only other "trick" is that comments had to be changed from // to @@, which
// is also "corrected" back during post-processing in the makefile.
//
_-_ @@@@
_-_  * @file
_-_  * The version module. It provides EosSdk version information.
_-_  *
_-_  * This module provides access to EosSdk version information, including
_-_  * version major number, version minor number and version patch number.
_-_  *
_-_  * To access the version information, application will need to include
_-_  * "eos/version.h", then it can access it directly, as following:
_-_  *   eos::version_major
_-_  *   eos::version_minor
_-_  *   eos::version_patch
_-_  *   eos::version
_-_  *
_-_  *   Note: eos::version is of type "char *" while version_major, version_minor
_-_  *   and version_patch are of type "uint8_t".
_-_  @@@
_-_
_-_ @@ Copyright (c) 2013 Arista Networks, Inc.  All rights reserved.
_-_ @@ Arista Networks, Inc. Confidential and Proprietary.
_-_
_-_ #ifndef EOSSDK_VERSION_H
_-_ #define EOSSDK_VERSION_H
_-_
_-_ #include <eos/base.h>
_-_
_-_ pounddefine EOSSDK_VERSION "2.18.0"
_-_ pounddefine EOSSDK_MAJOR 2
_-_ pounddefine EOSSDK_MINOR 18
_-_ pounddefine EOSSDK_PATCH 0
_-_
_-_ namespace eos {
_-_
_-_ @@ Version string, at least of the form "X.Y.Z", but possibly followed by a
_-_ @@ dash and more characters (e.g. "X.Y.Z-rc1").
_-_ extern const char * const version EOS_SDK_PUBLIC;
_-_
_-_ @@ Major version number (i.e. the "X" in "X.Y.Z")
_-_ extern const uint8_t version_major EOS_SDK_PUBLIC;
_-_
_-_ @@ Minor version number (i.e. the "Y" in "X.Y.Z")
_-_ extern const uint8_t version_minor EOS_SDK_PUBLIC;
_-_
_-_ @@ Patch version number (i.e. the "Z" in "X.Y.Z", regardless of any trailing
_-_ @@ characters followed by the dash optional)
_-_ extern const uint8_t version_patch EOS_SDK_PUBLIC;
_-_
_-_ @@ Arista project name used to build the EOS SDK.
_-_ extern const char * const build_project EOS_SDK_PUBLIC;
_-_
_-_ @@ User that built the EOS SDK.
_-_ extern const char * const build_user EOS_SDK_PUBLIC;
_-_
_-_ @@ Path under which the EOS SDK was built.
_-_ extern const char * const build_path EOS_SDK_PUBLIC;
_-_
_-_ @@ Source control system revision number at which the EOS SDK was built.
_-_ extern const uint32_t build_cl EOS_SDK_PUBLIC;
_-_
_-_ @@ UNIX timestamp at which the EOS SDK was built.
_-_ extern const uint64_t build_timestamp EOS_SDK_PUBLIC;
_-_
_-_ }
_-_
_-_ #endif @@ EOSSDK_VERSION_H
