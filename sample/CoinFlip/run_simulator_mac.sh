#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"
"$DIR/../../simulator/bin/mac/LuaHostMac.app/Contents/MacOS/LuaHostMac" -workdir "$DIR" -file scripts/main.lua -size 480x800
