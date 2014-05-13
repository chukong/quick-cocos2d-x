#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [ "$QUICK_COCOS2DX_ROOT" == "" ]; then
    echo PLEASE RUN setup-x.app first.
    return
fi

PLAYER="$QUICK_COCOS2DX_ROOT/player/simple_player_mac/simple_player_mac.app/Contents/MacOS/simple_player_mac"
CONFIG="-relaunch-off -quick $QUICK_COCOS2DX_ROOT -workdir $DIR"

# set screen size
SCREEN_SIZE="-size 960x640"

CMD="$PLAYER $CONFIG $SCREEN_SIZE"
until $CMD; do
    echo ""
    echo "------------------------------------------------------"
    echo ""
    echo ""
    echo ""
done
