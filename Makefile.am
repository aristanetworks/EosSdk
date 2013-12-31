lib_LTLIBRARIES = libeos.la

AM_CXXFLAGS = -fvisibility=hidden -std=gnu++0x
AM_CXXFLAGS += -Wextra -Wall -Werror -Wno-unused-parameter
AM_LDFLAGS = -Wl,--no-undefined

PUBLISHED_HEADER_FILES = $(wildcard eos/*.h) $(wildcard eos/inline/*.h)
eosheaderdir = $(includedir)/eos
eosheader_HEADERS = $(PUBLISHED_HEADER_FILES)

libeos_la_SOURCES =
libeos_la_SOURCES += agent.cpp
libeos_la_SOURCES += decap_group.cpp
libeos_la_SOURCES += eth.cpp
libeos_la_SOURCES += eth_intf.cpp
libeos_la_SOURCES += event_loop.cpp
libeos_la_SOURCES += eth_phy_intf.cpp
libeos_la_SOURCES += fd.cpp
libeos_la_SOURCES += intf.cpp
libeos_la_SOURCES += impl.cpp
libeos_la_SOURCES += ip.cpp
libeos_la_SOURCES += ip_route.cpp
libeos_la_SOURCES += mpls_route.cpp
libeos_la_SOURCES += panic.cpp
libeos_la_SOURCES += timer.cpp
libeos_la_SOURCES += version.cpp

libeos_la_LDFLAGS = -version-info $(SDK_LIBTOOL_VERSION) -lrt

ACLOCAL_AMFLAGS = -I autogen
EXTRA_DIST = bootstrap build.sh
