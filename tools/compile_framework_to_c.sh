#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR/../"
php "$DIR/package_lua_scripts.php" -x framework.server -p framework framework hosts/libs/framework/framework_lua
