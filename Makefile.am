lib_LTLIBRARIES = libeos.la

AM_CXXFLAGS = -fvisibility=hidden
AM_CXXFLAGS += $(EXTRA_CFLAGS)
AM_CXXFLAGS += -Wextra -Wall -Wnon-virtual-dtor -Werror -Wno-unused-parameter -Wno-error=unused-value -fPIC -fPIE -fvisibility-inlines-hidden
AM_CXXFLAGS += -DTRAFFIC_POLICY_ENABLED
AM_LDFLAGS = -Wl,--no-undefined -fPIC -fPIE

PUBLISHED_HEADER_FILES := $(wildcard eos/*.h) $(wildcard eos/inline/*.h) $(wildcard eos/types/*.h) $(wildcard eos/inline/types/*.h)
nobase_include_HEADERS = $(PUBLISHED_HEADER_FILES)

EXTRA_DIST = MaybePrintProfilesAndExit.cpp $(wildcard examples/*) $(wildcard examples/test/*)
EXTRA_DIST += GetAgentProcessName.cpp
EXTRA_DIST += eos/version.h.template

if SHIPPING
SHIPPING_FLAG=-DSHIPPING
else
SHIPPING_FLAG=
endif

version.cpp: eos/version.h
eos/version.h: eos/version.h.template
	cpp -traditional -I. -I/src/EosSdk $< $@.pp
	cat $@.pp | sed 's#@@@@#/**#' | sed 's#@@@#*/#' | sed 's#@@#//#' | grep "^_-_" | sed 's/^_-_ //' | sed 's/^_-_//' | sed 's/pounddefine/#define/' > $@

libeos_la_SOURCES =
libeos_la_SOURCES += agent.cpp
libeos_la_SOURCES += acl.cpp
libeos_la_SOURCES += aresolve.cpp
libeos_la_SOURCES += aresolve_types.cpp
libeos_la_SOURCES += class_map.cpp
libeos_la_SOURCES += decap_group.cpp
libeos_la_SOURCES += directflow.cpp
libeos_la_SOURCES += directflow_types.cpp
libeos_la_SOURCES += eapi.cpp
libeos_la_SOURCES += eth_types.cpp
libeos_la_SOURCES += eth_intf.cpp
libeos_la_SOURCES += eth_lag_intf.cpp
libeos_la_SOURCES += eth_phy_intf.cpp
libeos_la_SOURCES += event_loop.cpp
libeos_la_SOURCES += exception.cpp
libeos_la_SOURCES += fd.cpp
libeos_la_SOURCES += hardware_table.cpp
libeos_la_SOURCES += intf.cpp
libeos_la_SOURCES += intf_types.cpp
libeos_la_SOURCES += impl.cpp impl.h
libeos_la_SOURCES += ip.cpp
libeos_la_SOURCES += ip_types.cpp
libeos_la_SOURCES += ip_intf.cpp
libeos_la_SOURCES += ip_route.cpp
libeos_la_SOURCES += fib.cpp
libeos_la_SOURCES += iterator.cpp
libeos_la_SOURCES += macsec.cpp
libeos_la_SOURCES += mac_table.cpp
libeos_la_SOURCES += mlag.cpp
libeos_la_SOURCES += mpls.cpp
libeos_la_SOURCES += mpls_route.cpp
libeos_la_SOURCES += mpls_vrf_label.cpp
libeos_la_SOURCES += nexthop_group.cpp
libeos_la_SOURCES += panic.cpp
libeos_la_SOURCES += neighbor_table.cpp
libeos_la_SOURCES += policy_map.cpp
libeos_la_SOURCES += policy_map_types.cpp
libeos_la_SOURCES += route_map.cpp
libeos_la_SOURCES += sdk.cpp
libeos_la_SOURCES += SdkImpl.cpp SdkImpl.h
libeos_la_SOURCES += subintf.cpp
libeos_la_SOURCES += system.cpp
libeos_la_SOURCES += timer.cpp
libeos_la_SOURCES += tracing.cpp
libeos_la_SOURCES += version.cpp
libeos_la_SOURCES += vrf.cpp
libeos_la_SOURCES += bfd.cpp
libeos_la_SOURCES += bgp.cpp
libeos_la_SOURCES += bgp_path.cpp
libeos_la_SOURCES += lldp.cpp
libeos_la_SOURCES += xcvr.cpp
libeos_la_SOURCES += nexthop_group_tunnel.cpp
# Add in auto generated X_gen.cpp files too.
libeos_la_SOURCES += acl_gen.cpp
libeos_la_SOURCES += bfd_gen.cpp
libeos_la_SOURCES += bgp_path_gen.cpp
libeos_la_SOURCES += bgp_gen.cpp
libeos_la_SOURCES += class_map_gen.cpp
libeos_la_SOURCES += decap_group_gen.cpp
libeos_la_SOURCES += directflow_gen.cpp
libeos_la_SOURCES += eapi_gen.cpp
libeos_la_SOURCES += eth_lag_intf_gen.cpp
libeos_la_SOURCES += eth_phy_intf_gen.cpp
libeos_la_SOURCES += fib_gen.cpp
libeos_la_SOURCES += hardware_table_gen.cpp
libeos_la_SOURCES += intf_gen.cpp
libeos_la_SOURCES += ip_route_gen.cpp
libeos_la_SOURCES += ip_gen.cpp
libeos_la_SOURCES += lldp_gen.cpp
libeos_la_SOURCES += macsec_gen.cpp
libeos_la_SOURCES += mac_table_gen.cpp
libeos_la_SOURCES += mpls_route_gen.cpp
libeos_la_SOURCES += mpls_vrf_label_gen.cpp
libeos_la_SOURCES += neighbor_table_gen.cpp
libeos_la_SOURCES += nexthop_group_tunnel_gen.cpp
libeos_la_SOURCES += nexthop_group_gen.cpp
libeos_la_SOURCES += policy_map_gen.cpp
libeos_la_SOURCES += route_map_gen.cpp
libeos_la_SOURCES += structured_filter_gen.cpp
libeos_la_SOURCES += subintf_gen.cpp
libeos_la_SOURCES += vrf_gen.cpp

libeos_la_CPPFLAGS = $(AM_CPPFLAGS) $(SHIPPING_FLAG) -fPIC -fPIE
libeos_la_LDFLAGS = -version-info $(SDK_LIBTOOL_VERSION) -lrt
libeos_la_LDFLAGS += -soname libeos.so.$(SDK_VERSION_MAJOR).$(SDK_VERSION_MINOR)

noinst_PROGRAMS = HelloWorld
HelloWorld_SOURCES = examples/HelloWorld.cpp
HelloWorld_LDADD = libeos.la
HelloWorld_CPPFLAGS = -fPIE

# --------- #
# SWIG libs #
# --------- #

if USE_PYTHON
SWIG_FILES := EosSdk.i SwigUtils.i Includes.i SwigRenamer.py swig.patch
python_PYTHON = $(srcdir)/eossdk.py
pyexec_LTLIBRARIES = _eossdk.la
_eossdk_la_SOURCES = $(srcdir)/eossdk_wrap.cpp $(srcdir)/eossdk_wrap.h
_eossdk_la_LDFLAGS = -avoid-version -module
# Swig generated code produces some warnings, depending on the combination of
# Python version and GCC version, so we turn the problematic ones off here as
# we build with -Werror:
_eossdk_la_CXXFLAGS = $(AM_CXXFLAGS) -Wno-strict-aliasing -Wno-missing-field-initializers
_eossdk_la_CXXFLAGS += -Wno-error=maybe-uninitialized -Wno-error=unused-function
_eossdk_la_CPPFLAGS = -I/usr/include/python$(PYTHON_VERSION)
_eossdk_la_LIBADD = libeos.la

$(srcdir)/eossdk_wrap.cpp: $(SWIG_FILES) $(nobase_include_HEADERS) $(srcdir)/eossdk_wrap.cpp
	SRCDIR=$(srcdir) prefix [stubs-swig] $(SWIG) -threads -c++ -python -py3 -dirvtable -O -I$(srcdir) -o $@-t $(srcdir)/EosSdk.i
	patch --batch --no-backup-if-mismatch -p0 <$(srcdir)/swig.patch
	mv $@-t $@
	sed 's/#define PyString_AS_STRING.x. PyUnicode_AS_STRING.x./#define PyString_AS_STRING(x) PyBytes_AS_STRING(x)/' -i eossdk_wrap.cpp

$(srcdir)/eossdk_wrap.h: $(srcdir)/eossdk_wrap.cpp

$(srcdir)/eossdk.py: $(srcdir)/eossdk_wrap.cpp

GO_SWIG_FILES := GoEosSdk.i Includes.i SwigRenamer.py

stubsgosrcdir = $(srcdir)/go/src/eossdk
$(srcdir)/eossdkgo_wrap.cpp: $(GO_SWIG_FILES) $(nobase_include_HEADERS)
	SRCDIR=$(srcdir) prefix [stubs-swig] $(SWIG) -c++ -cgo -go -intgosize 32 -O -I$(srcdir) -o $@-go $(srcdir)/GoEosSdk.i
	mv $(srcdir)/$@-go $@

$(stubsgosrcdir)/eossdkgo_wrap.cpp: $(srcdir)/eossdkgo_wrap.cpp
	$(MKDIR_P) $(stubsgosrcdir) && mv $< $@

$(stubsgosrcdir)/eossdkgo_wrap.h: $(srcdir)/eossdkgo_wrap.cpp
	$(MKDIR_P) $(stubsgosrcdir) && mv $(srcdir)/$(@F) $@

$(stubsgosrcdir)/eossdk.go: $(stubsgosrcdir)/eossdkgo_wrap.cpp
	patch --batch --no-backup-if-mismatch -p0 <$(srcdir)/swig-go.patch
	$(MKDIR_P) $(stubsgosrcdir) && mv $(srcdir)/$(@F) $@

BUILT_SOURCES = $(_eossdk_la_SOURCES)

GO_SRC_FILES = $(stubsgosrcdir)/eossdkgo_wrap.cpp $(stubsgosrcdir)/eossdkgo_wrap.h $(stubsgosrcdir)/eossdk.go
MAINTAINERCLEANFILES = $(BUILT_SOURCES)
endif


ACLOCAL_AMFLAGS = -I autogen
EXTRA_DIST += bootstrap build.sh $(SWIG_FILES) $(GO_SWIG_FILES)
EXTRA_DIST += LICENSE
EXTRA_DIST += ltmain.patch
EXTRA_DIST += $(GO_SRC_FILES)
EXTRA_DIST += Dockerfile

dist-hook:
	chmod -R u+w $(distdir)
	$(MKDIR_P) $(srcdir)/$(stubsgosrcdir)

install-exec-hook:
	-echo "add major.minor link for stubbed libeos"
	cd .libs; ln -sf libeos.so.$(SDK_VERSION_MAJOR).$(SDK_VERSION_MINOR).$(SDK_VERSION_PATCH) libeos.so.$(SDK_VERSION_MAJOR).$(SDK_VERSION_MINOR);
