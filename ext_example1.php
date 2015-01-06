<?hh

function example1_hello() {
  echo "Hello World\n";
}

<<__Native>>
function example1_greet(string $name, bool $hello = false): void;

<<__Native>>
function example1_is_odd(int $num): bool;

<<__Native>>
function example1_life(mixed &$meaning): void;

<<__Native>>
function example1_count_preallocate(): string;

<<__Native>>
function example1_count_concatenate(): string;
