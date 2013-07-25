<?php

class Config
{
    public $title;
    public $packageName;
    public $excludes;

    public function __construct($configFilePath)
    {
        $contents = @file_get_contents($configFilePath);
        if ($contents)
        {
            $config = @json_decode($contents, true);
            if (is_array($config))
            {
                $this->title = !empty($config['title']) ? $config['title'] : '';
                $this->packageName = !empty($config['packageName']) ? $config['packageName'] : '';
                $excludes = !empty($config['excludes']) ? $config['excludes'] : '';
                $excludes = explode(',', $excludes);
                foreach ($excludes as $key => $value)
                {
                    $value = trim($value);
                    if (!empty($value))
                    {
                        $excludes[$key] = $value;
                    }
                    else
                    {
                        unset($excludes[$key]);
                    }
                }
                $this->excludes = $excludes;
            }
        }
    }

    public function isValid()
    {
        return !empty($this->title);
    }

}
