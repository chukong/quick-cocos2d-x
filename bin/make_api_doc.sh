#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
DEST_DIR="$DIR/../doc/api"
if [ -d "$DEST_DIR" ]; then
    rm -fr "$DEST_DIR/*"
fi
mkdir -p "$DEST_DIR"

cd "$DIR/../"
php "$DIR/lib/luadocx/luadocx.php" -t "quick-cocos2d-x API Documents" -r framework -i framework.init -x framework.client.cocos2dx,framework.server.resty,framework.shared.json framework/ "$DEST_DIR"
