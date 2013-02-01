#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
"$DIR"/../../bin/mac/LuaHostMac.app/Contents/MacOS/LuaHostMac -workdir "$DIR" -file scripts/main.lua -size 960x640

