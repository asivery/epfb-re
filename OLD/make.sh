#!/bin/sh
# Source toolchain first
TOOLCHAIN_LOCATION=~/Tools/remarkable-toolchain
SYSROOT_LOCATION=$TOOLCHAIN_LOCATION/sysroots/cortexa53-crypto-remarkable-linux
. $TOOLCHAIN_LOCATION/env*
cp $SYSROOT_LOCATION/usr/lib/plugins/scenegraph/libqsgepaper.so .

aarch64-remarkable-linux-g++ -I $SYSROOT_LOCATION/usr/include/QtCore -I $SYSROOT_LOCATION/usr/include/QtGui/ -I $SYSROOT_LOCATION/usr/include/ --sysroot $SYSROOT_LOCATION -lQt6Core -lQt6Gui -L. -lqsgepaper test.cpp -o test
