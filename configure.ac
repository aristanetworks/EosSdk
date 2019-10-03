m4_include([version.m4])
AC_INIT(_NAME_-stubs, _VERSION_, [], _NAME_-stubs)
AC_CONFIG_AUX_DIR([autogen])
AC_CONFIG_MACRO_DIR([autogen])
AC_PREREQ([2.59])

AM_INIT_AUTOMAKE([foreign 1.9 tar-pax])
AC_CONFIG_HEADERS([config.h])
LT_INIT([disable-static])
AC_PROG_CXX

# Some old versions of the STL only contain partial support for C++11, and
# this can lead to puzzling compilation errors.  Try to detect those here
# and report a more helpful error message.
AC_CACHE_CHECK([for std::unordered_set::operator==], [eossdk_cv_unordered_set_eq],
[AC_LANG_PUSH([C++])dnl
# Detect STL versions that are missing std::unordered_set::operator== (e.g.
# libstdc++-4.4.7 on CentOS 6.6)
save_CXXFLAGS=$CXXFLAGS
CXXFLAGS="$CXXFLAGS -std=gnu++14"
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
    #include <unordered_set>
    std::unordered_set<int> s;
    bool b = s == s;
]])], [eossdk_cv_unordered_set_eq=yes], [eossdk_cv_unordered_set_eq=no])
CXXFLAGS=$save_CXXFLAGS
AC_LANG_POP([C++])dnl
])
if test "x$eossdk_cv_unordered_set_eq" != xyes; then
   AC_MSG_ERROR([Your version of the STL seems to be missing std::unordered_set::operator==,dnl
 check config.log for more details])
fi

AC_MSG_CHECKING(SHIPPING)
AM_CONDITIONAL(SHIPPING, test "${SHIPPING:-0}" != 0)
AM_COND_IF(SHIPPING,AC_MSG_RESULT(yes),AC_MSG_RESULT(no))

AC_ARG_ENABLE([python],
              [AS_HELP_STRING([--enable-python],
                              [compile Python bindings])],
              [], [enable_python=no])
AM_CONDITIONAL([USE_PYTHON], [test "x$enable_python" = xyes])
if test "x$enable_python" != xyes; then
   AC_MSG_NOTICE([You may configure with --enable-python ]dnl
[if you need Python bindings.])
else
   AM_PATH_PYTHON([2.6])

   AC_CHECK_PROG([SWIG], [swig], [swig])
   test -z $SWIG && AC_MSG_ERROR([you don't have swig installed]);
   swig_version=$($SWIG -version |grep "SWIG Version ")
   test "$swig_version" \< "SWIG Version 3" && AC_MSG_ERROR([your swig version needs to be at least 3.0]);
fi

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
AC_DEFINE([SDK_VERSION_PATCH], [VERSION_PATCH],
          [Patch version number of the EOS SDK])
AC_SUBST([SDK_LIBTOOL_VERSION],
         [m4_eval(VERSION_MAJOR + VERSION_MINOR):VERSION_PATCH:VERSION_MINOR])dnl
AC_SUBST([SDK_VERSION_MAJOR], [VERSION_MAJOR])
AC_SUBST([SDK_VERSION_MINOR], [VERSION_MINOR])

AC_DEFINE_UNQUOTED([SDK_BUILD_TIMESTAMP], [`date +%s`UL],
                   [UNIX timestamp at which the EOS SDK was built])
AC_DEFINE_UNQUOTED([SDK_BUILD_PROJECT], ["${WP-unknown}"],
                   [Arista project from which the EOS SDK was built])
AC_DEFINE_UNQUOTED([SDK_BUILD_PROJECT_CL],
                   [$(sp=$(cat /eng/project/$WP/syncpoint 2>/dev/null);\
                    test "$sp" == "" && echo "0UL" || echo "${sp}UL")],
                   [Change list number from which the EOS SDK was built])
AC_DEFINE_UNQUOTED([SDK_BUILD_USER], ["${USER-unknown}"],
                   [User that built the EOS SDK])
AC_DEFINE_UNQUOTED([SDK_BUILD_PATH], ["`pwd -P`"],
                   [Path from which the EOS SDK was built])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
