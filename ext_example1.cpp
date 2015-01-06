#include "hphp/runtime/base/base-includes.h"

namespace HPHP {
/////////////////////////////////////////////////////////////////////////////

class Example1Extension : public Extension {
 public:
  Example1Extension(): Extension("example1", "1.0") {}

  void moduleInit() override {
    loadSystemlib();
  }
} s_example1_extension;

HHVM_GET_MODULE(example1);

/////////////////////////////////////////////////////////////////////////////
} // namespace HPHP
