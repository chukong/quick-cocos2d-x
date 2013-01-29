<?php

require(__DIR__ . '/build_config.inc.php');
require(__DIR__ . '/build_functions.inc.php');

define('SRC_DIR', __DIR__ . DS . 'win32' . DS);

$extensions = array(
    'crypto'     => 'cocos2dx_extension_crypto_win32',
    'native'     => 'cocos2dx_extension_native_win32',
    'network'    => 'cocos2dx_extension_network_win32',
);

runBuilder($extensions, SRC_DIR, OUT_DIR . 'win32' . DS);
