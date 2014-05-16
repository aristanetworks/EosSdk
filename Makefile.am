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
libeos_la_SOURCES += class_map.cpp
libeos_la_SOURCES += decap_group.cpp
libeos_la_SOURCES += directflow.cpp
libeos_la_SOURCES += eth.cpp
libeos_la_SOURCES += eth_intf.cpp
libeos_la_SOURCES += eth_phy_intf.cpp
libeos_la_SOURCES += event_loop.cpp
libeos_la_SOURCES += exception.cpp
libeos_la_SOURCES += fd.cpp
libeos_la_SOURCES += intf.cpp
libeos_la_SOURCES += impl.cpp impl.h
libeos_la_SOURCES += ip.cpp
libeos_la_SOURCES += ip_route.cpp
libeos_la_SOURCES += fib.cpp
libeos_la_SOURCES += iterator.cpp
libeos_la_SOURCES += mac_table.cpp
libeos_la_SOURCES += mlag.cpp
libeos_la_SOURCES += mpls_route.cpp
libeos_la_SOURCES += nexthop_group.cpp
libeos_la_SOURCES += panic.cpp
libeos_la_SOURCES += neighbor_table.cpp
libeos_la_SOURCES += policy_map.cpp
libeos_la_SOURCES += timer.cpp
libeos_la_SOURCES += sdk.cpp
libeos_la_SOURCES += system.cpp
libeos_la_SOURCES += version.cpp

libeos_la_LDFLAGS = -version-info $(SDK_LIBTOOL_VERSION) -lrt


# --------- #
# SWIG libs #
# --------- #

if USE_PYTHON
SWIG_FILES := EosSdk.i SwigUtils.i SwigRenamer.py swig.patch
python_PYTHON = $(srcdir)/eossdk.py
pyexec_LTLIBRARIES = _eossdk.la
_eossdk_la_SOURCES = $(srcdir)/eossdk_wrap.cpp $(srcdir)/eossdk_wrap.h
_eossdk_la_LDFLAGS = -avoid-version -module
# Swig generated code produces some warnings, depending on the combination of
# Python version and GCC version, so we turn the problematic ones off here as
# we build with -Werror:
_eossdk_la_CXXFLAGS = $(AM_CXXFLAGS) -Wno-strict-aliasing -Wno-missing-field-initializers
_eossdk_la_CPPFLAGS = -I/usr/include/python$(PYTHON_VERSION)
_eossdk_la_LIBADD = libeos.la

$(srcdir)/eossdk_wrap.cpp: $(SWIG_FILES) $(nobase_include_HEADERS)
	SRCDIR=$(srcdir) $(SWIG) -threads -c++ -python -I$(srcdir) -o $@-t $(srcdir)/EosSdk.i
	patch --batch --no-backup-if-mismatch -p0 <$(srcdir)/swig.patch
	mv $@-t $@

$(srcdir)/eossdk_wrap.h: $(srcdir)/eossdk_wrap.cpp

$(srcdir)/eossdk.py: $(srcdir)/eossdk_wrap.cpp

BUILT_SOURCES = $(_eossdk_la_SOURCES)
MAINTAINERCLEANFILES = $(BUILT_SOURCES)
endif

ACLOCAL_AMFLAGS = -I autogen
EXTRA_DIST = bootstrap build.sh $(SWIG_FILES)

dist-hook:
	chmod -R u+w $(distdir)
