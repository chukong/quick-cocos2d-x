<?php

function help()
{
    echo <<<EOT

Make luabinding from tolua++ pkg file.

Usage:
    compile_luabinding [-d output_dir] [-o output_filename] [-E KEY=VALUE] [-c config_filepath] pkg_filename

Example:
    -- create files MyClasses_luabinding.cpp, MyClasses_luabinding.h
    compile_luabinding MyClasses_luabinding.pkg

    -- create files MyClasses_binding.cpp, MyClasses_binding.h
    compile_luabinding -o MyClasses_binding MyClasses_luabinding.pkg

    -- set MACRO for tolua++
    compile_luabinding -E CCOBJECTS=MyClass,MyClass2 MyClasses_luabinding.pkg


EOT;

    exit(1);
}

if (!isset($argv))
{
    echo "\nERR: PHP \$argv not declared.\n";
    help();
}

if (count($argv) < 2)
{
    help();
}

// check command line parameters
$parameters = array();
$parameters['macros'] = array();
array_shift($argv);

while (!empty($argv))
{
    $arg = array_shift($argv);
    if ($arg == '-d')
    {
        $parameters['output_dir'] = array_shift($argv);
    }
    else if ($arg == '-o')
    {
        $parameters['output_filename'] = array_shift($argv);
    }
    else if ($arg == '-E')
    {
        array_push($parameters['macros'], array_shift($argv));
    }
    else if ($arg == '-c') 
    {
        $parameters['config_filepath'] = array_shift($argv);
    }
    else
    {
        $parameters['input_path'] = $arg;
    }
}

// check input file
if (!isset($parameters['input_path']))
{
    echo "\nERR: not set input_path.\n";
    help();
}
$input_path = realpath($parameters['input_path']);
if (!file_exists($parameters['input_path']))
{
    printf("\nERR: file \"%s\" not found.\n", $parameters['input_path']);
    help();
}
$parameters['input_path'] = $input_path;

// set output directory
$pathinfo = pathinfo($input_path);
if (!isset($parameters['output_dir']))
{
    $parameters['output_dir'] = $pathinfo['dirname'];
}
else if (!is_dir($parameters['output_dir']))
{
    printf("\nERR: invalid output dir \"%s\".\n", $parameters['output_dir']);
    help();
}

// set output filename
if (!isset($parameters['output_filename']))
{
    $parameters['output_filename'] = $pathinfo['filename'];
}

// set default config file path
if (!isset($parameters['config_filepath']))
{
    $parameters['config_filepath'] = rtrim(__DIR__, '/\\') . DIRECTORY_SEPARATOR . 'compile_luabinding_config.lua';
}

// call builder
require(__DIR__ . '/compile_luabinding_functions.php');
runBuilder($parameters);
