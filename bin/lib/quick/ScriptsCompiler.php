<?php

require_once(__DIR__ . '/init.php');
require_once(__DIR__ . '/xxtea.php');

class ScriptsCompiler
{
    const COMPILE_ZIP = 'zip';
    const COMPILE_FILES = 'files';
    const ENCRYPT_XXTEA_ZIP = 'xxtea_zip';
    const ENCRYPT_XXTEA_CHUNK = 'xxtea_chunk';
    const ENCRYPT_XXTEA_DEFAULT_SIGN = 'XXTEA';


    private $config;
    private $options;
    private $validated = false;

    function __construct($config, $options)
    {
        $this->config = $config;
        $this->options = $options;
    }

    function validateConfig()
    {
        if (empty($this->config['src']))
        {
            printf("ERR: not specifies source files directory\n");
            return false;
        }

        if (empty($this->config['output']))
        {
            printf("ERR: not output filename or output directory\n");
            return false;
        }

        if (!empty($this->config['prefix']))
        {
            $this->config['prefix'] = $this->config['prefix'] . '.';
        }
        else
        {
            $this->config['prefix'] = '';
        }

        if (!empty($this->config['excludes']))
        {
            $excludes = explode(',', $this->config['excludes']);
            array_walk($excludes, function($value) {
                return trim($value);
            });
            $this->config['excludes'] = array_filter($excludes, function($value) {
                return !empty($value);
            });
        }
        else
        {
            $this->config['excludes'] = array();
        }

        if ($this->config['compile'] != self::COMPILE_ZIP
            && $this->config['compile'] != self::COMPILE_FILES)
        {
            printf("ERR: invalid compile mode %s\n", $this->config['compile']);
            return false;
        }

        if (!empty($this->config['encrypt'])
            && $this->config['encrypt'] != self::ENCRYPT_XXTEA_ZIP
            && $this->config['encrypt'] != self::ENCRYPT_XXTEA_CHUNK)
        {
            printf("ERR: invalid encrypt mode %s\n", $this->config['encrypt']);
            return false;
        }

        if (!empty($this->config['encrypt']) && empty($this->config['key']))
        {
            print("ERR: not set encrypt key\n");
            return false;
        }

        if ($this->config['encrypt'] == self::ENCRYPT_XXTEA_ZIP
            || $this->config['encrypt'] == self::ENCRYPT_XXTEA_CHUNK)
        {
            if (empty($this->config['sign']))
            {
                $this->config['sign'] = self::ENCRYPT_XXTEA_DEFAULT_SIGN;
            }
        }

        if (!empty($this->config['encrypt']) && empty($this->config['sign']))
        {
            print("ERR: not set encrypt sign\n");
            return false;
        }

        if (!$this->config['quiet'])
        {
            dumpConfig($this->config, $this->options);
        }

        // check src path
        $srcpath = realpath($this->config['src']);
        if (!is_dir($srcpath))
        {
            printf("ERR: invalid src dir %s\n", $srcpath);
            return false;
        }
        $this->config['srcpath'] = $srcpath;
        $this->config['srcpathLength'] = strlen($srcpath) + 1;

        if ($this->config['compile'] == self::COMPILE_ZIP)
        {
            if (is_dir($this->config['output']))
            {
                printf("ERR: output file is dir %s\n", $this->config['output']);
                return false;
            }
        }
        else if ($this->config['compile'] == self::COMPILE_FILES)
        {
            @mkdir($this->config['output'], 0777, true);
            $this->config['output'] = realpath($this->config['output']);
            if (empty($this->config['output']) || !is_dir($this->config['output']))
            {
                printf("ERR: invalid output dir %s\n", $this->config['output']);
                return false;
            }
        }

        $this->validated = true;
        return true;
    }

    function run()
    {
        if (!$this->validated)
        {
            print("ERR: invalid config\n");
            return false;
        }

        // search source files
        if (!$this->config['quiet'])
        {
            printf("Compile Lua source files in path %s\n", $this->config['srcpath']);
        }
        $files = array();
        findFiles($this->config['srcpath'], $files);

        $modules = array();
        if ($this->config['compile'] == self::COMPILE_FILES)
        {
            $tmppath = $this->config['output'];
            $tmpextname = '.lua';
        }
        else
        {
            $tmppath = $this->config['srcpath'];
            $tmpextname = '.bytes';
        }

        foreach ($files as $key => $path)
        {
            if (pathinfo($path, PATHINFO_EXTENSION) != 'lua')
            {
                unset($files[$key]);
            }
            else
            {
                $moduleName = substr(substr($path, $this->config['srcpathLength']), 0, -4);
                $tmpfile = $tmppath . DS . $moduleName . $tmpextname;
                $moduleName = str_replace(DS, '.', $moduleName);
                $modules[$path] = array(
                    'moduleName' => $moduleName,
                    'tmpfile' => $tmpfile,
                );
            }
        }
        unset($files);

        $cleanup = function($modules)
        {
            foreach ($modules as $path => $module)
            {
                if (file_exists($module['tmpfile']))
                {
                    unlink($module['tmpfile']);
                }
            }
        };

        // compile files to bytecodes
        foreach ($modules as $path => $module)
        {
            $bytes = getScriptFileBytecodes($path, $module['tmpfile']);
            if (!$bytes)
            {
                print("\n");
                $cleanup($modules);
                break;
            }
            $modules[$path]['bytes'] = $bytes;
            if (!$this->config['quiet'])
            {
                printf("  > get bytes [% 3d KB] %s\n", ceil(strlen($bytes) / 1024), $module['moduleName']);
            }
        }

        if ($this->config['compile'] == self::COMPILE_ZIP)
        {
            // create ZIP archive
            $zipfile = $this->config['output'];
            $zip = new ZipArchive();
            if ($zip->open($zipfile, ZIPARCHIVE::OVERWRITE | ZIPARCHIVE::CM_STORE))
            {
                if (!$this->config['quiet'])
                {
                    printf("create ZIP archive file: %s\n", $zipfile);
                }
                foreach ($modules as $module)
                {
                    $zip->addFromString($module['moduleName'], $module['bytes']);
                }
                $zip->close();
                if (!$this->config['quiet'])
                {
                    printf("done.\n\n");
                }
            }
        }
        else if ($this->config['compile'] == self::COMPILE_FILES)
        {
            printf("done.\n\n");
        }
        else
        {
            printf("ERR: compile mode %s not implemented\n", $this->config['compile']);
            $cleanup($modules);
            return false;
        }

        return true;
    }

    function dump($outputFileBasename)
    {
        $this->files = array();
        $this->modules = array();

        if (!$this->quiet)
        {
            print("compile script files\n");
        }
        $this->compile();
        if (empty($this->files))
        {
            printf("error.\nERROR: not found script files in %s\n", $this->rootdir);
            return;
        }

        $headerFilename = $outputFileBasename . '.h';
        if (!$this->quiet)
        {
            printf("create C header file: %s\n", $headerFilename);
        }
        file_put_contents($headerFilename, $this->renderHeaderFile($outputFileBasename));

        $sourceFilename = $outputFileBasename . '.c';
        if (!$this->quiet)
        {
            printf("create C source file: %s\n", $sourceFilename);
        }
        file_put_contents($sourceFilename, $this->renderSourceFile($outputFileBasename));

        if (!$this->quiet)
        {
            printf("done.\n\n");
        }

        $outputFileBasename = basename($outputFileBasename);

        if (!$this->quiet)
        {
            print <<<EOT


### HOW TO USE ###

1. Add code to AppDelegate.cpp:

    extern "C" {
    #include "${outputFileBasename}.h"
    }

2. Add code to AppDelegate::applicationDidFinishLaunching()

    CCScriptEngineProtocol* pEngine = CCScriptEngineManager::sharedManager()->getScriptEngine();
    luaopen_${outputFileBasename}(pEngine->getLuaState());

    pEngine->executeString("require(\"main\")");


EOT;
        }

    }

    private function compile()
    {
        if (file_exists($this->rootdir) && is_dir($this->rootdir))
        {
            $this->files = $this->getFiles($this->rootdir);
        }

        foreach ($this->files as $path)
        {
            $filename = substr($path, $this->rootdirLength);
            $fi = pathinfo($filename);
            if ($fi['extension'] != 'lua') continue;

            $basename = ltrim($fi['dirname'] . DS . $fi['filename'], '/\\.');
            $moduleName = $this->packageName . str_replace(DS, '.', $basename);
            $found = false;
            foreach ($this->excludes as $k => $v)
            {
                if (substr($moduleName, 0, strlen($v)) == $v)
                {
                    $found = true;
                    break;
                }
            }
            if ($found) continue;

            if (!$this->quiet)
            {
                printf('  compile module: %s...', $moduleName);
            }
            $bytes = $this->compileFile($path);
            if ($bytes == false)
            {
                print("error.\n");
            }
            else
            {
                if (!$this->quiet)
                {
                    print("ok.\n");
                }
                $bytesName = 'lua_m_' . strtolower(str_replace(array('.', '-'), '_', $moduleName));
                $this->modules[] = array(
                    'moduleName'    => $moduleName,
                    'bytesName'     => $bytesName,
                    'functionName'  => 'luaopen_' . $bytesName,
                    'basename'      => $basename,
                    'bytes'         => $bytes,
                );
            }
        }
    }


    private function renderHeaderFile($outputFileBasename)
    {
        $headerSign = '__LUA_MODULES_' . strtoupper(md5($outputFileBasename . time())) . '_H_';
        $outputFileBasename = basename($outputFileBasename);

        $contents = array();
        $contents[] = <<<EOT

/* ${outputFileBasename}.h */

#ifndef ${headerSign}
#define ${headerSign}

#if __cplusplus
extern "C" {
#endif

#include "lua.h"

void luaopen_${outputFileBasename}(lua_State* L);

EOT;

        if (!$this->exportModuleFuntion)
        {
            $contents[] = '/*';
        }

        foreach ($this->modules as $module)
        {
            $contents[] = sprintf('int %s(lua_State* L);', $module['functionName']);
        }

        if (!$this->exportModuleFuntion)
        {
            $contents[] = '*/';
        }

        $contents[] = <<<EOT

#if __cplusplus
}
#endif

#endif /* ${headerSign} */

EOT;

        return implode("\n", $contents);
    }

    private function renderSourceFile($outputFileBasename)
    {
        $outputFileBasename = basename($outputFileBasename);

        $contents = array();
        $contents[] = <<<EOT

/* ${outputFileBasename}.c */

#include "lua.h"
#include "lauxlib.h"
#include "${outputFileBasename}.h"

EOT;

        foreach ($this->modules as $module)
        {
            $contents[] = sprintf('/* %s, %s.lua */', $module['moduleName'], $module['basename']);
            $contents[] = sprintf('static const char %s[] = {', $module['bytesName']);
            $contents[] = $this->encodeBytes($module['bytes']);
            // $contents[] = $this->encodeBytesFast($module['bytes']);
            $contents[] = '};';
            $contents[] = '';
        }

        $contents[] = '';

        foreach ($this->modules as $module)
        {
            $functionName = $module['functionName'];
            $bytesName    = $module['bytesName'];
            $basename     = $module['basename'];

            $contents[] = <<<EOT

int ${functionName}(lua_State *L) {
    luaL_loadbuffer(L,
                    (const char*)${bytesName},
                    sizeof(${bytesName}),
                    "${basename}");
    return 1;
}

EOT;
        }

        $contents[] = '';

        $contents[] = "static luaL_Reg ${outputFileBasename}_modules[] = {";

        foreach ($this->modules as $module)
        {
            $contents[] = sprintf('    {"%s", %s},',
                                  $module["moduleName"],
                                  $module["functionName"]);
        }

        $contents[] = <<<EOT
    {NULL, NULL}
};

void luaopen_${outputFileBasename}(lua_State* L)
{
    luaL_Reg* lib = ${outputFileBasename}_modules;
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    for (; lib->func; lib++)
    {
        lib->func(L);
        lua_setfield(L, -2, lib->name);
    }
    lua_pop(L, 2);
}

EOT;

        return implode("\n", $contents);
    }

    private function encodeBytes($bytes)
    {
        $len      = strlen($bytes);
        $contents = array();
        $offset   = 0;
        $buffer   = array();

        while ($offset < $len)
        {
            $buffer[] = ord(substr($bytes, $offset, 1));
            if (count($buffer) == 16)
            {
                $contents[] = '    ' . $this->encodeBytesBlock($buffer);
                $buffer = array();
            }
            $offset++;
        }
        if (!empty($buffer))
        {
            $contents[] = '    ' . $this->encodeBytesBlock($buffer);
        }

        return implode("\n", $contents);
    }

    private function encodeBytesFast($bytes)
    {
        $len = strlen($bytes);
        $output = array();
        for ($i = 0; $i < $len; $i++)
        {
            $output[] = sprintf('%d,', ord($bytes{$i}));
        }
        return implode('', $output);
    }

    private function encodeBytesBlock($buffer)
    {
        $output = array();
        $len = count($buffer);
        for ($i = 0; $i < $len; $i++)
        {
            $output[] = sprintf('0x%02x,', $buffer[$i]);
        }
        return implode('', $output);
    }
}
