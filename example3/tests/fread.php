<?php

$f = example3_fopen(__FILE__, 'r');
var_dump($f);
var_dump(example3_fread($f, 5));
var_dump(example3_ftell($f));
