#!/bin/bash
# Copyright (C) 2025 - UTC - Stéphane MOTTELET
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# CGAL build script for Linux and macOS
# cmake should be in the PATH
# boost, gmp, mpfr should be also installed

cd ..
THIRDPARTY="$(pwd)/$(uname -s)/$(uname -m)"
OS=$(uname)
cd build
CGAL_VER=4.7

# CGAL build
curl -LO https://github.com/CGAL/cgal/releases/download/releases%2FCGAL-${CGAL_VER}/CGAL-${CGAL_VER}.tar.xz
tar xf CGAL-${CGAL_VER}.tar.xz

# choose default CGAL_LITTLE_ENDIAN for unknown arch (typically ARM)
patch CGAL-${CGAL_VER}/include/CGAL/config.h config.patch 

cd CGAL-${CGAL_VER}
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX="${THIRDPARTY}" ..
make -j
make install

if [ "$OS" = "Darwin" ]; then
    cp ${CONDA_PREFIX}/lib/libboost_thread.dylib ${THIRDPARTY}/lib/
    cp ${CONDA_PREFIX}/lib/libgmp.dylib ${THIRDPARTY}/lib/
elif [ "$OS" = "Linux" ]; then
    cp /usr/lib/x86_64-linux-gnu/libboost_thread.so ${THIRDPARTY}/lib
    cp /usr/lib/x86_64-linux-gnu/libgmp.so ${THIRDPARTY}/lib
fi
