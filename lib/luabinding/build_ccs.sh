#!/bin/bash
DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
TOLUA="$QUICK_COCOS2DX_ROOT/bin/mac/tolua++"

cd "$DIR/"
${TOLUA} -L "$DIR/basic_ccs.lua" -o "$QUICK_COCOS2DX_ROOT/lib/cocos2d-x/scripting/lua/cocos2dx_support/LuaCocoStudio.cpp" CocoStudio.tolua
