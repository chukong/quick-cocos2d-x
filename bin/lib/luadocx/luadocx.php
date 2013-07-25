<?php

define('LUADOCX_VERSION', '1.2');
define('DS', DIRECTORY_SEPARATOR);

function help()
{
    print <<<EOT

LuaDocX - Generate documents from Lua source files

Step 1: extract tags (module, class, function) from Lua source files.
        write all tags to markdown files, one module one file

    luadocx extract -c config_file_path source_files_dir markdown_files_dir


Step 2(a): generate online HTML docments:

    luadocx generate -t html -c config_file_path markdown_files_dir html_files_dir

Step 2(b): Generate offline HTML docments:

    luadocx generate -t localhtml -c config_file_path markdown_files_dir html_files_dir


EOT;
}

if (!isset($argc) || $argc < 4)
{
    help();
    return 1;
}

array_shift($argv);
$params = array(
    'command' => '',
    'configFilePath' => '',
    'srcFilesDir' => '',
    'destDir' => ''
);
while ($arg = array_shift($argv))
{
    if (empty($params['command']))
    {
        $params['command'] = $arg;
        continue;
    }
    if ($arg == '-c')
    {
        $params['configFilePath'] = array_shift($argv);
        continue;
    }
    if (empty($params['srcFilesDir']))
    {
        $params['srcFilesDir'] = $arg;
        continue;
    }
    if (empty($params['destDir']))
    {
        $params['destDir'] = $arg;
    }
}


// check params
$commands = array('extract', 'generate');
if (!in_array($params['command'], $commands))
{
    printf("\nERROR: invalid command %s\n", $params['command']);
    help();
    return 1;
}

if (!is_file($params['configFilePath']))
{
    printf("\nERROR: invalid config file path %s\n", $params['configFilePath']);
    help();
    return 1;
}
$params['configFilePath'] = realpath($params['configFilePath']);

if (!is_dir($params['srcFilesDir']))
{
    printf("\nERROR: invalid srcFilesDir %s\n", $params['srcFilesDir']);
    help();
    return 1;
}
$params['srcFilesDir'] = realpath($params['srcFilesDir']);

if (!is_dir($params['destDir']))
{
    @mkdir($params['destDir']);
    if (!is_dir($params['destDir']))
    {
        printf("\nERROR: invalid destDir %s\n", $params['destDir']);
        help();
        return 1;
    }
}
$params['destDir'] = realpath($params['destDir']);


// execute
require_once(__DIR__ . '/inc/Config.php');


$config = new Config($params['configFilePath']);
if (!$config->isValid())
{
    printf("\nERROR: invalid config file %s\n", $params['configFilePath']);
    help();
    return 1;
}

if ($params['command'] == 'extract')
{
    require_once(__DIR__ . '/inc/DirScanner.php');
    $scanner = new DirScanner($config, $params);
    $modules = $scanner->execute();

    require_once(__DIR__ . '/inc/APIDocumentsGenerator.php');
    $generator = new APIDocumentsGenerator($config, $modules);
    $generator->execute($params['destDir']);
}
