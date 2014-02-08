m4_include([version.m4])
AC_INIT(_NAME_-stubs, _VERSION_, [], _NAME_-stubs)
AC_CONFIG_AUX_DIR([autogen])
AC_CONFIG_MACRO_DIR([autogen])
AC_PREREQ([2.59])

AM_INIT_AUTOMAKE([foreign 1.9 tar-pax])
AC_CONFIG_HEADERS([config.h])
LT_INIT([disable-static])
AC_PROG_CXX
AM_PATH_PYTHON([2.6])

# Debian has a binary for SWIG 2.0 named swig2.0 and they kept swig as
# an alias for swig-1.3.  Let's use the former when available.
AC_CHECK_PROGS([SWIG], [swig2.0 swig], [swig])

m4_define([VERSION_MAJOR],
          [m4_bregexp(_VERSION_, [^\([0-9]+\)], [\1])])dnl
AC_DEFINE([SDK_VERSION_MAJOR], [VERSION_MAJOR],
          [Major version number of the EOS SDK])
m4_define([VERSION_MINOR],
          [m4_bregexp(_VERSION_, [^[0-9]+[-._]\([0-9]+\)], [\1])])dnl
AC_DEFINE([SDK_VERSION_MINOR], [VERSION_MINOR],
          [Minor version number of the EOS SDK])
m4_define([VERSION_PATCH],
          [m4_bregexp(_VERSION_, [^[0-9]+[-._][0-9]+[-._]\([0-9]+\)], [\1])])dnl
AC_DEFINE([[SDK_VERSION_PATCH]], [VERSION_PATCH],
          [Patch version number of the EOS SDK])
AC_SUBST([SDK_LIBTOOL_VERSION],
         [m4_eval(VERSION_MAJOR + VERSION_MINOR):VERSION_PATCH:VERSION_MINOR])dnl

AC_DEFINE_UNQUOTED([SDK_BUILD_TIMESTAMP], [`date +%s`UL],
                   [UNIX timestamp at which the EOS SDK was built])
AC_DEFINE_UNQUOTED([SDK_BUILD_PROJECT], ["${WP-unknown}"],
                   [Arista project from which the EOS SDK was built])
AC_DEFINE_UNQUOTED([SDK_BUILD_PROJECT_CL],
                   [`cat /eng/project/$WP/syncpoint 2>/dev/null || echo 0`UL],
                   [Change list number from which the EOS SDK was built])
AC_DEFINE_UNQUOTED([SDK_BUILD_USER], ["${USER-unknown}"],
                   [User that built the EOS SDK])
AC_DEFINE_UNQUOTED([SDK_BUILD_PATH], ["`pwd -P`"],
                   [Path from which the EOS SDK was built])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
