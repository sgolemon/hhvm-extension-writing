#include "hphp/runtime/base/base-includes.h"

#include <stdio.h>

namespace HPHP {
/////////////////////////////////////////////////////////////////////////////

class Example3File : public SweepableResourceData {
 public:
  DECLARE_RESOURCE_ALLOCATION_NO_SWEEP(Example3File)
  CLASSNAME_IS("example3-file")
  const String& o_getClassNameHook() const override { return classnameof(); }

  Example3File(const String& filename, const String& mode) {
    m_file = fopen(filename.c_str(), mode.c_str());
    if (!m_file) {
      throw Object(SystemLib::AllocExceptionObject(
        "Unable to open file"
      ));
    }
  }

  ~Example3File() { sweep(); }
  void sweep() { close(); }

  void close() {
    if (m_file) {
      fclose(m_file);
      m_file = nullptr;
    }
  }

  bool isInvalid() const override {
    return !m_file;
  }

  FILE* m_file{nullptr};
};

/////////////////////////////////////////////////////////////////////////////

Resource HHVM_FUNCTION(example3_fopen, const String& filename,
                                       const String& mode) {
  return Resource(NEWOBJ(Example3File)(filename, mode));
}

void HHVM_FUNCTION(example3_fclose, const Resource& fp) {
  // By default, if fp is not of type "Example3File" and valid,
  // HHVM will throw an exception here
  auto f = fp.getTyped<Example3File>();
  f->close();
}

Variant HHVM_FUNCTION(example3_ftell, const Resource& fp) {
  // By passing "true" for "badTypeOkay", invalid resources
  // result in returning nullptr, rather than throwing an exception
  // So check the return type!
  auto f = fp.getTyped<Example3File>(true /* nullOkay */,
                                     true /* badTypeOkay */);
  if (!f) {
    raise_warning("Instance of example3-file resource expected");
    return init_null();
  }
  return (int64_t)ftell(f->m_file);
}

// Since you'll probably do a lot of it, why not make a macro?
#define FETCH_EXAMPLE3_FP(f, fp) \
  auto f = fp.getTyped<Example3File>(true, true); \
  if (!f) { \
    raise_warning("Instance of example3-file resource expected"); \
    return init_null(); \
  }

Variant HHVM_FUNCTION(example3_fread, const Resource& fp, int64_t len) {
  FETCH_EXAMPLE3_FP(f, fp);

  String ret(len, ReserveString);
  auto slice = ret.bufferSlice();
  len = fread(slice.ptr, 1, len, f->m_file);
  return ret.setSize(len);
}

/////////////////////////////////////////////////////////////////////////////

class Example3Extension : public Extension {
 public:
  Example3Extension(): Extension("example3", "1.0") {}

  void moduleInit() override {
    HHVM_FE(example3_fopen);
    HHVM_FE(example3_fclose);
    HHVM_FE(example3_ftell);
    HHVM_FE(example3_fread);

    loadSystemlib();
  }
} s_example3_extension;

HHVM_GET_MODULE(example3);

/////////////////////////////////////////////////////////////////////////////
} // namespace HPHP
