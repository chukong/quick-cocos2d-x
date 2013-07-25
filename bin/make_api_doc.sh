#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
LUADOCX="$DIR/lib/luadocx/luadocx.php"
ROOT_DIR="`dirname $DIR`"
SOURCE_DIR="$ROOT_DIR/framework"
CONFIG_PATH="$ROOT_DIR/doc/apidoc_config.json"
TEMP_DIR="$ROOT_DIR/tmp/apidoc"

if [ ! -d $TEMP_DIR ]; then
    mkdir -p $TEMP_DIR
fi

if [ -f $TEMP_DIR/* ]; then
    rm -fr $TEMP_DIR/*
fi

php "$LUADOCX" extract -c "$CONFIG_PATH" "$SOURCE_DIR" "$TEMP_DIR"
