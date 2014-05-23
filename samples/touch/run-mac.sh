#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

BIN="$DIR/proj.mac/bin/touch.app/Contents/MacOS/touch"
if [ ! -f $BIN ]; then
    echo "PLEASE BUILD proj.mac/touch.xcodeproj FIRST"
    exit
fi

ARG="-relaunch-off -quick $QUICK_COCOS2DX_ROOT -workdir $DIR"
SIZE="-size 480x800"
CMD="$BIN $ARG $SIZE"

until $CMD; do
    echo ""
    echo "------------------------------------------------------"
    echo ""
    echo ""
    echo ""
done
