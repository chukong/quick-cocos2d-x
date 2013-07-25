<?php

require_once(__DIR__ . '/Config.php');

class APIDocumentsGenerator
{
    private $modules;

    public function __construct(Config $config, array $modules)
    {
        $this->modules = $modules;
        usort($this->modules, array($this, 'compareTwoModule'));
    }

    public function execute($destDir)
    {
        $chars = array('.', '-', '/', ':');
        $count = count($this->modules);
        for ($i = 0; $i < $count; $i++)
        {
            $module = $this->modules[$i];
            // create module index page
            ob_start();
            require(__DIR__ . '/../template/apidoc_module_markdown.php');
            $contents = ob_get_clean();
            $outputPath = $destDir . DS . strtolower(str_replace($chars, '_', $module['moduleName'])) . '_index.md';
            file_put_contents($outputPath, $contents);

            $parts = explode('.', $module['moduleName']);
            $last = $parts[count($parts) - 1];

            // create module functions page
            foreach ($module['tags']['functions'] as $function)
            {
                ob_start();
                require(__DIR__ . '/../template/apidoc_function_markdown.php');
                $contents = ob_get_clean();

                $functionName = $function['name'];
                $parts = explode('.', $functionName);
                $first = $parts[0];

                if ($first == $last)
                {
                    array_shift($parts);
                    $functionName = implode('.', $parts);
                }
                $outputPath = $destDir . DS . strtolower(str_replace($chars, '_', $module['moduleName'] . '_function_' . $functionName)) . '.md';
                file_put_contents($outputPath, $contents);
            }
        }
    }

    private function compareTwoModule($one, $two)
    {
        $oneDepth = substr_count($one['moduleName'], '.');
        $twoDepth = substr_count($two['moduleName'], '.');
        if ($oneDepth == 0 && $twoDepth == 0) return strcmp($one['moduleName'], $two['moduleName']);
        if ($oneDepth == 0) return -1;
        if ($twoDepth == 0) return 1;

        return strcmp($one['moduleName'], $two['moduleName']);
    }

}
