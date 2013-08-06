<?php

require(__DIR__ . "/luadocxMarkdown.php");

function makeCrossReferencesImpl($doc, $modules)
{
    return $doc;
}

function makeCrossReferences($doc, $modules)
{
    $pCodeBegin = "/<pre><code>/";
    $pCodeEnd = "/<\\/code><\\/pre>/";

    $matchesBegin = null;
    $matchesEnd = null;
    preg_match_all($pCodeBegin, $doc, $matchesBegin, PREG_OFFSET_CAPTURE);
    preg_match_all($pCodeEnd, $doc, $matchesEnd, PREG_OFFSET_CAPTURE);
    $offset = 0;
    $result = array();

    if (isset($matchesBegin[0]))
    {
        $matchesBegin = $matchesBegin[0];
    }
    if (isset($matchesEnd[0]))
    {
        $matchesEnd = $matchesEnd[0];
    }

    for ($i = 0; $i < count($matchesBegin); $i++)
    {
        $begin = $matchesBegin[$i][1];
        $end = $matchesEnd[$i][1];

        $prefix = substr($doc, $offset, $begin - $offset);
        $result[] = makeCrossReferencesImpl($prefix, $modules);

        $begin += 11;
        $code = substr($doc, $begin, $end - $begin - 1);
        $result[] = '<pre><code class="lua">' . $code;
        $offset = $end;
    }
    $suffix = substr($doc, $offset);
    if (strlen($suffix) > 0)
    {
        $result[] = makeCrossReferencesImpl($suffix, $modules);
    }

    return implode("\n", $result);
}

class FileParser
{
    private $title           = "";

    private $parseDocBegin      = "/^[ \t]*\\-\\-\\[\\[\\-\\-$/m";
    private $parseDocEnd        = "/^[ \t]*\\]\\]$/m";
    private $parseFunctionArray = array();

    private $moduleDocs         = array();
    private $moduleTags         = array();
    private $functions          = array();
    private $moduleName         = '';
    private $indexFilename      = '';

    public function __construct($title, $moduleName, $indexFilename)
    {
        $this->title         = $title;
        $this->moduleName    = $moduleName;
        $this->indexFilename = $indexFilename;

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
            // 取得文档开始位置
            $matches = array();
            if (preg_match($this->parseDocBegin, $contents, $matches, PREG_OFFSET_CAPTURE, $offset) == 0)
            {
                break;
            }
            $offset = $matches[0][1];
            // printf("comment begin: %d\n", $offset);

            // 取得文档结束位置
            if (preg_match($this->parseDocEnd, $contents, $matches, PREG_OFFSET_CAPTURE, $offset) == 0)
            {
                break;
            }
            $offsetEnd = $matches[0][1];

            $doc = $this->formatDoc(substr($contents, $offset, $offsetEnd - $offset));
            $offset = $offsetEnd;
            // printf("comment end: %d\n", $offset);

            // 取得下一个文档的开始位置
            $matchesNext = array();
            $nextOffset = $len;
            if (preg_match($this->parseDocBegin, $contents, $matchesNext, PREG_OFFSET_CAPTURE, $offset) != 0)
            {
                $nextOffset = $matchesNext[0][1];
            }
            // printf("next comment begin: %d\n", $nextOffset);

            // 函数定义必须位于当前文档的结束位置和下一个文档的开始位置之间
            // 查找函数定义
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
                        $tags = $this->findTags($doc);
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
                            $this->functions[$key] = array(
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
                $tags = $this->findTags($doc);
                $this->moduleTags = array_merge($this->moduleTags, $tags);
                // printf("comments count: %d\n", count($moduleDocs));
            }
        }
    }

    public function html($modules)
    {
        $title           = $this->title;
        $moduleName      = $this->moduleName;
        $moduleDocs      = $this->moduleDocs;
        $functions       = $this->functions;
        $indexFilename   = $this->indexFilename;

        ob_start();
        require(__DIR__ . '/luadocxPageHtmlTemplate.php');
        return ob_get_clean();
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

    private function findTags($contents)
    {
        $tags = array();
        $lines = explode("\n", $contents);
        for ($i = 0; $i < count($lines); $i++)
        {
            $line = trim($lines[$i]);
            if ($line == "") continue;

            $matches = array();
            if (preg_match("/\@(\w+)([ \t]+[\w\d_,\. ]+)?/i", $line, $matches) == 0) continue;

            $tag = array(
                "name" => $matches[1],
                "value" => isset($matches[2]) ? $matches[2] : ""
            );
            $tags[] = $tag;
        }

        return $tags;
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

        $doc = implode("\n", $result);

        return $doc;
    }
}
