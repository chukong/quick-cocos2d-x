#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SRCDIR=$DIR/LuaJit-2.0.0
DESTDIR=$DIR/proj.ios
IXCODE=`xcode-select -print-path`
ISDK=$IXCODE/Platforms/iPhoneOS.platform/Developer
ISDKVER=iPhoneOS6.0.sdk
ISDKP=$ISDK/usr/bin/
ISDKF="-arch armv7 -isysroot $ISDK/SDKs/$ISDKVER"

cd $SRCDIR
make HOST_CC="gcc -m32 -arch i386" CROSS=$ISDKP TARGET_FLAGS="$ISDKF" TARGET_SYS=iOS

if [ -f $SRCDIR/src/libluajit.a ]; then
    mv $SRCDIR/src/libluajit.a $DESTDIR/libluajit2.a

    cp $SRCDIR/src/lauxlib.h $DIR/include
    cp $SRCDIR/src/lua.h $DIR/include
    cp $SRCDIR/src/lua.hpp $DIR/include
    cp $SRCDIR/src/luaconf.h $DIR/include
    cp $SRCDIR/src/luajit.h $DIR/include
    cp $SRCDIR/src/lualib.h $DIR/include
fi;
