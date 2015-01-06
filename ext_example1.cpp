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
  s_name("name"),
  s_hello("hello"),
  s_Stranger("Stranger");

void HHVM_FUNCTION(example1_greet_options, const Array& options) {
  String name(s_Stranger);
  if (options.exists(s_name)) {
    name = options[s_name].toString();
  }
  bool hello = true;
  if (options.exists(s_hello)) {
    hello = options[s_hello].toBoolean();
  }
  g_context->write(hello ? "Hello " : "Goodbye ");
  g_context->write(name);
  g_context->write("\n");
}

Array HHVM_FUNCTION(example1_greet_make_options,
                    const String& name, bool hello) {
  Array ret = Array::Create();
  if (!name.empty()) {
    ret.set(s_name, name);
  }
  ret.set(s_hello, hello);
  return ret;
}

const StaticString
  s_secret("Open Sesame");

Variant HHVM_FUNCTION(example1_password, const String& guess) {
  if (guess.same(s_secret)) {
    return "Password accepted: A winner is you!";
  }
  return false;
}

void HHVM_FUNCTION(example1_var_dump, const Variant &value) {
  if (value.isNull()) {
    g_context->write("null\n");
    return;
  }
  if (value.isBoolean()) {
    g_context->write("bool(");
    g_context->write(value.toBoolean() ? "true" : "false");
    g_context->write(")\n");
    return;
  }
  if (value.isInteger()) {
    g_context->write("int(");
    g_context->write(String(value.toInt64()));
    g_context->write(")\n");
    return;
  }
  if (value.isDouble()) {
    g_context->write("float(");
    g_context->write(String(value.toDouble()));
    g_context->write(")\n");
    return;
  }
  if (value.isString()) {
    auto strval = value.toString();
    g_context->write("string(");
    g_context->write(String(strval.size()));
    g_context->write(") \"");
    g_context->write(strval);
    g_context->write("\"\n");
    return;
  }
  if (value.isArray()) {
    g_context->write("array(");
    g_context->write(String(value.toArray().size()));
    g_context->write(")\n");
    return;
  }
  g_context->write("Something else, I dunno what...\n");
}

const StaticString
  s_Example1_Greeter("Example1_Greeter");

String HHVM_METHOD(Example1_Greeter, getName) {
  return this_->o_get(s_name, false, s_Example1_Greeter);
}

String HHVM_STATIC_METHOD(Example1_Greeter, DefaultGreeting) {
  return "Hello";
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
    HHVM_FE(example1_greet_options);
    HHVM_FE(example1_greet_make_options);
    HHVM_FE(example1_password);
    HHVM_FE(example1_var_dump);

    HHVM_ME(Example1_Greeter, getName);
    HHVM_STATIC_ME(Example1_Greeter, DefaultGreeting);

    loadSystemlib();
  }
} s_example1_extension;

HHVM_GET_MODULE(example1);

/////////////////////////////////////////////////////////////////////////////
} // namespace HPHP
