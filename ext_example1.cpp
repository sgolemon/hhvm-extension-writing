#include "hphp/runtime/base/base-includes.h"

namespace HPHP {
/////////////////////////////////////////////////////////////////////////////

void HHVM_FUNCTION(example1_greet, const String& name, bool hello) {
  g_context->write(hello ? "Hello " : "Goodbye ");
  g_context->write(name);
  g_context->write("\n");
}

bool HHVM_FUNCTION(example1_is_odd, int64_t num) {
  return (num % 2);
}

void HHVM_FUNCTION(example1_life, VRefParam meaning) {
  meaning = 42;
}

String HHVM_FUNCTION(example1_count_preallocate) {
  /* 30 bytes: 3 per number: 'X, ' */
  String ret(30, ReserveString);
  auto slice = ret.bufferSlice();
  for (int i = 0; i < 10; ++i) {
    snprintf(slice.ptr + (i*3), 4, "%d, ", i);
  }
  /* Terminate just after the 9th digit, overwriting the ',' with a null byte */
  return ret.setSize((9*3) + 1);
}

String HHVM_FUNCTION(example1_count_concatenate) {
  String ret, delimiter(", ");
  for (int i = 0; i < 10; ++i) {
    if (i > 0) {
      ret += delimiter;
    }
    ret += String(i);
  }
  return ret;
}
const StaticString
  s_EXAMPLE1_NOTHING("EXAMPLE1_NOTHING"),
  s_EXAMPLE1_YEAR("EXAMPLE1_YEAR"),
  s_EXAMPLE1_URL("EXAMPLE1_URL"),
  s_URL("http://blog.golemon.com/2015/01/hhvm-extension-writing-part-i.html");

class Example1Extension : public Extension {
 public:
  Example1Extension(): Extension("example1", "1.0") {}

  void moduleInit() override {
    Native::registerConstant<KindOfNull>(s_EXAMPLE1_NOTHING.get());
    Native::registerConstant<KindOfInt64>(s_EXAMPLE1_YEAR.get(), 2015);
    Native::registerConstant<KindOfStaticString>(s_EXAMPLE1_URL.get(),
                                                 s_URL.get());

    HHVM_FE(example1_greet);
    HHVM_FE(example1_is_odd);
    HHVM_FE(example1_life);
    HHVM_FE(example1_count_preallocate);
    HHVM_FE(example1_count_concatenate);

    loadSystemlib();
  }
} s_example1_extension;

HHVM_GET_MODULE(example1);

/////////////////////////////////////////////////////////////////////////////
} // namespace HPHP
