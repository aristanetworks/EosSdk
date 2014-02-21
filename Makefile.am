lib_LTLIBRARIES = libeos.la

AM_CXXFLAGS = -fvisibility=hidden -std=gnu++0x
AM_CXXFLAGS += -Wextra -Wall -Wnon-virtual-dtor -Werror -Wno-unused-parameter
AM_LDFLAGS = -Wl,--no-undefined

PUBLISHED_HEADER_FILES := $(wildcard eos/*.h) $(wildcard eos/inline/*.h)
nobase_include_HEADERS = $(PUBLISHED_HEADER_FILES)

libeos_la_SOURCES =
libeos_la_SOURCES += agent.cpp
libeos_la_SOURCES += acl.cpp
libeos_la_SOURCES += aresolve.cpp
libeos_la_SOURCES += decap_group.cpp
libeos_la_SOURCES += directflow.cpp
libeos_la_SOURCES += eth.cpp
libeos_la_SOURCES += eth_intf.cpp
libeos_la_SOURCES += event_loop.cpp
libeos_la_SOURCES += eth_phy_intf.cpp
libeos_la_SOURCES += fd.cpp
libeos_la_SOURCES += intf.cpp
libeos_la_SOURCES += impl.cpp impl.h
libeos_la_SOURCES += ip.cpp
libeos_la_SOURCES += ip_route.cpp
libeos_la_SOURCES += iterator.cpp
libeos_la_SOURCES += mpls_route.cpp
libeos_la_SOURCES += panic.cpp
libeos_la_SOURCES += timer.cpp
libeos_la_SOURCES += version.cpp

libeos_la_LDFLAGS = -version-info $(SDK_LIBTOOL_VERSION) -lrt


# # --------- #
# # SWIG libs #
# # --------- #
# 
# SWIG_FILES := EosSdk.i SwigUtils.i SwigRenamer.py
# python_PYTHON = EosSdk.py
# pyexec_LTLIBRARIES = _EosSdk.la
# _EosSdk_la_SOURCES = $(srcdir)/EosSdk_wrap.cpp $(srcdir)/EosSdk_wrap.h
# _EosSdk_la_LDFLAGS = -avoid-version -module
# # Swig generated code produces some warnings, depending on the combination of
# # Python version and GCC version, so we turn the problematic ones off here as
# # we build with -Werror:
# _EosSdk_la_CXXFLAGS = $(AM_CXXFLAGS) -Wno-strict-aliasing -Wno-missing-field-initializers
# _EosSdk_la_CPPFLAGS = -I/usr/include/python$(PYTHON_VERSION)
# _EosSdk_la_LIBADD = libeos.la
# 
# $(srcdir)/EosSdk_wrap.cpp: $(SWIG_FILES)
# 	SRCDIR=$(srcdir) $(SWIG) -c++ -python -I$(srcdir) -o $@ $(srcdir)/EosSdk.i
# 
# $(srcdir)/EosSdk.py: $(SWIG_FILES)
# 	$(MAKE) $(AM_MAKEFLAGS) EosSdk_wrap.cpp
# 
# MAINTAINERCLEANFILES = $(_EosSdk_la_SOURCES)

ACLOCAL_AMFLAGS = -I autogen
# EXTRA_DIST = bootstrap build.sh $(SWIG_FILES)
EXTRA_DIST = bootstrap build.sh

dist-hook:
	chmod -R u+w $(distdir)
