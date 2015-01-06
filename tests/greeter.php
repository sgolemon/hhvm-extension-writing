<?php

$g = new Example1_Greeter("Sara");
$g->greet();
var_dump($g->getName());
var_dump(Example1_Greeter::DefaultGreeting());
