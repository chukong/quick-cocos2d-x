<?php

class Builder
{
    private $_luabindingFilename;
    private $_inputPath;
    private $_outputCppPath;
    private $_outputHeaderPath;
    private $_luaopenFunctionName;
    private $_fix;

    function __construct($srcDir, $outDir, $luabindingFilename, $fix)
    {
        $this->_luabindingFilename = $luabindingFilename;
        $this->_inputPath = $srcDir . $luabindingFilename . '.tolua';
        $this->_outputCppPath = $outDir . $luabindingFilename . '.cpp';
        $this->_outputHeaderPath = $outDir . $luabindingFilename . '.h';
        $this->_luaopenFunctionName = sprintf('tolua_%s_open', $luabindingFilename);
        $this->_fix = $fix;
    }

    function build()
    {
        $command = sprintf('%s -L build_tolua_config.lua -o %s %s',
                           TOLUA_BIN, $this->_outputCppPath, $this->_inputPath);

        printf("  creating file: %s.cpp\n", $this->_luabindingFilename);
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
            $find = str_replace('##LUABINDING_FILENAME##', $this->_luabindingFilename, $find);
            $replace = str_replace('##LUABINDING_FILENAME##', $this->_luabindingFilename, $replace);

            $contents = str_replace($find, $replace, $contents);
        }

        file_put_contents($this->_outputCppPath, $contents);
    }
}

function runBuilder($extensions, $srcDir, $outDir)
{
    $fix = require(__DIR__ . '/build_rules.inc.php');
    printf("\nOUT_DIR: %s\n", $outDir);

    $contents = array();
    $contents[] = '';
    $contents[] = '// cocos2dx-extensions';

    $functions = array();

    foreach ($extensions as $extensionName => $luabindingFilename)
    {
        $builder = new Builder($srcDir, $outDir, $luabindingFilename, $fix);
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
