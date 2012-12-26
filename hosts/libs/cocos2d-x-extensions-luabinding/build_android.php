<?php

require(__DIR__ . '/build_config.inc.php');
require(__DIR__ . '/build_functions.inc.php');

define('SRC_DIR', __DIR__ . DS . 'android' . DS);

$extensions = array(
    'crypto'     => 'cocos2dx_extension_crypto_android',
    // 'native'     => 'cocos2dx_extension_native',
    'network'    => 'cocos2dx_extension_network_android',
    // 'store'      => 'cocos2dx_extension_store',
    // 'openfeint'  => 'cocos2dx_extension_openfeint',
    // 'gamecenter' => 'cocos2dx_extension_gamecenter',
);

runBuilder($extensions, SRC_DIR, OUT_DIR);
