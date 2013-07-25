<?php

require_once(__DIR__ . '/Config.php');
require_once(__DIR__ . '/GeneratorBase.php');

class MarkdownGenerator extends GeneratorBase
{
    public function execute($destDir)
    {
        $count = count($this->modules);
        for ($i = 0; $i < $count; $i++)
        {
            $module = $this->modules[$i];
            $moduleName = $module['moduleName'];

            // create module index page
            ob_start();
            require(__DIR__ . '/../template/apidoc_module_markdown.php');
            $contents = ob_get_clean();
            file_put_contents($this->getModuleIndexPath($destDir, $moduleName, '.md'), $contents);

            // create module functions page
            foreach ($module['tags']['functions'] as $function)
            {
                ob_start();
                require(__DIR__ . '/../template/apidoc_function_markdown.php');
                $contents = ob_get_clean();
                file_put_contents($this->getModuleFunctionPath($destDir, $moduleName, $function['name'], '.md'), $contents);
            }
        }
    }
}
