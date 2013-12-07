EXTRA_DIST = EosSdk.spec $(TESTS) eossdkpublish

CPP_INCLUDE_FLAGS = -I/usr/include/python$(PYTHON_VERSION) \
   -Isrc-includes -I$(includedir)
AM_CPPFLAGS = $(CPP_INCLUDE_FLAGS) -DTAC_STRING_TO_NAME_CONVERSION
AM_CXXFLAGS = -fvisibility=hidden -std=gnu++0x
AM_CXXFLAGS += -Wextra -Wall -Werror -Wno-unused-parameter
AM_LDFLAGS = -Wl,--no-undefined

lib_LTLIBRARIES = libeos.la
bin_PROGRAMS =
bin_PROGRAMS += EchoBot
noinst_PROGRAMS =
noinst_PROGRAMS += EthAddrTest
noinst_PROGRAMS += EthIntfTestAgent
noinst_PROGRAMS += IntfIdTest
noinst_PROGRAMS += IntfTestAgent
noinst_PROGRAMS += IpAddrTest
bin_SCRIPTS = eossdkpublish

PUBLISHED_HEADER_FILES = eos/agent.h
PUBLISHED_HEADER_FILES += eos/base.h
PUBLISHED_HEADER_FILES += eos/eth.h
PUBLISHED_HEADER_FILES += eos/eth_intf.h
PUBLISHED_HEADER_FILES += eos/fd.h
PUBLISHED_HEADER_FILES += eos/intf.h
PUBLISHED_HEADER_FILES += eos/ip.h
PUBLISHED_HEADER_FILES += eos/panic.h
PUBLISHED_HEADER_FILES += eos/timer.h
PUBLISHED_HEADER_FILES += eos/version.h

eosheaderdir = $(includedir)/eos
eosheader_HEADERS = $(PUBLISHED_HEADER_FILES)

eos/%.h: $(srcdir)/%.h $(srcdir)/eossdkpublish
	mkdir -p eos
	rm -f $@
	$(srcdir)/eossdkpublish < $< > $@
	chmod 444 $@

pkginclude_HEADERS = Conversions.h Mount.h

libeos_la_SOURCES =
libeos_la_SOURCES += agent.cpp
libeos_la_SOURCES += base.h
libeos_la_SOURCES += Conversions.h
libeos_la_SOURCES += EosSdkAgent.tac EosSdkAgent.tin
libeos_la_SOURCES += eth.h eth.cpp
libeos_la_SOURCES += eth_intf.h eth_intf.cpp
libeos_la_SOURCES += EthIntfMgrSm.tac
libeos_la_SOURCES += fd.h fd.cpp
libeos_la_SOURCES += FileSm.tac
libeos_la_SOURCES += intf.h intf.cpp
libeos_la_SOURCES += IntfMgrSm.tac
libeos_la_SOURCES += ip.h ip.cpp
libeos_la_SOURCES += Mount.h Mount.cpp
libeos_la_SOURCES += panic.h panic.cpp
libeos_la_SOURCES += timer.h timer.cpp
libeos_la_SOURCES += TimerSm.tac
libeos_la_SOURCES += version.h version.cpp

libeos_la_LIBADD = -lAgentBase -lSysdbEntityMgr -ltac -ldl
libeos_la_LIBADD += -lIntf -lArnet -lArk -lEthIntf
libeos_la_LDFLAGS = -version-info $(SDK_LIBTOOL_VERSION)

IntfIdTest_SOURCES = test/IntfIdTest.cpp
IntfIdTest_LDADD = libeos.la

EthAddrTest_SOURCES = test/EthAddrTest.cpp
EthAddrTest_LDADD = libeos.la

IntfTestAgent_SOURCES = test/IntfTestAgent.cpp
IntfTestAgent_LDADD = libeos.la

IpAddrTest_SOURCES = test/IpAddrTest.cpp
IpAddrTest_LDADD = libeos.la

EthIntfTestAgent_SOURCES = test/EthIntfTestAgent.cpp
EthIntfTestAgent_LDADD = libeos.la

EchoBot_SOURCES = examples/EchoBot.cpp
EchoBot_LDADD = libeos.la

LIBMAP = .libs/tacc/map.d/$(PACKAGE).map
mapdir = $(libdir)/tacc/map.d
map_DATA = $(LIBMAP)

$(LIBMAP): $(lib_LTLIBRARIES)
	mkdir -p .libs/tacc/map.d
	tacFindFactories $(addprefix .libs/,$(subst .la,.so,$^)) >$@

TESTS_ENVIRONMENT = SRCDIR="$(srcdir)"

python_PYTHON = EosSdkTestLib.py

sanityTests = 
TESTS = $(sanityTests)
TESTS += EthAddrTest
TESTS += examples/EchoBotTest.py
TESTS += IntfIdTest
TESTS += IpAddrTest
TESTS += test/EthIntfTest.py
TESTS += test/IntfTest.py
sanity:
	make TESTS="$(sanityTests)" check

#--------------------------------------------------------------------------------
# Include parallel make support and enable it by overriding check-TESTS.  The 
# space before 'include' causes automake to ignore the line; do not delete it.
#--------------------------------------------------------------------------------
 include Ark/Makefile.ark
check-TESTS: check.ark

install-exec-hook:
	[ -n "$(DESTDIR)" ] || a4 post EosSdk.spec

SUFFIXES = .tac
TACC := tacc
TACCFLAGS = +ntd-N
.tac.cpp:
	$(TACC) $(TACCFLAGS) $(CPP_INCLUDE_FLAGS) $<
TAC_FILES = $(filter %.tac,$(SOURCES))
TAC_CPP_FILES = $(subst .tac,.cpp,$(TAC_FILES))
TAC_H_FILES = $(subst .tac,.h,$(TAC_FILES))
TAC_D_FILES = $(subst .tac,.tac.d,$(TAC_FILES))
BUILT_SOURCES = $(TAC_CPP_FILES) $(PUBLISHED_HEADER_FILES)
clean-local:
	rm -f $(TAC_CPP_FILES)
	rm -f $(TAC_H_FILES)
	rm -f $(TAC_D_FILES)
	rm -f $(PUBLISHED_HEADER_FILES)
-include *.d
