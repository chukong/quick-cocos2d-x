<?php

defined('DS') or define('DS', DIRECTORY_SEPARATOR);
define('BIN_DIR', rtrim(dirname(__DIR__), '/\\'));
define('TOLUA_BIN', (DS == '\\') ?  BIN_DIR . '\\win32\\tolua++.exe' : BIN_DIR . '/mac/tolua++');
define('CONFIG_PATH', rtrim(__DIR__, '/\\') . DS . 'compile_luabinding_config.lua');

// ----------------------------------------
// rules

function getRules()
{
    $rules = array();

    // remove unused header
    $find = <<<EOT
#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"
EOT;
    $replace = <<<EOT
#include "##LUABINDING_FILENAME##.h"
#include "CCLuaEngine.h"

using namespace cocos2d;

EOT;
    $rules[$find] = $replace;

    // remove unused functions
    $find = <<<EOT
/* Exported function */
TOLUA_API int  tolua_##LUABINDING_FILENAME##_open (lua_State* tolua_S);
EOT;
    $replace = '';
    $rules[$find] = $replace;

    // fix LUA_FUNCTION
    $find = '*((LUA_FUNCTION*)';
    $replace = '(';
    $rules[$find] = $replace;

    $find = 'tolua_usertype(tolua_S,"LUA_FUNCTION");';
    $replace = '';
    $rules[$find] = $replace;

    // fix LUA_TABLE
    $find = '*((LUA_TABLE*)';
    $replace = '(';
    $rules[$find] = $replace;

    $find = 'tolua_usertype(tolua_S,"LUA_TABLE");';
    $replace = '';
    $rules[$find] = $replace;

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
    $rules[$find] = $replace;

    $find = 'LUA_TABLE tolua_ret = (LUA_TABLE)';
    $replace = '';
    $rules[$find] = $replace;

    $find = <<<EOT
static int tolua_collect_LUA_TABLE (lua_State* tolua_S)
{
 LUA_TABLE* self = (LUA_TABLE*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
EOT;
    $replace = '';
    $rules[$find] = $replace;

    // fix push ccobject
    $find = 'toluafix_pushusertype_ccobject(tolua_S,(void*)tolua_ret';
    $replace = <<<EOT
int nID = (tolua_ret) ? tolua_ret->m_uID : -1;
int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret
EOT;
    $rules[$find] = $replace;

    // fix LUA_STRING
    $find = '((LUA_STRING*)';
    $replace = '(';
    $rules[$find] = $replace;

    $find = 'tolua_usertype(tolua_S,"LUA_STRING");';
    $replace = '';
    $rules[$find] = $replace;

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
    $rules[$find] = $replace;

    $find = 'LUA_STRING tolua_ret = (LUA_STRING)';
    $replace = '';
    $rules[$find] = $replace;

    $find = <<<EOT
static int tolua_collect_LUA_STRING (lua_State* tolua_S)
{
 LUA_STRING* self = (LUA_STRING*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
EOT;
    $replace = '';
    $rules[$find] = $replace;

    return $rules;
}


// ----------------------------------------
// Builder class

class Builder
{
    private $rules_;
    private $inputPath_;
    private $outputDir_;
    private $outputFilename_;
    private $outputSourcePath_;
    private $outputHeaderPath_;
    private $macros_;
    private $luaopenFunctionName_;
    private $password_;

    function __construct($parameters)
    {
        $this->rules_               = getRules();
        $this->inputPath_           = $parameters['input_path'];
        $this->outputDir_           = rtrim($parameters['output_dir'], '/\\') . DS;
        $this->outputFilename_      = $parameters['output_filename'];
        $this->outputSourcePath_    = $this->outputDir_ . $this->outputFilename_ . '.cpp';
        $this->outputHeaderPath_    = $this->outputDir_ . $this->outputFilename_ . '.h';
        $this->macros_              = $parameters['macros'];
        $this->luaopenFunctionName_ = str_replace('-', '_', sprintf('luaopen_%s', $parameters['output_filename']));
    }

    function build()
    {
        $macros = array();
        if (is_array($this->macros_))
        {
            for ($i = 0; $i < count($this->macros_); $i++)
            {
                $macros[$i] = '-E ' . $this->macros_[$i];
            }
        }
        $macros = implode(' ', $macros);

        chdir(dirname($this->inputPath_));
        $inputFilename = pathinfo($this->inputPath_, PATHINFO_BASENAME);
        $command = sprintf('"%s" %s -L "%s" -o "%s" "%s"', TOLUA_BIN, $macros, CONFIG_PATH, $this->outputSourcePath_, $inputFilename);
        printf("\ncommand: %s\n\n", $command);

        printf("creating file: %s\n\n", $this->outputSourcePath_);
        passthru($command);

        if (!file_exists($this->outputSourcePath_))
        {
            return false;
        }

        $this->fixLuabindingFile();

        $includeOnce = sprintf('__%s_H_', strtoupper(str_replace('-', '_', $this->outputFilename_)));
        $functionName = $this->luaopenFunctionName_;
        $contents = <<<EOT

#ifndef ${includeOnce}
#define ${includeOnce}

extern "C" {
#include "lua.h"
#include "tolua++.h"
#include "tolua_fix.h"
}

TOLUA_API int ${functionName}(lua_State* tolua_S);

#endif // ${includeOnce}

EOT;
        printf("creating file: %s\n\n", $this->outputHeaderPath_);
        file_put_contents($this->outputHeaderPath_, $contents);

        echo "----------------------------------------\n\n";

        return true;
    }

    function getOutputFilename()
    {
        return $this->outputFilename_;
    }

    function getLuaopenFunctionName()
    {
        return $this->luaopenFunctionName_;
    }

    private function fixLuabindingFile()
    {
        $contents = file_get_contents($this->outputSourcePath_);
        $contents = str_replace("\r", '', $contents);
        $contents = str_replace("\t", '    ', $contents);
        $contents = str_replace($this->outputFilename_, str_replace('-', '_', $this->outputFilename_), $contents);

        foreach ($this->rules_ as $find => $replace)
        {
            $find = str_replace('##LUABINDING_FILENAME##', $this->outputFilename_, $find);
            $replace = str_replace('##LUABINDING_FILENAME##', $this->outputFilename_, $replace);
            $contents = str_replace($find, $replace, $contents);
        }

        file_put_contents($this->outputSourcePath_, $contents);
    }
}

function encrypt($str, $key)
{
    if ($str == "") {
        return "";
    }
    $v = str2long($str, true);
    $k = str2long($key, false);
    $n = count($v) - 1;

    $z = $v[$n];
    $y = $v[0];
    $delta = 0x9E3779B9;
    $q = floor(6 + 52 / ($n + 1));
    $sum = 0;
    while (0 < $q--) {
        $sum = int32($sum + $delta);
        $e = $sum >> 2 & 3;
        for ($p = 0; $p < $n; $p++) {
            $y = $v[$p + 1];
            $mx = int32((($z >> 5 & 0x07ffffff) ^ $y << 2) + (($y >> 3 & 0x1fffffff) ^ $z << 4)) ^ int32(($sum ^ $y) + ($k[$p & 3 ^ $e] ^ $z));
            $z = $v[$p] = int32($v[$p] + $mx);
        }
        $y = $v[0];
        $mx = int32((($z >> 5 & 0x07ffffff) ^ $y << 2) + (($y >> 3 & 0x1fffffff) ^ $z << 4)) ^ int32(($sum ^ $y) + ($k[$p & 3 ^ $e] ^ $z));
        $z = $v[$n] = int32($v[$n] + $mx);
    }
    return long2str($v, false);
}

function decrypt($str, $key)
{
    if ($str == "") {
        return "";
    }
    $v = str2long($str, false);
    $k = str2long($key, false);
    $n = count($v) - 1;

    $z = $v[$n];
    $y = $v[0];
    $delta = 0x9E3779B9;
    $q = floor(6 + 52 / ($n + 1));
    $sum = int32($q * $delta);
    while ($sum != 0) {
        $e = $sum >> 2 & 3;
        for ($p = $n; $p > 0; $p--) {
            $z = $v[$p - 1];
            $mx = int32((($z >> 5 & 0x07ffffff) ^ $y << 2) + (($y >> 3 & 0x1fffffff) ^ $z << 4)) ^ int32(($sum ^ $y) + ($k[$p & 3 ^ $e] ^ $z));
            $y = $v[$p] = int32($v[$p] - $mx);
        }
        $z = $v[$n];
        $mx = int32((($z >> 5 & 0x07ffffff) ^ $y << 2) + (($y >> 3 & 0x1fffffff) ^ $z << 4)) ^ int32(($sum ^ $y) + ($k[$p & 3 ^ $e] ^ $z));
        $y = $v[0] = int32($v[0] - $mx);
        $sum = int32($sum - $delta);
    }
    return long2str($v, true);
}

function long2str($v, $w) {
    $len = count($v);
    $s = array();
    for ($i = 0; $i < $len; $i++)
    {
        $s[$i] = pack("V", $v[$i]);
    }
    if ($w) {
        return substr(join('', $s), 0, $v[$len - 1]);
    }
    else {
        return join('', $s);
    }
}

function str2long($s, $w) {
    $v = unpack("V*", $s . str_repeat("\0", (4 - strlen($s) % 4) & 3));
    $v = array_values($v);
    if ($w) {
        $v[count($v)] = strlen($s);
    }
    return $v;
}

function int32($n) {
    while ($n >= 2147483648) $n -= 4294967296;
    while ($n <= -2147483649) $n += 4294967296;
    return (int)$n;
}

// ----------------------------------------
// bootstrap

function runBuilder($params)
{
    $builder = new Builder($params);
    if ($builder->build())
    {
        $contents = array();
        $contents[] = '';
        $contents[] = '// add to AppDelegate.cpp';
        $contents[] = sprintf('#include "%s"', $builder->getOutputFilename() . '.h');
        $contents[] = '';
        $contents[] = '// add to AppDelegate::applicationDidFinishLaunching()';
        $contents[] = 'CCLuaStack* stack = CCScriptEngineManager::sharedManager()->getScriptEngine()->getLuaStack();';
        $contents[] = 'lua_State* L = stack->getLuaState();';
        $contents[] = sprintf('%s(L);', $builder->getLuaopenFunctionName());
        $contents[] = '';

        print(implode("\n", $contents));
    }
}
