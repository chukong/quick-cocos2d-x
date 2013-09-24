#!/usr/bin/env bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SRCDIR=$DIR/LuaJit-2.0.2
DESTDIR=$DIR/mac
MACOSX_DEPLOYMENT_TARGET="10.6"

rm "$DESTDIR"/*.a

cd $SRCDIR
make clean
make CC="clang -arch x86_64" clean all

if [ -f $SRCDIR/src/libluajit.a ]; then
    mv $SRCDIR/src/libluajit.a $DESTDIR/libluajit2.a
fi;

make clean
