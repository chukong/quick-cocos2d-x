<?php

define('DS', DIRECTORY_SEPARATOR);
define('LUAJIT', true);

class LuaPackager
{
    private $quiet          = false;
    private $packageName    = '';
    private $rootdir        = '';
    private $rootdirLength  = 0;
    private $files          = array();
    private $modules        = array();
    private $excludes       = array();

    function __construct($config)
    {
        $this->quiet         = $config['quiet'];
        $this->rootdir       = realpath($config['srcdir']);
        $this->rootdirLength = strlen($this->rootdir) + 1;
        $this->packageName   = trim($config['packageName'], '.');
        $this->excludes      = $config['excludes'];
        if (!empty($this->packageName))
        {
            $this->packageName = $this->packageName . '.';
        }
    }

    function dumpZip($outputFileBasename)
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

        $zipFilename = $outputFileBasename . '.zip';
        $zip = new ZipArchive();
        if ($zip->open($zipFilename, ZIPARCHIVE::OVERWRITE | ZIPARCHIVE::CM_STORE))
        {
            if (!$this->quiet)
            {
                printf("create ZIP bundle file: %s\n", $zipFilename);
            }
            foreach ($this->modules as $module)
            {
                $zip->addFromString($module['moduleName'], $module['bytes']);
            }
            $zip->close();
            if (!$this->quiet)
            {
                printf("done.\n\n");
            }
        }

        if (!$this->quiet)
        {
            print <<<EOT


### HOW TO USE ###

1. Add code to your lua script:

    CCLuaLoadChunksFromZip("${zipFilename}")


EOT;
        }
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
                $bytesName = 'lua_m_' . strtolower(str_replace('.', '_', $moduleName));
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

    private function getFiles($dir)
    {
        $files = array();
        $dir = rtrim($dir, "/\\") . DS;
        $dh = opendir($dir);
        if ($dh == false) { return $files; }

        while (($file = readdir($dh)) !== false)
        {
            if ($file{0} == '.') { continue; }

            $path = $dir . $file;
            if (is_dir($path))
            {
                $files = array_merge($files, $this->getFiles($path));
            }
            elseif (is_file($path))
            {
                $files[] = $path;
            }
        }
        closedir($dh);
        return $files;
    }

    private function compileFile($path)
    {
        $tmpfile = $path . '.bytes';
        if (file_exists($tmpfile)) unlink($tmpfile);

        if (LUAJIT)
        {
            $command = sprintf('luajit -b -s "%s" "%s"', $path, $tmpfile);
        }
        else
        {
            $command = sprintf('luac -o "%s" "%s"', $tmpfile, $path);
        }
        passthru($command);

        if (!file_exists($tmpfile)) return false;
        $bytes = file_get_contents($tmpfile);
        unlink($tmpfile);
        return $bytes;
    }

    private function renderHeaderFile($outputFileBasename)
    {
        $headerSign = '__LUA_MODULES_' . strtoupper(md5(time())) . '_H_';
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

#if __cplusplus
}
#endif

EOT;

        $contents[] = '/*';

        foreach ($this->modules as $module)
        {
            $contents[] = sprintf('int %s(lua_State* L);', $module['functionName']);
        }

        $contents[] = '*/';

        $contents[] = <<<EOT

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
            $contents[] = sprintf('static const unsigned char %s[] = {', $module['bytesName']);
            // $contents[] = $this->encodeBytes($module['bytes']);
            $contents[] = $this->encodeBytesFast($module['bytes']);
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
    int arg = lua_gettop(L);
    luaL_loadbuffer(L,
                    (const char*)${bytesName},
                    sizeof(${bytesName}),
                    "${basename}.lua");
    lua_insert(L,1);
    lua_call(L,arg,1);
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
    for (; lib->func; lib++)
    {
        lua_getglobal(L, "package");
        lua_getfield(L, -1, "preload");
        lua_pushcfunction(L, lib->func);
        lua_setfield(L, -2, lib->name);
        lua_pop(L, 2);
    }
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
                $contents[] = $this->encodeBytesBlock($buffer);
                $buffer = array();
            }
            $offset++;
        }
        if (!empty($buffer))
        {
            $contents[] = $this->encodeBytesBlock($buffer);
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
            $output[] = sprintf('%d,', $buffer[$i]);
        }
        return implode('', $output);
    }
}


function help()
{
    echo <<<EOT
usage: php package_scripts.php [options] dirname output_filename

options:
    --bundle make bundle file
    -p prefix package name
    -x exclude packages, eg: -x framework.server, framework.tests


EOT;

}

if ($argc < 3)
{
    help();
    exit(1);
}

array_shift($argv);

$config = array(
    'packageName'        => '',
    'excludes'           => array(),
    'srcdir'             => '',
    'outputFileBasename' => '',
    'zip'                => false,
    'quiet'              => false,
);

do
{
    if ($argv[0] == '-p')
    {
        $config['packageName'] = $argv[1];
        array_shift($argv);
    }
    else if ($argv[0] == '-x')
    {
        $excludes = explode(',', $argv[1]);
        foreach ($excludes as $k => $v)
        {
            $v = trim($v);
            if (empty($v))
            {
                unset($excludes[$k]);
            }
            else
            {
                $excludes[$k] = $v;
            }
        }
        $config['excludes'] = $excludes;
        array_shift($argv);
    }
    else if ($argv[0] == '-q')
    {
        $config['quiet'] = true;
    }
    else if ($argv[0] == '-zip')
    {
        $config['zip'] = true;
    }
    else if ($config['srcdir'] == '')
    {
        $config['srcdir'] = $argv[0];
    }
    else
    {
        $config['outputFileBasename'] = $argv[0];
    }

    array_shift($argv);
} while (count($argv) > 0);

$packager = new LuaPackager($config);
if ($config['zip'])
{
    $packager->dumpZip($config['outputFileBasename']);
}
else
{
    $packager->dump($config['outputFileBasename']);
}
