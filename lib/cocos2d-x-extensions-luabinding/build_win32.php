<?php

require(__DIR__ . '/build/build_functions.inc.php');

define('SRC_DIR', __DIR__ . DS . 'win32' . DS);
define('OUT_DIR', __DIR__ . DS . 'win32' . DS);

$extensions = array(
    'cocos2dx_extensions_luabinding_win32' => 'cocos2dx_extensions_luabinding_win32',
);

runBuilder($extensions, SRC_DIR, OUT_DIR);
