#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SRCDIR=$DIR/LuaJit-2.0.0
DESTDIR=$DIR/proj.mac
MACOSX_DEPLOYMENT_TARGET="10.6"
cd $SRCDIR
make CC="gcc -m32 -arch i386" clean all

if [ -f $SRCDIR/src/libluajit.a ]; then
    mv $SRCDIR/src/libluajit.a $DESTDIR/libluajit2.a
fi;
