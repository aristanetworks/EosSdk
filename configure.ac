m4_include([version.m4])
AC_INIT(_NAME_, _VERSION_, [], _NAME_)
AC_CONFIG_AUX_DIR([autogen])
AC_PREREQ(2.59)

AM_INIT_AUTOMAKE([foreign 1.9 tar-pax])

dnl If this package doesn't use C or C++, remove the next three lines
AC_CONFIG_HEADERS([config.h])
LT_INIT([disable-static])
AC_PROG_CXX

AM_PATH_PYTHON

rm -rf src-includes generated-includes
mkdir src-includes generated-includes
ln -s $(cd ${srcdir}; /bin/pwd) src-includes/EosSdk
ln -s .. generated-includes/EosSdk

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
