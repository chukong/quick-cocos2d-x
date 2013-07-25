
# <?php echo $moduleName; ?>

<?php foreach ($moduleDocs as $doc): ?>

<?php echo $doc; ?>

<?php endforeach; ?>

<br />

Function | Description
-------- | -----------
<?php
$anchors = array();
foreach ($functions as $offset => $function):
    $fn = str_replace(array('.'), array('_'), $function['name']);
    if (isset($anchors[$fn]))
    {
        $anchors[$fn]++;
        $anchorName = sprintf('anchor_%s_%d', $fn, $anchors[$fn]);
    }
    else
    {
        $anchorName = sprintf('anchor_%s', $fn, $offset);
        $anchors[$fn] = 1;
    }
    $anchorName = str_replace(':', '_', $anchorName);
    $functions[$offset]['anchorName'] = $anchorName;
    $indent = (strpos($function['name'], ':')) ? '    ' : '';
    $functionName = sprintf('%s(%s)', $function['name'], $function['params']);
    ?>
[<?php echo $functionName; ?>](#<?php echo $anchorName; ?>) | <?php echo
!empty($function['description']) ? $function['description'] : "~"; ?>

<?php endforeach; ?>


<?php
foreach ($functions as $offset => $function):
    $fn = str_replace(array('.'), array('_'), $function['name']);
    $anchorName = $functions[$offset]['anchorName'];
    $indent = (strpos($function['name'], ':')) ? '#' : '';
    $class = (strpos($function['name'], ':')) ? 'member_method' : '';
    $functionName = htmlspecialchars(sprintf('%s(%s)', $function['name'], $function['params']));

?>

<hr />

<?php echo $indent; ?>### <a id="<?php echo $anchorName; ?>"></a><?php echo $functionName; ?>


<?php echo $function['doc']; ?>

<?php endforeach; ?>
