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
    'destDir' => '',
    'generateType' => '',
);
while ($arg = array_shift($argv))
{
    if ($arg == '-c')
    {
        $params['configFilePath'] = array_shift($argv);
        continue;
    }
    if ($arg == '-t')
    {
        $params['generateType'] = array_shift($argv);
        continue;
    }

    if ($arg[0] == '-')
    {
        printf("\nERROR: invalid option %s\n", $arg);
        help();
        return 1;
    }

    if (empty($params['command']))
    {
        $params['command'] = $arg;
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

    require_once(__DIR__ . '/inc/MarkdownGenerator.php');
    $generator = new MarkdownGenerator($config, $modules);
    $generator->execute($params['destDir']);

    $contents = json_encode($modules);
    file_put_contents($params['destDir'] . DS . 'modules.json', $contents);
}
else if ($params['command'] == 'generate')
{
    if ($params['generateType'] != 'html' && $params['generateType'] != 'localhtml')
    {
        printf("\nERROR: invalid generate type %s\n", $params['generateType']);
        help();
        return 1;
    }

    $modules = json_decode(file_get_contents($params['srcFilesDir'] . DS . 'modules.json'), true);

    require_once(__DIR__ . '/inc/LocalHTMLGenerator.php');
    $generator = new LocalHTMLGenerator($config, $modules);
    $generator->execute($params['srcFilesDir'], $params['destDir']);
}
