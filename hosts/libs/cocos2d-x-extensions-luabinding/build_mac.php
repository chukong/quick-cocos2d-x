<?php

require(__DIR__ . '/build/build_functions.inc.php');

define('SRC_DIR', __DIR__ . DS . 'mac' . DS);
define('OUT_DIR', __DIR__ . DS . 'mac' . DS);

$extensions = array(
    'cocos2dx_extensions_luabinding_mac' => 'cocos2dx_extensions_luabinding_mac',
);

runBuilder($extensions, SRC_DIR, OUT_DIR);
