#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"
OUTPUT_DIR="$DIR"
"$DIR"/../../bin/compile_luabinding.sh -E CCOBJECTS=CCScale9Sprite,CCControl,CCControlButton,CCEditBox -d "$OUTPUT_DIR" cocos2dx_extensions_luabinding.tolua
