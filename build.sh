#!/bin/sh
LANG=C
export LANG
unset DISPLAY  
CFLAGS='-Os -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector -fno-var-tracking -fno-var-tracking-assignments --param=ssp-buffer-size=4 -Wno-unused -Wno-uninitialized -m32 -march=i686 -mtune=atom -fasynchronous-unwind-tables'
export CFLAGS
CXXFLAGS=$CFLAGS
export CXXFLAGS

set -e
test -f configure || ./bootstrap
test -f Makefile || ./configure --build=i686-pc-linux-gnu --host=i686-pc-linux-gnu --program-prefix= --disable-dependency-tracking --prefix=/usr --exec-prefix=/usr --bindir=/usr/bin --sbindir=/usr/sbin --sysconfdir=/etc --datadir=/usr/share --includedir=/usr/include --libdir=/usr/lib --libexecdir=/usr/libexec --localstatedir=/var --sharedstatedir=/var/lib --mandir=/usr/share/man --infodir=/usr/share/info
exec make "$@"
