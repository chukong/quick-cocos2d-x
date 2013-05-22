<?php

define('DS', DIRECTORY_SEPARATOR);

class ProjectCreator
{
    private $templatePath;
    private $packageName;
    private $packageFullName;
    private $packageLastName;
    private $projectPath;
    private $orientation;
    private $noproj;

    private $vars = array();

    private $ready = false;

    function __construct(array $config)
    {
        $force = $config['force'];
        $this->noproj = $config['noproj'];

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

        // check packageName
        $packageName = str_replace('-', '_', strtolower($config['packageName']));
        $parts = explode('.', $packageName);
        $packageName = array();
        for ($i = 0; $i < count($parts); $i++)
        {
            $parts[$i] = preg_replace('/[^a-z0-9_]/', '', $parts[$i]);
            if (!empty($parts[$i])) $packageName[] = $parts[$i];
        }
        if (count($packageName) < 2)
        {
            printf("ERROR: invalid package name \"%s\"\n", implode('.', $packageName));
            return;
        }

        $lastname = $packageName[count($packageName) - 1];
        array_pop($packageName);
        $packageName = implode('.', $packageName);
        $this->packageName = $packageName;
        $this->packageLastName = $lastname;
        $this->packageFullName = $packageName . '.' . $lastname;

        // check projectName
        $this->projectPath = rtrim(getcwd(), '/\\') . DS . $lastname . DS;

        if (!$force && (is_dir($this->projectPath) || file_exists($this->projectPath)))
        {
            printf("ERROR: project path \"%s\" exists\n", $this->projectPath);
            return;
        }

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

package name        : {$this->packageFullName}
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

        // prepare contents
        $this->vars['__TEMPLATE_PATH__'] = $this->templatePath;
        $this->vars['__PROJECT_PACKAGE_NAME__'] = $this->packageName;
        $this->vars['__PROJECT_PACKAGE_NAME_L__'] = strtolower($this->packageName);
        $this->vars['__PROJECT_PACKAGE_FULL_NAME__'] = $this->packageFullName;
        $this->vars['__PROJECT_PACKAGE_FULL_NAME_L__'] = strtolower($this->packageFullName);
        $this->vars['__PROJECT_PACKAGE_LAST_NAME__'] = $this->packageLastName;
        $this->vars['__PROJECT_PACKAGE_LAST_NAME_L__'] = strtolower($this->packageLastName);
        $this->vars['__PROJECT_PACKAGE_LAST_NAME_UF__'] = ucfirst(strtolower($this->packageLastName));
        $this->vars['__PROJECT_PATH__'] = $this->projectPath;
        $this->vars['__SCREEN_ORIENTATION__'] = $this->orientation;
        $this->vars['__SCREEN_ORIENTATION_L__'] = strtolower($this->orientation);
        $this->vars['__SCREEN_ORIENTATION_UF__'] = ucfirst(strtolower($this->orientation));
        if ($this->orientation == 'landscape')
        {
            $this->vars['__SCREEN_WIDTH__'] = '960';
            $this->vars['__SCREEN_HEIGHT__'] = '640';
            $this->vars['__SCREEN_ORIENTATION_QUICK__'] = 'FIXED_HEIGHT';
        }
        else
        {
            $this->vars['__SCREEN_WIDTH__'] = '640';
            $this->vars['__SCREEN_HEIGHT__'] = '960';
            $this->vars['__SCREEN_ORIENTATION_QUICK__'] = 'FIXED_WIDTH';
        }

        if ($this->orientation == 'landscape')
        {
            $this->vars['__SCREEN_ORIENTATION_IOS__'] = "<string>UIInterfaceOrientationLandscapeRight</string>\n<string>UIInterfaceOrientationLandscapeLeft</string>";
        }
        else
        {
            $this->vars['__SCREEN_ORIENTATION_IOS__'] = '<string>UIInterfaceOrientationPortrait</string>';
        }

        // copy files
        $paths = $this->getPaths($this->templatePath);
        foreach ($paths as $sourcePath)
        {
            $sourceFilename = substr($sourcePath, strlen($this->templatePath));
            if ($sourceFilename == 'TEMPLATE_INFO.json') continue;
            if ($this->noproj && substr($sourceFilename, 0, 5) == 'proj.') continue;
            if ($this->noproj && substr($sourceFilename, 0, 8) == 'sources/') continue;
            if (!$this->copyFile($sourcePath, $sourceFilename)) return false;
        }

        return true;
    }

    private function copyFile($sourcePath, $sourceFilename)
    {
        // check filename
        $sourceFilename = substr($sourcePath, strlen($this->templatePath));
        $destinationFilename = $sourceFilename;

        foreach ($this->vars as $key => $value)
        {
            $value = str_replace('.', DS, $value);
            $destinationFilename = str_replace($key, $value, $destinationFilename);
        }

        printf("create file \"%s\" ... ", $destinationFilename);
        $dirname = pathinfo($destinationFilename, PATHINFO_DIRNAME);
        $destinationDir = $this->projectPath . $dirname;

        if (!is_dir($destinationDir))
        {
            mkdir($destinationDir, 0777, true);
        }
        if (!is_dir($destinationDir))
        {
            printf("ERROR: mkdir failure\n");
            return false;
        }

        $destinationPath = $this->projectPath . $destinationFilename;
        $contents = file_get_contents($sourcePath);
        if ($contents == false)
        {
            printf("ERROR: file_get_contents failure\n");
            return false;
        }
        $stat = stat($sourcePath);

        foreach ($this->vars as $key => $value)
        {
            $contents = str_replace($key, $value, $contents);
        }

        if (file_put_contents($destinationPath, $contents) == false)
        {
            printf("ERROR: file_put_contents failure\n");
            return false;
        }
        chmod($destinationPath, $stat['mode']);

        printf("OK\n");
        return true;
    }

    private function getPaths($dir)
    {
        $files = array();
        $dir = rtrim($dir, "/\\") . DS;
        $dh = opendir($dir);
        if ($dh == false)
        {
            return $files;
        }

        while (($file = readdir($dh)) !== false)
        {
            if ($file{0} == '.')
            {
                continue;
            }

            $path = $dir . $file;
            if (is_dir($path))
            {
                $files = array_merge($files, $this->getPaths($path));
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

usage: create_project [options] package_name

options:
    -f force copy files to project dir
    -o screen orientation, eg: -o landscape . default is portrait
    -t template path, eg: -t /quick-cocos2d-x/template/PROJECT_TEMPLATE_01
    -noproj skip create projects

    package name, eg: com.quickx.games.physics

examples:

    create_project -o landscape com.mycomp.games.game01


EOT;

}

if ($argc < 2)
{
    help();
    exit(1);
}

array_shift($argv);

$config = array(
    'orientation' => 'portrait',
    'force' => false,
    'templatePath' => '',
    'packageName' => '',
    'noproj' => false,
);

do
{
    if ($argv[0] == '-t')
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
    else if ($argv[0] == '-noproj')
    {
        $config['noproj'] = true;
    }
    else if ($config['packageName'] == '')
    {
        $config['packageName'] = $argv[0];
    }

    array_shift($argv);
} while (count($argv) > 0);

$creator = new ProjectCreator($config);
if ($creator->run())
{
    echo <<<EOT

DONE.


EOT;

}
else
{
    help();
}
