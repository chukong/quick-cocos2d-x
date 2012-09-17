#!/bin/sh
BASEDIR=`dirname $0`
xcodebuild -project $BASEDIR/LuaHostMac.xcodeproj -configuration Debug

