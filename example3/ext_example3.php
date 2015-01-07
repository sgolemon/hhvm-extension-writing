<?hh

<<__Native>>
function example3_fopen(string $filename, string $mode): resource;

<<__Native>>
function example3_fclose(resource $fp): void;

<<__Native>>
function example3_ftell(resource $fp): mixed;

<<__Native>>
function example3_fread(resource $fp, int $len): mixed;
