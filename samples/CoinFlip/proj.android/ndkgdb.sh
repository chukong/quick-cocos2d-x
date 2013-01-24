APPNAME="killfruitcn"
APP_ANDROID_NAME="com.qeeplay.games.$APPNAME"

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
APP_ROOT="$DIR/../../.."
APP_ANDROID_ROOT="$DIR"

echo "ANDROID_NDK_ROOT = $ANDROID_NDK_ROOT"
echo "ANDROID_SDK_ROOT = $ANDROID_SDK_ROOT"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"
echo "APP_ANDROID_NAME = $APP_ANDROID_NAME"

echo
echo "Killing and restarting ${APP_ANDROID_NAME}"
echo

set -x

"${ANDROID_SDK_ROOT}"/platform-tools/adb shell am start "${APP_ANDROID_NAME}"

NDK_MODULE_PATH="${QUICK_COCOS2DX_ROOT}:${APP_ROOT}/client_sources:${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt" \
    "${ANDROID_NDK_ROOT}"/ndk-gdb \
    --adb="${ANDROID_SDK_ROOT}"/platform-tools/adb \
    --verbose \
    --start \
    --force
