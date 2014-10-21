#!/usr/bin/env bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"
OUTPUT_DIR="$DIR"
MAKE_LUABINDING="$QUICK_COCOS2DX_ROOT"/bin/compile_luabinding.sh
$MAKE_LUABINDING -E CCOBJECTS=CCHTTPRequest -d "$OUTPUT_DIR" cocos2dx_extra_luabinding.tolua
echo ""
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo ""
$MAKE_LUABINDING -E CCOBJECTS=CCHTTPRequest -d "$OUTPUT_DIR" cocos2dx_httprequest_luabinding.tolua
echo ""
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo ""
$MAKE_LUABINDING -d "$OUTPUT_DIR" cocos2dx_extra_ios_iap_luabinding.tolua
echo ""
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo ""
$MAKE_LUABINDING -d "$OUTPUT_DIR" CZHelperFunc_luabinding.tolua
