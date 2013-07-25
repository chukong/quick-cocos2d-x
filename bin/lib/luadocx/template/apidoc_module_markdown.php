
# <?php echo $module['moduleName']; ?>

<?php foreach ($module['tags']['moduleDocs'] as $doc): ?>

<?php echo $doc; ?>

<?php endforeach; ?>


<br />

Function | Description
-------- | -----------
<?php
$anchors = array();
foreach ($module['tags']['functions'] as $offset => $function):
    $fn = str_replace(array('.'), array('_'), $function['name']);
    $functionName = sprintf('%s(%s)', $function['name'], $function['params']);
    ?>
<?php echo $functionName; ?> | <?php echo !empty($function['description']) ? $function['description'] : "~"; ?>

<?php endforeach; ?>

