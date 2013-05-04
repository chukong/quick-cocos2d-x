#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
#DIR=/Users/xatest/Downloads/HelloWorld
cd "$DIR"
../../simulator/bin/mac/LuaHostMac.app/Contents/MacOS/LuaHostMac -workdir "$DIR" -file scripts/main.lua -size 640x960
