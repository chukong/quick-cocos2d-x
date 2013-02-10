#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"
OUTPUT_DIR="$DIR"/../extra/luabinding
"$DIR"/../../../../tools/make_luabinding.sh -E CCOBJECTS=CCHTTPRequest,CCStorePaymentTransaction,CCStoreProduct -d "$OUTPUT_DIR" cocos2d-x-extra-luabinding.tolua
