<?php

require_once(__DIR__ . "/Markdown.php");

class FileParser
{
    private $parseDocBegin      = "/^[ \t]*\\-\\-\\[\\[\\-\\-$/m";
    private $parseDocEnd        = "/^[ \t]*\\]\\]$/m";
    private $parseFunctionArray = array();

    private $moduleDocs         = array();
    private $moduleTags         = array();
    private $functions          = array();

    public function __construct()
    {
        $functionName               = "([\w\d_:\.]+)";
        $functionParams             = "([\w\d_,\. ]*)";
        $this->parseFunctionArray[] = "/function[ \t]+${functionName}[ \t]*\(${functionParams}\)/i";
        $this->parseFunctionArray[] = "/${functionName}[ \t]*=[ \t]*function[ \t]*\(${functionParams}\)/i";
    }

    public function parse($filename)
    {
        $contents = file_get_contents($filename);

        $this->moduleDocs = array();
        $this->functions = array();

        $offset = 0;
        $len = strlen($contents);
        while ($offset < $len)
        {
            $matches = array();
            if (preg_match($this->parseDocBegin, $contents, $matches, PREG_OFFSET_CAPTURE, $offset) == 0)
            {
                break;
            }
            $offset = $matches[0][1];
            // printf("comment begin: %d\n", $offset);

            if (preg_match($this->parseDocEnd, $contents, $matches, PREG_OFFSET_CAPTURE, $offset) == 0)
            {
                break;
            }
            $offsetEnd = $matches[0][1];

            $doc = $this->formatDoc(substr($contents, $offset, $offsetEnd - $offset));
            $offset = $offsetEnd;
            // printf("comment end: %d\n", $offset);

            $matchesNext = array();
            $nextOffset = $len;
            if (preg_match($this->parseDocBegin, $contents, $matchesNext, PREG_OFFSET_CAPTURE, $offset) != 0)
            {
                $nextOffset = $matchesNext[0][1];
            }
            // printf("next comment begin: %d\n", $nextOffset);

            for ($i = 0; $i < count($this->parseFunctionArray); $i++)
            {
                $pFunc = $this->parseFunctionArray[$i];
                if (preg_match($pFunc, $contents, $matches, PREG_OFFSET_CAPTURE, $offset) != 0)
                {
                    if ($matches[0][1] >= $offset && $matches[0][1] < $nextOffset)
                    {
                        // printf("func offset: %d\n", $matches[0][1]);
                        $key = $matches[0][1];
                        $functionName = $matches[1][0];
                        if (substr($functionName, 0, 2) == 'M.')
                        {
                            $functionName = substr($functionName, 2);
                        }
                        $tags = $this->extractTags($doc);
                        $ignore = false;
                        foreach ($tags as $tag)
                        {
                            if ($tag['name'] == 'ignore')
                            {
                                $ignore = true;
                                break;
                            }
                        }

                        if (!$ignore)
                        {
                            $this->functions[] = array(
                                'description' => $this->findFirstLine($doc),
                                'tags'        => $tags,
                                'doc'         => $doc,
                                'name'        => $functionName,
                                'type'        => $i,
                                'params'      => $matches[2][0],
                            );
                        }
                        $doc = null;
                    }

                    break;
                }
            }

            if ($doc)
            {
                $this->moduleDocs[] = $doc;
                $tags = $this->extractTags($doc);
                $this->moduleTags = array_merge($this->moduleTags, $tags);
                // printf("comments count: %d\n", count($moduleDocs));
            }
        }

        return array('moduleDocs' => $this->moduleDocs, 'moduleTags' => $this->moduleTags,
            'functions' => $this->functions);
    }

    private function findFirstLine($contents)
    {
        $lines = explode("\n", $contents);
        for ($i = 0; $i < count($lines); $i++)
        {
            if (trim($lines[$i]) != "") return trim($lines[$i]);
        }
        return "";
    }

    private function extractTags(& $contents)
    {
        $firstParam = true;
        $firstReturn = true;
        $tags = array();
        $lines = explode("\n", $contents);
        $count = count($lines);
        for ($i = 0; $i < $count; $i++)
        {
            $line = trim($lines[$i]);
            if ($line == '') continue;

            $matches = array();
            if (preg_match("/\@(\w+)([ \t]+[\w\d_,\. ]+)?/i", $line, $matches) == 0) continue;

            $tag = array(
                "name" => $matches[1],
                "value" => isset($matches[2]) ? trim($matches[2]) : ''
            );
            $tags[] = $tag;

            $line = $this->processTag($tag, $line);
            $lines[$i] = $line;

            if ($firstParam && ($tag['name'] == 'param' || $tag['name'] == 'optional'))
            {
                $a = array_slice($lines, 0, $i);
                array_push($a, '');
                array_push($a, '### Parameters');
                array_push($a, '');
                $lines = array_merge($a, array_slice($lines, $i));
                $firstParam = false;
                $count += 3;
            }

            if ($firstReturn && $tag['name'] == 'return')
            {
                $a = array_slice($lines, 0, $i);
                array_push($a, '');
                array_push($a, '### Returns');
                array_push($a, '');
                $lines = array_merge($a, array_slice($lines, $i));
                $firstParam = false;
                $count += 3;
            }

        }

        $contents = trim(implode("\n", $lines));

        return $tags;
    }

    private function processTag($tag, $line)
    {
        switch ($tag['name'])
        {
            case 'param':
                $parts = explode(' ', $tag['value']);
                if (!empty($parts[1]))
                {
                    $parts[1] = '**' . $parts[1] . '**';
                }
                return '-   ' . implode(' ', $parts);

            case 'optional':
                $parts = explode(' ', $tag['value']);
                if (!empty($parts[1]))
                {
                    return trim(sprintf('-   [_optional %s **%s**_] %s', $parts[0], $parts[1], implode(' ', array_slice($parts, 2))));
                }
                else
                {
                    return trim(sprintf('-   [_optional **%s**_]', $parts[0]));
                }

            case 'return':
                return '-   ' . trim($tag['value']);

            case 'example':
                return '### Example';
        }

        return $line;
    }

    private function formatDoc($doc)
    {
        $lines = explode("\n", $doc);
        $result = array();
        $tabstop = -1;
        foreach ($lines as $line)
        {
            $t = trim($line);
            if ($t == '--[[--' || $t == ']]') continue;
            if ($tabstop == -1 && $t == '') continue;

            $line = str_replace("\t", '    ', $line);
            $line = rtrim($line);

            if ($tabstop == -1)
            {
                $tabstop = strlen($line) - strlen(ltrim($line));
                $line = trim($line);
            }
            else
            {
                $line = substr($line, $tabstop);
            }
            $result[] = $line;
        }

        $doc = trim(implode("\n", $result));

        return $doc;
    }
}
