#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR/../"

find . -type f | xargs chmod 644 $1
find . -type f | grep "\.sh" | xargs chmod 755 $1

chmod 755 bin/mac/tolua++
chmod 755 player/mac/player.app/Contents/MacOS/player
