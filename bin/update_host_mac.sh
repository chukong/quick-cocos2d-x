#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJDIR="$DIR"/../hosts/mac
DESTDIR="$DIR"/../bin/mac
cd "$PROJDIR"
xcodebuild -workspace LuaHostMac.xcworkspace -scheme LuaHostMac -arch i386 ONLY_ACTIVE_ARCH=NO

cp -R build/LuaHostMac/Build/Products/Debug/LuaHostMac.app "$DESTDIR"
