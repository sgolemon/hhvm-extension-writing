#include "hphp/runtime/base/base-includes.h"

namespace HPHP {
/////////////////////////////////////////////////////////////////////////////

class Example2Extension : public Extension {
 public:
  Example2Extension(): Extension("example2", "1.0") {}

  void moduleInit() override {

    loadSystemlib();
  }
} s_example2_extension;

HHVM_GET_MODULE(example2);

/////////////////////////////////////////////////////////////////////////////
} // namespace HPHP
