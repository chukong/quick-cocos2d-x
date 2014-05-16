#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ARG="-relaunch-off -quick $QUICK_COCOS2DX_ROOT -workdir $DIR"
SIZE="-size 480x800"
CMD="$DIR/proj.mac/bin/__PROJECT_PACKAGE_LAST_NAME_L__.app/Contents/MacOS/__PROJECT_PACKAGE_LAST_NAME_L__ $ARG $SIZE"

until $CMD; do
    echo ""
    echo "------------------------------------------------------"
    echo ""
    echo ""
    echo ""
done

