<?hh

<<__NativeData("Example2_File")>>
class Example2_File {
  <<__Native>>
  public function __construct(string $filename, string $mode): void;

  <<__Native>>
  public function read(int $len): string;

  <<__Native>>
  public function tell(): int;

  <<__Native>>
  public function seek(int $pos, int $whence = self::SEEK_SET): bool;
}
