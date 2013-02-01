<?php

require(__DIR__ . '/build_config.inc.php');
require(__DIR__ . '/build_functions.inc.php');

define('SRC_DIR', __DIR__ . DS . 'android' . DS);

$extensions = array(
    'crypto'     => 'cocos2dx_extension_crypto_android',
    'network'    => 'cocos2dx_extension_network_android',
);

runBuilder($extensions, SRC_DIR, OUT_DIR . 'android' . DS);
