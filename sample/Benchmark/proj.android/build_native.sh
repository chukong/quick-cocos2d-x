#!/usr/bin/env bash

APPNAME="benchmark"

# options

buildexternalsfromsource=
chinamobile=

usage() {
    cat << EOF
    usage: $0 [options]

    Build C/C++ code for $APPNAME using Android NDK

    OPTIONS:
    -s	Build externals from source
    -h	this help
EOF
}

while getopts "sch" OPTION; do
    case "$OPTION" in
        s)
            buildexternalsfromsource=1
            shift `expr $OPTIND - 1`
            ;;
        h)
            usage
            exit 0
            ;;
    esac
done

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
APP_ROOT="$DIR/.."
APP_ANDROID_ROOT="$DIR"

if [ -d "/cygdrive/" ]; then
    ANDROID_NDK_ROOT=`cygpath "$ANDROID_NDK_ROOT"`
    QUICK_COCOS2DX_ROOT=`cygpath "$QUICK_COCOS2DX_ROOT"`
    COCOS2DX_ROOT=`cygpath "$COCOS2DX_ROOT"`
fi

echo "- config:"
echo "  ANDROID_NDK_ROOT    = $ANDROID_NDK_ROOT"
echo "  QUICK_COCOS2DX_ROOT = $QUICK_COCOS2DX_ROOT"
echo "  COCOS2DX_ROOT       = $COCOS2DX_ROOT"
echo "  APP_ROOT            = $APP_ROOT"
echo "  APP_ANDROID_ROOT    = $APP_ANDROID_ROOT"

echo "- cleanup"
chmod -R 755 "$APP_ANDROID_ROOT"
if [ -d "$APP_ANDROID_ROOT"/bin ]; then
    rm -rf "$APP_ANDROID_ROOT"/bin/*.apk
fi
mkdir -p "$APP_ANDROID_ROOT"/bin
chmod 755 "$APP_ANDROID_ROOT"/bin

if [ -d "$APP_ANDROID_ROOT"/assets ]; then
    rm -rf "$APP_ANDROID_ROOT"/assets/*
fi
mkdir -p "$APP_ANDROID_ROOT"/assets
chmod 755 "$APP_ANDROID_ROOT"/assets

echo "- copy scripts"
cp -rf "$APP_ROOT"/scripts "$APP_ANDROID_ROOT"/assets/
echo "- copy resources"
cp -rf "$APP_ROOT"/res "$APP_ANDROID_ROOT"/assets/

# build
if [[ "$buildexternalsfromsource" ]]; then
    echo "Building external dependencies from source"
    "$ANDROID_NDK_ROOT"/ndk-build -j -C "$APP_ANDROID_ROOT" $* \
    "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/source"
else
    echo "Using prebuilt externals"
    "$ANDROID_NDK_ROOT"/ndk-build -j -C "$APP_ANDROID_ROOT" $* \
    "NDK_MODULE_PATH=${QUICK_COCOS2DX_ROOT}:${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt"
fi
