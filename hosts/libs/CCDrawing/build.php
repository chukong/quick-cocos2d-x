<?php

defined('DS') or define('DS', DIRECTORY_SEPARATOR);
define('SRC_DIR', __DIR__ . DS);
define('OUT_DIR', __DIR__ . DS);
define('TOLUA_BIN', (DS == '\\') ? 'tolua++.exe' : '/usr/local/bin/tolua++');

class Builder
{
    private $_extensionName;
    private $_luabindingFilename;
    private $_inputPath;
    private $_outputCppPath;
    private $_outputHeaderPath;
    private $_luaopenFunctionName;
    private $_fix;

    function __construct($extensionName, $luabindingFilename, $fix)
    {
        $this->_extensionName = $extensionName;
        $this->_luabindingFilename = $luabindingFilename;
        $this->_inputPath = SRC_DIR . $extensionName . '.tolua';
        $this->_outputCppPath = OUT_DIR . $luabindingFilename . '.cpp';
        $this->_outputHeaderPath = OUT_DIR . $luabindingFilename . '.h';
        $this->_luaopenFunctionName = sprintf('tolua_%s_open', $extensionName);
        $this->_fix = $fix;
    }

    function build()
    {
        $command = sprintf('%s -L basic.lua -o %s %s',
                           TOLUA_BIN, $this->_outputCppPath, $this->_inputPath);

        printf("  creating file: %s.cpp\n", $this->_luabindingFilename);
        printf("  command: %s\n", $command);
        passthru($command);

        if (file_exists($this->_outputCppPath))
        {
            $this->_fixLuabindingFile();
        }

        $includeOnce = sprintf('__%s_H_', strtoupper($this->_luabindingFilename));
        $functionName = $this->_luaopenFunctionName;
        $header = <<<EOT

#ifndef ${includeOnce}
#define ${includeOnce}

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "cocos2d.h"
#include "CCDrawing.h"

using namespace cocos2d;

TOLUA_API int ${functionName}(lua_State* tolua_S);

#endif // ${includeOnce}

EOT;
        printf("  creating file: %s.h\n", $this->_luabindingFilename);
        file_put_contents($this->_outputHeaderPath, $header);
    }

    function getLuaopenFunctionName()
    {
        return $this->_luaopenFunctionName;
    }

    private function _fixLuabindingFile()
    {
        $contents = file_get_contents($this->_outputCppPath);
        $contents = str_replace("\t", '    ', $contents);
        foreach ($this->_fix as $find => $replace)
        {
            $find = str_replace('##EXTENSION_NAME##', $this->_extensionName, $find);
            $replace = str_replace('##EXTENSION_NAME##', $this->_extensionName, $replace);

            $contents = str_replace($find, $replace, $contents);
        }

        file_put_contents($this->_outputCppPath, $contents);
    }
}

$FIX = array();

// remove unused header
$find = <<<EOT

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
EOT;
$replace = '

#include "LuaCCDrawing.h"

';
$FIX[$find] = $replace;

// remove unused functions
$find = <<<EOT
/* Exported function */
TOLUA_API int  tolua_##EXTENSION_NAME##_open (lua_State* tolua_S);
EOT;
$replace = '';
$FIX[$find] = $replace;

// fix
$find = 'unsigned void* tolua_ret = (unsigned void*)  self->getTiles();';
$replace = 'unsigned int* tolua_ret = (unsigned int*)  self->getTiles();';
$FIX[$find] = $replace;

$find = 'ccColor3B color = *((ccColor3B*)  tolua_tousertype(tolua_S,4,(void*)&(const ccColor3B)ccBLACK));';
$replace = 'const ccColor3B clr = ccBLACK;
ccColor3B color = *((ccColor3B*)  tolua_tousertype(tolua_S,4,(void*)&clr));';
$FIX[$find] = $replace;

// fix LUA_FUNCTION
$find = '*((LUA_FUNCTION*)';
$replace = '(';
$FIX[$find] = $replace;

$find = 'tolua_usertype(tolua_S,"LUA_FUNCTION");';
$replace = '';
$FIX[$find] = $replace;

// fix LUA_TABLE
$find = '*((LUA_TABLE*)';
$replace = '(';
$FIX[$find] = $replace;

$find = 'tolua_usertype(tolua_S,"LUA_TABLE");';
$replace = '';
$FIX[$find] = $replace;

$find = <<<EOT
{
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LUA_TABLE)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LUA_TABLE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LUA_TABLE));
     tolua_pushusertype(tolua_S,tolua_obj,"LUA_TABLE");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
EOT;
$replace = '';
$FIX[$find] = $replace;

$find = 'LUA_TABLE tolua_ret = (LUA_TABLE)';
$replace = '';
$FIX[$find] = $replace;

$find = <<<EOT
static int tolua_collect_LUA_TABLE (lua_State* tolua_S)
{
 LUA_TABLE* self = (LUA_TABLE*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
EOT;
$replace = '';
$FIX[$find] = $replace;

// fix push ccobject
$find = 'toluafix_pushusertype_ccobject(tolua_S,(void*)tolua_ret';
$replace = <<<EOT
int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret
EOT;
$FIX[$find] = $replace;

// fix LUA_STRING
$find = '((LUA_STRING*)';
$replace = '(';
$FIX[$find] = $replace;

$find = 'tolua_usertype(tolua_S,"LUA_STRING");';
$replace = '';
$FIX[$find] = $replace;

$find = <<<EOT
{
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((LUA_STRING)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"LUA_STRING");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LUA_STRING));
     tolua_pushusertype(tolua_S,tolua_obj,"LUA_STRING");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
EOT;
$replace = '';
$FIX[$find] = $replace;

$find = 'LUA_STRING tolua_ret = (LUA_STRING)';
$replace = '';
$FIX[$find] = $replace;

$find = <<<EOT
static int tolua_collect_LUA_STRING (lua_State* tolua_S)
{
 LUA_STRING* self = (LUA_STRING*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
EOT;
$replace = '';
$FIX[$find] = $replace;

// main
printf("\nOUT_DIR: %s\n", OUT_DIR);

$builder = new Builder('CCDrawing', 'LuaCCDrawing', $FIX);
$builder->build();
