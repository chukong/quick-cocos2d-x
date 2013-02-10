<?php

defined('DS') or define('DS', DIRECTORY_SEPARATOR);
define('TOLUA_BIN', (DS == '\\') ? 'tolua++.exe' : '/usr/local/bin/tolua++');
define('CONFIG_PATH', rtrim(__DIR__, '/\\') . DS . 'make_luabinding_config.lua');

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

        $command = sprintf('"%s" %s -L "%s" -o "%s" "%s"', TOLUA_BIN, $macros, CONFIG_PATH, $this->outputSourcePath_, $this->inputPath_);
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
        $contents[] = sprintf('#include "%s"', $luabindingFilename . '.h');
        $contents[] = '';
        $contents[] = '// add to AppDelegate::applicationDidFinishLaunching()';
        $contents[] = 'CCLuaStack* stack = CCScriptEngineManager::sharedManager()->getScriptEngine()->getLuaStack();';
        $contents[] = 'lua_State* L = stack->getLuaState();';
        $contents[] = sprintf('%s(L);', $builder->getLuaopenFunctionName());
        $contents[] = '';

        print(implode("\n", $contents));
    }
}
