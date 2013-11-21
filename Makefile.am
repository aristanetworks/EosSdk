EXTRA_DIST = EosSdk.spec $(TESTS) test/EosSdkTestLib.py

CPP_INCLUDE_FLAGS = -I/usr/include/python$(PYTHON_VERSION) \
   -Isrc-includes -I$(includedir)
AM_CPPFLAGS = $(CPP_INCLUDE_FLAGS) -DTAC_STRING_TO_NAME_CONVERSION
AM_CXXFLAGS = -std=gnu++0x -Wextra -Wall -Werror -Wno-unused-parameter
AM_LDFLAGS = -Wl,--no-undefined

lib_LTLIBRARIES = libeos.la
bin_PROGRAMS = IntfTestAgent # demo1 
nobase_pkginclude_HEADERS = eos/agent.h eos/intf.h eos/ip.h

eos/%.h: $(srcdir)/%.h $(srcdir)/publish
	mkdir -p eos
	rm -f $@
	$(srcdir)/publish < $< > $@
	chmod 444 $@

libeos_la_SOURCES =
libeos_la_SOURCES += EosSdkAgent.tac EosSdkAgent.tin
libeos_la_SOURCES += types.h agent.cpp Mount.h Mount.cpp
libeos_la_SOURCES += panic.cpp
libeos_la_SOURCES += TimerSm.tac TimerSm.tin timer.h timer.cpp
libeos_la_SOURCES += IntfMgrSm.tac IntfMgrSm.tin intf.h intf.cpp
libeos_la_SOURCES += ip.h ip.cpp

libeos_la_LIBADD = -lAgentBase -lSysdbEntityMgr -ltac -ldl
libeos_la_LIBADD += -lIntf -lArnet

# demo1_SOURCES = examples/demo1.cpp <<<
# demo1_LDADD = libeos.la <<<

IntfTestAgent_SOURCES = test/IntfTestAgent.cpp
IntfTestAgent_LDADD = libeos.la

LIBMAP = .libs/tacc/map.d/$(PACKAGE).map
mapdir = $(libdir)/tacc/map.d
map_DATA = $(LIBMAP)

$(LIBMAP): $(lib_LTLIBRARIES)
	mkdir -p .libs/tacc/map.d
	tacFindFactories $(addprefix .libs/,$(subst .la,.so,$^)) >$@

TESTS_ENVIRONMENT = SRCDIR="$(srcdir)"

sanityTests = 
TESTS = $(sanityTests)
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
BUILT_SOURCES = $(TAC_CPP_FILES)
clean-local:
	rm -f $(TAC_CPP_FILES)
	rm -f $(TAC_H_FILES)
	rm -f $(TAC_D_FILES)
-include *.d
