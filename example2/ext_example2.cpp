#include "hphp/runtime/base/base-includes.h"
#include "hphp/runtime/vm/native-data.h"

#include <stdio.h>

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

String HHVM_METHOD(Example2_File, read, int64_t len) {
  auto data = Native::data<Example2_File>(this_);
  String ret(len, ReserveString);
  auto slice = ret.bufferSlice();
  len = fread(slice.ptr, 1, len, data->m_file);
  return ret.setSize(len);
}

int64_t HHVM_METHOD(Example2_File, tell) {
  auto data = Native::data<Example2_File>(this_);
  return ftell(data->m_file);
}

bool HHVM_METHOD(Example2_File, seek, int64_t pos, int64_t whence) {
  if ((whence != SEEK_SET) && (whence != SEEK_CUR) && (whence != SEEK_END)) {
    raise_warning("Invalid seek-whence");
    return false;
  }
  auto data = Native::data<Example2_File>(this_);
  return 0 == fseek(data->m_file, pos, whence);
}

/////////////////////////////////////////////////////////////////////////////

class Example2Extension : public Extension {
 public:
  Example2Extension(): Extension("example2", "1.0") {}

  void moduleInit() override {
    HHVM_ME(Example2_File, __construct);
    HHVM_ME(Example2_File, read);
    HHVM_ME(Example2_File, tell);
    HHVM_ME(Example2_File, seek);

#define X(w) \
    Native::registerClassConstant<KindOfInt64>(s_Example2_File.get(), \
                                               String::FromCStr(#w).get(), w);
    X(SEEK_SET);
    X(SEEK_CUR);
    X(SEEK_END);
#undef X

    Native::registerNativeDataInfo<Example2_File>(s_Example2_File.get());
    loadSystemlib();
  }
} s_example2_extension;

HHVM_GET_MODULE(example2);

/////////////////////////////////////////////////////////////////////////////
} // namespace HPHP
