<?php

define('LUADOCX_VERSION', '1.1');
define('DS', DIRECTORY_SEPARATOR);

function help()
{
    print <<<EOT

Usage: luadocx [-t title] [-r root] [-i index] [-x exclude] source_files_dir output_dir

Parameters:
    -t title of the documents
    -r root module name
    -i index module name
    -x excludes

Examples:

    luadocx -t "My App Docuemtns" -r MyApp -i MyApp.main MyApp/ docs/

    luadocx -r MyApp -x "MyApp.tests,MyApp.data" MyApp/ docs/



EOT;
}

if (!isset($argc) || $argc < 3)
{
    help();
    return 1;
}

array_shift($argv);
$params = array();
while ($arg = array_shift($argv))
{
    if ($arg == '-t')
    {
        $params['title'] = array_shift($argv);
        continue;
    }

    if ($arg == '-r')
    {
        $params['rootModuleName'] = array_shift($argv);
        continue;
    }

    if ($arg == '-i')
    {
        $params['indexModuleName'] = array_shift($argv);
        continue;
    }

    if ($arg == '-x')
    {
        $params['excludes'] = array_shift($argv);
        continue;
    }

    if (empty($params['sourceFilesDir']))
    {
        $params['sourceFilesDir'] = $arg;
        continue;
    }

    if (empty($params['outputDir']))
    {
        $params['outputDir'] = $arg;
    }
}

if (!is_dir($params['sourceFilesDir']))
{
    print("\nERROR: Invalid source files dir: " . $params['sourceFilesDir'] . "\n");
    help();
    return 1;
}
$params['sourceFilesDir'] = realpath($params['sourceFilesDir']);

if (!is_dir($params['outputDir']))
{
    @mkdir($params['outputDir']);
    if (!is_dir($params['outputDir']))
    {
        print("\nERROR: Invalid output dir: " . $params['outputDir'] . "\n");
        help();
        return 1;
    }
}
$params['outputDir'] = realpath($params['outputDir']);

require(__DIR__ . '/inc/luadocxDirScanner.php');

$scanner = new DirScanner($params);
if (!$scanner->execute())
{
    help();
    return 1;
}
