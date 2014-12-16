<?php

require_once(__DIR__ . '/init.php');

class EncryptSetter
{
    private $config;
    private $options;
    private $validated = false;
    private $vars = array();

    function __construct(array $config, array $options)
    {
        $this->config = $config;
        $this->options = $options;
    }

    function validateConfig()
    {
        // check project path
        $defFile1 = 'lopcodes.def';
        $defFile2 = 'lopmodes.def';
        if ($this->config['project'])
        {
            $projPath = rtrim($this->config['project'], "/\\") . DS;
            if (!is_dir($projPath))
            {
                printf("ERROR: invalid project path \"%s\"\n", $projPath);
                return false;
            }
            $filePath = $projPath . 'frameworks/cocos2d-x/external/lua/lua/';
            if ( !file_exists($filePath . $defFile1)
                    || !file_exists($filePath . $defFile2)
                )
            {
                printf("ERROR: invalid project path \"%s\"\n", $projPath);
                return false;
            }
        }
        else
        {
            $quickPath = dirname(BIN_DIR) . DS;
            // $quick_ver = 2;
            if (!file_exists($quickPath . 'VERSION'))
            {
                $quickPath = dirname($quickPath) . DS;
                if (!file_exists($quickPath . 'VERSION'))
                {
                    printf("ERROR: invalid quick path !!\n");
                    return false;
                }
                // $quick_ver = 3;
                $filePath = $quickPath . 'external/lua/lua/';
            }
            else
            {
                $filePath = $quickPath . 'lib/cocos2d-x/scripting/lua/lua/lua-5.1.5/src/';
            }

            if ( !file_exists($filePath . $defFile1)
                    || !file_exists($filePath . $defFile2)
                )
            {
                printf("ERROR: invalid quick path !!\n");
                return false;
            }
        }
        $this->config['def_file_1'] = $filePath . $defFile1;
        $this->config['def_file_2'] = $filePath . $defFile2;

        $this->validated = true;
        return true;
    }

    function run()
    {
        if (!$this->validated)
        {
            print("ERR: invalid config\n");
            return false;
        }

        print("file1: " . $this->config['def_file_1'] . "\n");
        print("file2: " . $this->config['def_file_2'] . "\n");

        print("\n\n");

        return true;
    }

}
