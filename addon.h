#include <napi.h>
#include <array_printer.h>

class Addon : public Napi::ObjectWrap<Addon> {

  public:
    static Napi::FunctionReference constructor;
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Napi::Value PassArray(const Napi::CallbackInfo& info);
};