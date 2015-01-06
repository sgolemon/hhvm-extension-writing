<?php

$filename = __FILE__ . '.test';
@unlink($filename);

var_dump(file_exists($filename));
$f = new Example2_File($filename, 'w');
unset($f);
var_dump(file_exists($filename));
@unlink($filename);
