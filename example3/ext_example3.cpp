#include "hphp/runtime/base/base-includes.h"

namespace HPHP {
/////////////////////////////////////////////////////////////////////////////

class Example3Extension : public Extension {
 public:
  Example3Extension(): Extension("example3", "1.0") {}

  void moduleInit() override {

    loadSystemlib();
  }
} s_example3_extension;

HHVM_GET_MODULE(example3);

/////////////////////////////////////////////////////////////////////////////
} // namespace HPHP
