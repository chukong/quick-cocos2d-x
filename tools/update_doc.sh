#!/bin/sh
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR/../"
php ../luadocx/luadocx.php -t "quick-cocos2d-x API Documents" -r framework -i framework.init -x framework.client.cocos2dx,framework.server.resty,framework.shared.json framework/ ../quick-cocos2d-x-pages/docs/framework/

