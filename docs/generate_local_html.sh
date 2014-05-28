#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SOURCE_DIR="$DIR/../framework"
CONFIG_PATH="$DIR/apidoc_config.json"
TEMP_DIR="$DIR/tmp/"
DOC_DIR="$DIR/api/"

if [ -d "$TEMP_DIR" ]; then
    rm -r "$TEMP_DIR"
fi

php "$LUADOCX" extract -c "$CONFIG_PATH" "$SOURCE_DIR" "$TEMP_DIR"
php "$LUADOCX" generate -c "$CONFIG_PATH" "$TEMP_DIR" "$DOC_DIR"

if [ -d "$TEMP_DIR" ]; then
    rm -r "$TEMP_DIR"
fi

