<?php

defined('DS') or define('DS', DIRECTORY_SEPARATOR);
define('OUT_DIR', dirname(__DIR__) . DS . 'extra' . DS . 'luabinding' . DS);
define('TOLUA_BIN', (DS == '\\') ? 'tolua++.exe' : '/usr/local/bin/tolua++');
