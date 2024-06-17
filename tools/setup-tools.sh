#!/usr/bin/env bash

set -xe

BINUTILSVER=2.42
GCCVER=14.1.0

SCRIPTPATH=$(dirname $(realpath "$0"))
cd "$SCRIPTPATH"

if [ -d "$SCRIPTPATH/src" ]; then
   echo "src directory found, please remove it and run this script again"
   exit 0
fi

if [ -d "$SCRIPTPATH/path" ]; then
   echo "path directory found, please remove it and run this script again"
   exit 0
fi

if [ ! -d "$SCRIPTPATH/autotools" ]; then
   AUTOPREFIX=$SCRIPTPATH/autotools

   # if you already have it setup you dont need to again
   if [ -e "$AUTOPREFIX" ]; then
      exit 0
   fi

   mkdir -p "$AUTOPREFIX"

   mkdir tmp
   cd tmp

   wget "https://ftp.gnu.org/gnu/automake/automake-1.15.1.tar.xz"
   tar -xvf "automake-1.15.1.tar.xz"
   cd "automake-1.15.1"
   ./configure --prefix="$AUTOPREFIX"
   make -j $(nproc)
   make install
   cd ..


   wget "https://ftp.gnu.org/gnu/autoconf/autoconf-2.69.tar.xz"
   tar -xvf "autoconf-2.69.tar.xz"
   cd "autoconf-2.69"
   ./configure --prefix="$AUTOPREFIX"
   make -j $(nproc)
   make install
   cd ..

   cd ..
   rm -rf tmp
fi

export PREFIX="$(pwd)/path"
export TARGET=x86_64-moss
export PATH="$SCRIPTPATH/autotools/bin:$SCRIPTPATH/path/bin:$PATH"
export SYSROOT="$SCRIPTPATH/../sysroot"

mkdir path
mkdir src
cd src

# binutils
wget https://ftp.gnu.org/gnu/binutils/binutils-"$BINUTILSVER".tar.xz
tar -xvf binutils-"$BINUTILSVER".tar.xz

cd binutils-"$BINUTILSVER"
patch -p1 <$SCRIPTPATH/patches/binutils.diff
cd ld
automake
cd ../..

mkdir -p build-binutils
cd build-binutils

../binutils-"$BINUTILSVER"/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot="$SYSROOT" --disable-nls --enable-shared
make -j $(nproc)
make install
cd ..
rm -rf binutils-"$BINUTILSVER"


# gcc
wget https://ftp.gnu.org/gnu/gcc/gcc-"$GCCVER"/gcc-"$GCCVER".tar.xz
tar -xvf gcc-"$GCCVER".tar.xz

cd gcc-"$GCCVER"
patch -p1 <$SCRIPTPATH/patches/gcc.diff
cd libstdc++-v3
autoconf
cd ../..

mkdir -p build-gcc
cd build-gcc

../gcc-"$GCCVER"/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot="$SYSROOT" --disable-nls --enable-languages=c --enable-shared
make -j $(nproc) all-gcc
make -j $(nproc) all-target-libgcc
make install-gcc
make install-target-libgcc
