<?php

require(__DIR__ . '/build_config.inc.php');
require(__DIR__ . '/build_functions.inc.php');

define('SRC_DIR', __DIR__ . DS . 'ios' . DS);

$extensions = array(
    'crypto'     => 'cocos2dx_extension_crypto_ios',
    'native'     => 'cocos2dx_extension_native_ios',
    'network'    => 'cocos2dx_extension_network_ios',
    'store'      => 'cocos2dx_extension_store_ios',
);

runBuilder($extensions, SRC_DIR, OUT_DIR . 'ios' . DS);
