#include "hphp/runtime/base/base-includes.h"
#include "hphp/runtime/vm/native-data.h"

namespace HPHP {
/////////////////////////////////////////////////////////////////////////////

const StaticString
  s_Example2_File("Example2_File");

class Example2_File {
 public:
  Example2_File() { /* new Example2_File */ }
  Example2_File(const Example2_File&) = delete;
  Example2_File& operator=(const Example2_File& src) {
    /* clone $instanceOfExample2_File */
    throw Object(SystemLib::AllocExceptionObject(
      "Cloning Example2_File is not allowed"
    ));
  }

  ~Example2_File() { sweep(); }
  void sweep() {
    if (m_file) {
      fclose(m_file);
      m_file = nullptr;
    }
  }

  FILE* m_file{nullptr};
};

/////////////////////////////////////////////////////////////////////////////

void HHVM_METHOD(Example2_File, __construct,
                 const String& filename, const String& mode) {
  auto data = Native::data<Example2_File>(this_);
  if (data->m_file) {
    throw Object(SystemLib::AllocExceptionObject(
      "File is already open!"
    ));
  }
  data->m_file = fopen(filename.c_str(), mode.c_str());
  if (!data->m_file) {
    String message("Unable to open ");
    message += filename + ": errno=" + String(errno);
    throw Object(SystemLib::AllocExceptionObject(message));
  }
}

/////////////////////////////////////////////////////////////////////////////

class Example2Extension : public Extension {
 public:
  Example2Extension(): Extension("example2", "1.0") {}

  void moduleInit() override {
    HHVM_ME(Example2_File, __construct);

    Native::registerNativeDataInfo<Example2_File>(s_Example2_File.get());
    loadSystemlib();
  }
} s_example2_extension;

HHVM_GET_MODULE(example2);

/////////////////////////////////////////////////////////////////////////////
} // namespace HPHP
