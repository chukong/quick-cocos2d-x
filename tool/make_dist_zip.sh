#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
QUICK_COCOS2DX_ROOT=`dirname "$DIR"`

cd "$QUICK_COCOS2DX_ROOT"
if [ -d tmp ]; then
    rm -fr tmp
fi;

read -p "Please enter version : " VER
WORKDIR=tmp/quick-cocos2d-x-$VER

echo "VER = $VER"
echo "WORKDIR = $WORKDIR"

echo ""
echo "exporting files..."

mkdir -p "$WORKDIR"
git archive master -0 -o tmp/tmp.zip
cd "$WORKDIR"

unzip -q ../tmp.zip

echo "create installer..."

rm .gitignore
cd ..
rm tmp.zip

zip -9 -r -q quick-cocos2d-x-$VER.zip quick-cocos2d-x-$VER/
rm -fr quick-cocos2d-x-$VER/

pwd
ls -lFh quick-cocos2d-x-$VER.zip

echo "done."
echo ""
