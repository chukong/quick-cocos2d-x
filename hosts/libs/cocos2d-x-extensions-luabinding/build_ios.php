<?php

require(__DIR__ . '/build/build_functions.inc.php');

define('SRC_DIR', __DIR__ . DS . 'ios' . DS);
define('OUT_DIR', __DIR__ . DS . 'ios' . DS);

$extensions = array(
    'cocos2dx_extensions_luabinding_ios' => 'cocos2dx_extensions_luabinding_ios',
);

runBuilder($extensions, SRC_DIR, OUT_DIR);
