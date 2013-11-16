EXTRA_DIST = EosSdk.spec $(TESTS)

CPP_INCLUDE_FLAGS = -I/usr/include/python$(PYTHON_VERSION) \
   -Isrc-includes -I$(includedir)
AM_CPPFLAGS = $(CPP_INCLUDE_FLAGS) -DTAC_STRING_TO_NAME_CONVERSION
AM_CXXFLAGS = -std=gnu++0x -Wextra -Wall -Werror -Wno-unused-parameter
AM_LDFLAGS = -Wl,--no-undefined

lib_LTLIBRARIES = libEosSdk.la libEosSdkLoader.la
pkginclude_HEADERS = Fwd.h EosSdk.h

libEosSdk_la_SOURCES = EosSdk.cpp
libEosSdk_la_SOURCES += SDKInternal.h
libEosSdk_la_SOURCES += EnumCast.h
libEosSdk_la_SOURCES += EosSdkAgent.tac EosSdkAgent.tin
libEosSdk_la_SOURCES += EthIntfSm.tac EthIntfSm.tin
libEosSdk_la_LIBADD = -lEthIntf -lIntf -lArnet -lAgentBase -lSysdbEntityMgr -ltac -ldl

libEosSdkLoader_la_SOURCES = EosSdkLoader.cpp
libEosSdkLoader_la_LIBADD = -lAgentBase -ltac /usr/lib/Scrt1.o

pkgdata_LTLIBRARIES = libDemoApp.la
libDemoApp_la_SOURCES = test/DemoApp.cpp
libDemoApp_la_LIBADD = libEosSdk.la

LIBMAP = .libs/tacc/map.d/$(PACKAGE).map
mapdir = $(libdir)/tacc/map.d
map_DATA = $(LIBMAP)

$(LIBMAP): $(lib_LTLIBRARIES)
	mkdir -p .libs/tacc/map.d
	tacFindFactories $(addprefix .libs/,$(subst .la,.so,$^)) >$@

TESTS_ENVIRONMENT = SRCDIR="$(srcdir)"

sanityTests = 
TESTS = $(sanityTests)
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
	ln -sf $(libdir)/libEosSdkLoader.so $(DESTDIR)$(bindir)/EosSdk

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
