<?php

require_once(__DIR__ . '/Config.php');
require_once(__DIR__ . '/GeneratorBase.php');

class LocalHTMLGenerator extends GeneratorBase
{
    public function execute($srcFilesDir, $destDir)
    {
        $templateDir = dirname(__DIR__) . DS . 'template' . DS;
        $templatePath = $templateDir . 'apidoc_module_html.php';

        $config = $this->config;
        $modules = $this->modules;
        $indexFilename = '';
        foreach ($modules as $key => $module)
        {
            if ($module['moduleName'] == $this->config->indexModule)
            {
                $module['outputFilename'] = $this->getModulePath($destDir, 'index', '.html');
                $indexFilename = $module['outputFilename'];
            }
            else
            {
                $module['outputFilename'] = $this->getModulePath($destDir, $module['moduleName'], '.html');
                if (empty($indexFilename))
                {
                    $indexFilename = $module['outputFilename'];
                }
            }
            $modules[$key] = $module;
        }

        foreach ($modules as $key => $module)
        {
            $moduleName = $module['moduleName'];
            $functions = $module['tags']['functions'];

            printf("proces module %s ... ", $module['moduleName']);
            ob_start();
            require($templatePath);
            $contents = ob_get_clean();
            print("ok\n");
            file_put_contents($module['outputFilename'], $contents);
        }

        print("copy assets ... ");
        $this->copyFile($templateDir, $destDir, 'luadocx-highlight.min.js');
        $this->copyFile($templateDir, $destDir, 'luadocx-style.css');
        $this->copyFile($templateDir, $destDir, 'luadocx-style-monokai.css');
        print("ok\n");
    }
}
