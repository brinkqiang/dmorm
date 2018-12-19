#!/bin/bash

# - install depends tools
# yum -y install git
# yum -y install gcc gcc-c++ autoconf libtool automake make
#

# - clone code
# git clone https://github.com/brinkqiang/dmgen4pborm.git
# pushd dmgen4pborm
# git submodule update --init --recursive
#

pushd thirdparty/ctemplate
libtoolize && aclocal && autoheader && autoconf && automake --add-missing
sh configure
popd

rm -rf build
mkdir build
pushd build
cmake -DCMAKE_BUILD_TYPE=relwithdebinfo ..
cmake --build .
popd

# popd

# echo continue && read -n 1
