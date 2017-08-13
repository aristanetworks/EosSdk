#!/bin/sh
LANG=C
export LANG
unset DISPLAY
CFLAGS='-Os -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector --param=ssp-buffer-size=4 -Wno-unused -Wno-uninitialized -fasynchronous-unwind-tables'
CFLAGS_32B='-m32 -march=i686 -mtune=atom'
export CFLAGS

target_32b=true
configure_flags=

# Extract the arguments that we need to forward to `./configure'.
# Other arguments will be passed to `make'.  This is so that one can
# do something along the lines of `./build.sh --enable-python check',
# for instance.
configure_flags=''
for arg; do
   case $arg in
      (--enable-*|--disable-*|--with-*|--without-*|--host=*|--build=*)
         configure_flags="$configure_flags $arg"
         shift
         ;;
      (-m64|--m64)
         target_32b=false
         shift
         ;;
      (-force|--force)
         rm -f Makefile
         shift
         ;;
   esac
done

if $target_32b; then
   CFLAGS="$CFLAGS $CFLAGS_32B"
   configure_flags='--build=i686-pc-linux-gnu --host=i686-pc-linux-gnu'
fi
CXXFLAGS=$CFLAGS
export CXXFLAGS

sysroot=$($(which gcc) --print-sysroot) || sysroot = ""
[ $sysroot -a ${sysroot%fc14-gcc4.9.2-glibc2.19} != $sysroot ] && {
  LDFLAGS="-Wl,--dynamic-linker=$sysroot/lib/ld-linux.so.2 -Wl,-rpath,$sysroot/lib:/usr/lib:/lib"
  export LDFLAGS
}

set -e
test -f configure || ./bootstrap
test -f Makefile || ./configure $configure_flags \
   $configure_flags --program-prefix= \
   --prefix=$sysroot/usr
exec make "$@"
