<?php

$f = new Example2_File(__FILE__, 'r');
var_dump($f->tell());
var_dump($f->read(5));
var_dump($f->tell());
var_dump($f->seek(1));
var_dump($f->tell());
var_dump($f->read(4));
