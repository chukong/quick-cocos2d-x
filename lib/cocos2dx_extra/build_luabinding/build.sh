#!/usr/bin/env bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"
OUTPUT_DIR="$DIR"/../extra/luabinding
MAKE_LUABINDING="$DIR"/../../../bin/compile_luabinding.sh
$MAKE_LUABINDING -E CCOBJECTS=CCHTTPRequest -d "$OUTPUT_DIR" cocos2dx_extra_luabinding.tolua
echo ""
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo ""
$MAKE_LUABINDING -d "$OUTPUT_DIR" cocos2dx_extra_ios_iap_luabinding.tolua
