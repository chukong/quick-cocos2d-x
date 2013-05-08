<?php

define('DS', DIRECTORY_SEPARATOR);

class ProjectCreator
{
    private $templatePath;
    private $packageName;
    private $packageFullName;
    private $packageLastName;
    private $projectName;
    private $projectPath;
    private $orientation;

    private $ready = false;

    function __construct(array $config)
    {
        $force = $config['force'];

        // check template
        $templatePath = rtrim($config['templatePath'], "/\\") . DS;
        if (!is_dir($templatePath))
        {
            printf("ERROR: invalid template path \"%s\"\n", $templatePath);
            return;
        }
        if (!file_exists($templatePath . 'TEMPLATE_INFO.json'))
        {
            printf("ERROR: not found TEMPLATE_INFO.json in template path \"%s\"\n", $templatePath);
            return;
        }
        $info = file_get_contents($templatePath . 'TEMPLATE_INFO.json');
        $info = json_decode($info, true);
        if (!is_array($info) || empty($info['name']))
        {
            printf("ERROR: invalid TEMPLATE_INFO.json in template path \"%s\"\n", $templatePath);
            return;
        }

        $this->templatePath = $templatePath;

        // check projectName
        $projectName = preg_replace('/[^a-z0-9_]/i', '', $config['projectName']);
        if (empty($projectName))
        {
            printf("ERROR: invalid project name \"%s\"\n", $projectName);
            return;
        }

        $this->projectName = $projectName;
        $this->projectPath = rtrim(getcwd(), '/\\') . DS . $projectName;

        if (!$force && (is_dir($this->projectPath) || file_exists($this->projectPath)))
        {
            printf("ERROR: project path \"%s\" exists\n", $this->projectPath);
            return;
        }

        // check packageName
        $packageName = str_replace('-', '_', strtolower($config['packageName']));
        $parts = explode('.', $packageName);
        $packageName = array();
        for ($i = 0; $i < count($parts); $i++)
        {
            $parts[$i] = preg_replace('/[^a-z0-9_]/', '', $parts[$i]);
            if (!empty($parts[$i])) $packageName[] = $parts[$i];
        }
        if (empty($packageName))
        {
            printf("ERROR: invalid package name \"%s\"\n", $packageName);
            return;
        }

        $lastname = $packageName[count($packageName) - 1];
        if ($lastname == strtolower($this->projectName))
        {
            array_pop($packageName);
        }
        $packageName = implode('.', $packageName);
        $this->packageName = $packageName;
        $this->packageLastName = strtolower($this->projectName);
        $this->packageFullName = $packageName . '.' . $this->packageLastName;

        // check more options
        $orientation = strtolower($config['orientation']);
        if ($orientation != 'landscape' && $orientation != 'portrait')
        {
            printf("ERROR: invalid screen orientation \"%s\"\n", $orientation);
            return;
        }
        $this->orientation = $orientation;

        $this->ready = true;
    }

    function run()
    {
        if (!$this->ready) return false;

        echo <<<EOT

template            : {$this->templatePath}

project name        : {$this->projectName}
package name        : {$this->packageName}
package full name   : {$this->packageFullName}
project path        : {$this->projectPath}
screen orientation  : {$this->orientation}


EOT;

        // create project dir
        if (!is_dir($this->projectPath)) mkdir($this->projectPath);
        if (!is_dir($this->projectPath))
        {
            printf("ERROR: create project dir \"%s\" failure\n", $this->projectPath);
            return;
        }

        // copy files
        $files = $this->getFiles($this->templatePath);
        foreach ($files as $filename)
        {
            print(substr($filename, strlen($this->templatePath)) . "\n");
        }



        return true;
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

}


// ----------------------------------------

function help()
{
    echo <<<EOT

usage: php create_project.php [options] -t template_path -p package_name project_name

options:
    -f force copy files to project dir
    -o screen orientation, eg: -o landscape . default is portrait
    -t template path, eg: -t /quick-cocos2d-x/template/PROJECT_TEMPLATE_01
    -p package name, eg: -p com.quickx.games


EOT;

}

if ($argc < 4)
{
    help();
    exit(1);
}

array_shift($argv);

$config = array(
    'orientation'   => 'portrait',
    'force'         => false,
    'templatePath'  => '',
    'packageName'   => '',
    'projectName'   => '',
);

do
{
    if ($argv[0] == '-p')
    {
        $config['packageName'] = $argv[1];
        array_shift($argv);
    }
    else if ($argv[0] == '-t')
    {
        $config['templatePath'] = $argv[1];
        array_shift($argv);
    }
    else if ($argv[0] == '-o')
    {
        $config['orientation'] = $argv[1];
        array_shift($argv);
    }
    else if ($argv[0] == '-f')
    {
        $config['force'] = true;
    }
    else if ($config['projectName'] == '')
    {
        $config['projectName'] = $argv[0];
    }

    array_shift($argv);
} while (count($argv) > 0);

$creator = new ProjectCreator($config);
if (!$creator->run())
{
    help();
}
