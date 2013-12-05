EXTRA_DIST = EosSdk.spec $(TESTS) eossdkpublish

CPP_INCLUDE_FLAGS = -I/usr/include/python$(PYTHON_VERSION) \
   -Isrc-includes -I$(includedir)
AM_CPPFLAGS = $(CPP_INCLUDE_FLAGS) -DTAC_STRING_TO_NAME_CONVERSION
AM_CXXFLAGS = -std=gnu++0x -Wextra -Wall -Werror -Wno-unused-parameter
AM_LDFLAGS = -Wl,--no-undefined

lib_LTLIBRARIES = libeos.la
bin_PROGRAMS =
bin_PROGRAMS += IntfTestAgent
bin_PROGRAMS += EthIntfTestAgent
bin_PROGRAMS += EchoBot
bin_PROGRAMS += IntfIdTest
bin_PROGRAMS += EthAddrTest
bin_SCRIPTS = eossdkpublish

PUBLISHED_HEADER_FILES = eos/agent.h
PUBLISHED_HEADER_FILES += eos/types.h
PUBLISHED_HEADER_FILES += eos/panic.h
PUBLISHED_HEADER_FILES += eos/timer.h
PUBLISHED_HEADER_FILES += eos/fd.h
PUBLISHED_HEADER_FILES += eos/intf.h
PUBLISHED_HEADER_FILES += eos/eth.h
PUBLISHED_HEADER_FILES += eos/eth_intf.h
PUBLISHED_HEADER_FILES += eos/ip.h

eosheaderdir = $(includedir)/eos
eosheader_HEADERS = $(PUBLISHED_HEADER_FILES)

eos/%.h: $(srcdir)/%.h $(srcdir)/eossdkpublish
	mkdir -p eos
	rm -f $@
	$(srcdir)/eossdkpublish < $< > $@
	chmod 444 $@

pkginclude_HEADERS = Mount.h IntfId.h

libeos_la_SOURCES =
libeos_la_SOURCES += EosSdkAgent.tac EosSdkAgent.tin
libeos_la_SOURCES += types.h agent.cpp Mount.h Mount.cpp
libeos_la_SOURCES += panic.h panic.cpp
libeos_la_SOURCES += TimerSm.tac timer.h timer.cpp
libeos_la_SOURCES += FileSm.tac fd.h fd.cpp
libeos_la_SOURCES += IntfMgrSm.tac intf.h intf.cpp
libeos_la_SOURCES += ip.h ip.cpp
libeos_la_SOURCES += eth.h eth.cpp
libeos_la_SOURCES += EthIntfMgrSm.tac eth_intf.h eth_intf.cpp

libeos_la_LIBADD = -lAgentBase -lSysdbEntityMgr -ltac -ldl
libeos_la_LIBADD += -lIntf -lArnet -lArk -lEthIntf

IntfIdTest_SOURCES = test/IntfIdTest.cpp
IntfIdTest_LDADD = libeos.la

EthAddrTest_SOURCES = test/EthAddrTest.cpp
EthAddrTest_LDADD = libeos.la

IntfTestAgent_SOURCES = test/IntfTestAgent.cpp
IntfTestAgent_LDADD = libeos.la

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
TESTS += ${builddir}/IntfIdTest
TESTS += ${builddir}/EthAddrTest
TESTS += test/IntfTest.py
TESTS += test/EthIntfTest.py
TESTS += examples/EchoBotTest.py
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
	mkdir -p $(DESTDIR)$(bindir)

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
