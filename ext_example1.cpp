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

class Example1Extension : public Extension {
 public:
  Example1Extension(): Extension("example1", "1.0") {}

  void moduleInit() override {
    HHVM_FE(example1_greet);
    HHVM_FE(example1_is_odd);
    HHVM_FE(example1_life);

    loadSystemlib();
  }
} s_example1_extension;

HHVM_GET_MODULE(example1);

/////////////////////////////////////////////////////////////////////////////
} // namespace HPHP
