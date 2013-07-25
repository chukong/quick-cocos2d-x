<?php

require_once(__DIR__ . '/Config.php');
require_once(__DIR__ . '/FileParser.php');

class DirScanner
{
    private $srcFilesDir;
    private $destDir;
    private $title;
    private $packageName;
    private $excludes;

    public function __construct(Config $config, array $params)
    {
        $this->srcFilesDir = $params['srcFilesDir'];
        $this->destDir = $params['destDir'];
        $this->title = $config->title;
        $this->packageName = $config->packageName;
        $this->excludes = $config->excludes;
    }

    public function execute()
    {
        $paths = $this->getFiles($this->srcFilesDir);

        $prefixLength = strlen($this->srcFilesDir);
        $modules = array();
        for ($i = 0; $i < count($paths); $i++)
        {
            $path = $paths[$i];
            $filename = trim(substr(substr($path, 0, -3), $prefixLength), "/\\.");
            $moduleName = str_replace(DS, '.', $filename);
            if (!empty($this->packageName))
            {
                $moduleName = $this->packageName . '.' . $moduleName;
            }

            $skip = false;
            foreach ($this->excludes as $key => $value)
            {
                $len = strlen($value);
                if (substr($moduleName, 0, $len) == $value)
                {
                    $skip = true;
                    break;
                }
            }
            if ($skip) continue;

            $module = array('path' => $path, 'filename' => $filename, 'moduleName' => $moduleName);
            $modules[] = $module;
        }

        foreach ($modules as $key => $module)
        {
            printf("process %s\n", $module['moduleName']);
            $parser = new FileParser();
            $module['tags'] = $parser->parse($module['path']);
            $modules[$key] = $module;
        }

        return $modules;
    }

    private function getFiles($dir)
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
