<?php

require(__DIR__ . '/build_config.inc.php');
require(__DIR__ . '/build_functions.inc.php');

define('SRC_DIR', __DIR__ . DS . 'mac' . DS);

$extensions = array(
    'crypto'     => 'cocos2dx_extension_crypto_mac',
    'native'     => 'cocos2dx_extension_native_mac',
    'network'    => 'cocos2dx_extension_network_mac',
);

runBuilder($extensions, SRC_DIR, OUT_DIR . 'mac' . DS);
