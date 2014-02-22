#!/bin/sh
LANG=C
export LANG
unset DISPLAY
CFLAGS='-Os -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector -fno-var-tracking -fno-var-tracking-assignments --param=ssp-buffer-size=4 -Wno-unused -Wno-uninitialized -m32 -march=i686 -mtune=atom -fasynchronous-unwind-tables'
export CFLAGS
CXXFLAGS=$CFLAGS
export CXXFLAGS

# Extract the arguments that we need to forward to `./configure'.
# Other arguments will be passed to `make'.  This is so that one can
# do something along the lines of `./build.sh --enable-python check',
# for instance.
configure_flags=''
for arg; do
   case $arg in
      (--enable-*|--disable-*|--with-*|--without-*)
         configure_flags="$configure_flags $arg"
         shift
         ;;
   esac
done

set -e
test -f configure || ./bootstrap
test -f Makefile || ./configure $configure_flags \
   --build=i686-pc-linux-gnu --host=i686-pc-linux-gnu --program-prefix= \
   --prefix=/usr --exec-prefix=/usr --bindir=/usr/bin --sbindir=/usr/sbin \
   --sysconfdir=/etc --datadir=/usr/share --includedir=/usr/include \
   --libdir=/usr/lib --libexecdir=/usr/libexec --localstatedir=/var \
   --sharedstatedir=/var/lib --mandir=/usr/share/man --infodir=/usr/share/info
exec make "$@"
