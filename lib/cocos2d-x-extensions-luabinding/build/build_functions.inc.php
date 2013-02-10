<?php

defined('DS') or define('DS', DIRECTORY_SEPARATOR);
define('TOLUA_BIN', (DS == '\\') ? 'tolua++.exe' : '/usr/local/bin/tolua++');
define('CONFIG_PATH', rtrim(__DIR__, '/\\') . DS . 'build_tolua_config.lua');

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
    $replace = '#include "##LUABINDING_FILENAME##.h"';
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
    private $luabindingFilename_;
    private $inputPath_;
    private $outputCppPath_;
    private $outputHeaderPath_;
    private $luaopenFunctionName_;
    private $rules_;

    function __construct($srcDir, $outDir, $luabindingFilename, $rules)
    {
        $this->luabindingFilename_  = $luabindingFilename;
        $this->inputPath_           = $srcDir . $luabindingFilename . '.tolua';
        $this->outputCppPath_       = $outDir . $luabindingFilename . '.cpp';
        $this->outputHeaderPath_    = $outDir . $luabindingFilename . '.h';
        $this->luaopenFunctionName_ = sprintf('tolua_%s_open', $luabindingFilename);
        $this->rules_               = $rules;
    }

    function build()
    {
        $command = sprintf('"%s" -L "%s" -o "%s" "%s"',
                           TOLUA_BIN, CONFIG_PATH, $this->outputCppPath_, $this->inputPath_);

        printf("  creating file: %s.cpp\n", $this->luabindingFilename_);
        passthru($command);

        if (file_exists($this->outputCppPath_))
        {
            $this->rules_LuabindingFile();
        }

        $includeOnce = sprintf('__%s_H_', strtoupper($this->luabindingFilename_));
        $functionName = $this->luaopenFunctionName_;
        $header = <<<EOT

#ifndef ${includeOnce}
#define ${includeOnce}

extern "C" {
#include "tolua++.h"
#include "tolua_fix.h"
}
#include "cocos2d.h"
#include "CCLuaEngine.h"

using namespace cocos2d;

TOLUA_API int ${functionName}(lua_State* tolua_S);

#endif // ${includeOnce}

EOT;
        printf("  creating file: %s.h\n", $this->luabindingFilename_);
        file_put_contents($this->outputHeaderPath_, $header);
    }

    function getLuaopenFunctionName()
    {
        return $this->luaopenFunctionName_;
    }

    private function rules_LuabindingFile()
    {
        $contents = file_get_contents($this->outputCppPath_);
        $contents = str_replace("\t", '    ', $contents);
        foreach ($this->rules_ as $find => $replace)
        {
            $find = str_replace('##LUABINDING_FILENAME##', $this->luabindingFilename_, $find);
            $replace = str_replace('##LUABINDING_FILENAME##', $this->luabindingFilename_, $replace);

            $contents = str_replace($find, $replace, $contents);
        }

        file_put_contents($this->outputCppPath_, $contents);
    }
}


// ----------------------------------------
// bootstrap

function runBuilder($extensions, $srcDir, $outDir)
{
    printf("\nOUT_DIR: %s\n", $outDir);

    $contents = array();
    $contents[] = '';
    $contents[] = '// cocos2dx-extensions';

    $functions = array();

    foreach ($extensions as $extensionName => $luabindingFilename)
    {
        $builder = new Builder($srcDir, $outDir, $luabindingFilename, getRules());
        $builder->build();

        $contents[] = sprintf('#include "%s"', $luabindingFilename . '.h');
        $functions[] = $builder->getLuaopenFunctionName();
    }

    $contents[] = '';
    $contents[] = '';
    $contents[] = '// cocos2dx-extensions';
    $contents[] = 'lua_State* L = CCScriptEngineManager::sharedManager()->getScriptEngine()->getLuaState();';

    foreach ($functions as $functionName)
    {
        $contents[] = sprintf('%s(L);', $functionName);
    }

    $contents[] = '';
    $contents[] = '';

    print("\n---------------------\n");
    print(implode("\n", $contents));
}

