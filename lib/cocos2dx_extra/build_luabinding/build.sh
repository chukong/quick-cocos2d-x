#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"
OUTPUT_DIR="$DIR"/../extra/luabinding
"$DIR"/../../../bin/make_luabinding.sh -E CCOBJECTS=CCHTTPRequest,CCStorePaymentTransaction,CCStoreProduct -d "$OUTPUT_DIR" cocos2dx_extra_luabinding.tolua
