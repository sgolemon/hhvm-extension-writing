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

<<__Native>>
function example1_greet_options(array $options): void;

<<__Native>>
function example1_greet_make_options(string $name = "",
                                     bool $hello = true): array;

<<__Native>>
function example1_password(string $guess): mixed;

<<__Native>>
function example1_var_dump(mixed $value): void;

class Example1_Greeter {
  public function greet() {
    echo self::DefaultGreeting(), " {$this->name}\n";
  }

  public function __construct(protected string $name = 'Stranger') {}

  <<__Native>>
  public function getName(): string;

  <<__Native>>
  static public function DefaultGreeting(): string;
}
