#include <napi.h>
#include "array_printer.h"

class Addon {

  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    static Napi::Value PassArray(const Napi::CallbackInfo& info);
};