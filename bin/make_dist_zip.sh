#!/usr/bin/env bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR/../../"
DEST_DIR=`pwd`
VER=`date "+%Y%m%d"`
TMP_DIR="/tmp/quick-cocos2d-x-$VER"
DEST_FILE="$DEST_DIR/quick-cocos2d-x-$VER.zip"
mkdir -p "$TMP_DIR"
if [ ! -d "$TMP_DIR" ]; then
    echo "[ERROR] Can't create temp dir."
    exit
fi

echo create distribute ZIP: $DEST_FILE...

cd "$TMP_DIR"
rm -fr "$TMP_DIR/*"

cd "$DIR/../"
git archive HEAD | tar -x -C "$TMP_DIR"
mkdir -p "$TMP_DIR/lib/cocos2d-x"

cd "$DIR/../lib/cocos2d-x"
git archive HEAD | tar -x -C "$TMP_DIR/lib/cocos2d-x"
cd "$TMP_DIR/../"
zip -q -9 -r $DEST_FILE "quick-cocos2d-x-$VER"
rm -fr "$TMP_DIR"
