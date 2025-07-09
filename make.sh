#!/bin/sh
# Source toolchain first
TOOLCHAIN_LOCATION=~/Tools/remarkable-toolchain
SYSROOT_LOCATION=$TOOLCHAIN_LOCATION/sysroots/cortexa53-crypto-remarkable-linux
. $TOOLCHAIN_LOCATION/env*

aarch64-remarkable-linux-g++ -I $SYSROOT_LOCATION/usr/include/QtCore -I $SYSROOT_LOCATION/usr/include/QtGui/ -I $SYSROOT_LOCATION/usr/include/ --sysroot $SYSROOT_LOCATION -L. -lqsgepaper epfb.cpp -fPIC -shared -o libepfb.so
# Make sure to link against libepfb.so first!
aarch64-remarkable-linux-g++ -I $SYSROOT_LOCATION/usr/include/QtCore -I $SYSROOT_LOCATION/usr/include/QtGui/ -I $SYSROOT_LOCATION/usr/include/ --sysroot $SYSROOT_LOCATION -lepfb -lQt6Core -lQt6Gui -L. -lqsgepaper test.cpp -o test
