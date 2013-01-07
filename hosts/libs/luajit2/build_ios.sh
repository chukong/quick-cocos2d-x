#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SRCDIR=$DIR/LuaJit-2.0.0
DESTDIR=$DIR/proj.ios
IXCODE=`xcode-select -print-path`
ISDK=$IXCODE/Platforms/iPhoneOS.platform/Developer
ISDKVER=iPhoneOS6.0.sdk
ISDKP=$ISDK/usr/bin/
ISDKF="-arch armv7 -isysroot $ISDK/SDKs/$ISDKVER"

rm "$DESTDIR"/*.a

cd $SRCDIR
make HOST_CC="gcc -m32 -arch i386" CROSS=$ISDKP TARGET_FLAGS="$ISDKF" TARGET_SYS=iOS
mv "$SRCDIR"/src/libluajit.a "$DESTDIR"/libluajit2-armv7.a

make CC="gcc -m32 -arch i386" clean all
mv "$SRCDIR"/src/libluajit.a "$DESTDIR"/libluajit2-i386.a

lipo -create "$DESTDIR"/libluajit2-*.a -output "$DESTDIR"/libluajit2.a
rm "$DESTDIR"/libluajit2-*.a
