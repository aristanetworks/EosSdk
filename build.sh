#!/bin/bash
LANG=C
export LANG
unset DISPLAY
CFLAGS='-Os -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector --param=ssp-buffer-size=4 -Wno-unused -Wno-uninitialized -fasynchronous-unwind-tables'
CFLAGS_32B='-m32 -march=i686 -mtune=atom'
export CFLAGS
CXXFLAGS=$CFLAGS
export CXXFLAGS
CXXFLAGS_32B="-m32" 
LDFLAGS_32B="-m32" 
export LDFLAGS

target_32b=true
libdir="lib"

# Extract the arguments that we need to forward to `./configure'.
# Other arguments will be passed to `make'.  This is so that one can
# do something along the lines of `./build.sh --enable-python check',
# for instance.
configure_flags='--host=x86_64-pc-linux-gnu'
for arg; do
   case $arg in
      (--enable-*|--disable-*|--with-*|--without-*|--host=*|--build=*|--prefix=*|--libdir=*)
         configure_flags="$configure_flags $arg"
         shift
         ;;
      (-m64|--m64)
         target_32b=false
         libdir="lib64"
         shift
         ;;
      (-m32|--m32)
         target_32b=true
         libdir="lib"
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
   CXXFLAGS="$CXXFLAGS $CXXFLAGS_32B"
   LDFLAGS="$LDFLAGS $LDFLAGS_32B"
fi

sysroot=$($(which gcc) --print-sysroot) || sysroot = ""
inst_prefix="--prefix=$sysroot/usr"
inst_libdir="--libdir=$sysroot/usr/$libdir"
# if prefix already set in configure_flags, skip sysroot one
if grep -q -- "--prefix=" <<< "$configure_flags"; then
  inst_prefix=""
fi
if grep -q -- "--libdir=" <<< "$configure_flags"; then
  inst_libdir=""
fi

set -e
test -f configure || ./bootstrap
test -f Makefile || ./configure  \
   $configure_flags --program-prefix= \
   $inst_prefix \
   $inst_libdir \

set -x
STUBS_DIR=$PWD
GO_SRCDIR="$STUBS_DIR/go/src/eossdk"
if [ -d $GO_SRCDIR/eos ]; then
   rm -f "$GO_SRCDIR/eos"
   ln -s "$STUBS_DIR/eos" "$GO_SRCDIR/"
fi

exec make "$@"
