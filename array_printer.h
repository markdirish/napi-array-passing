#include <napi.h>

class ArrayPrinter : public Napi::ObjectWrap<ArrayPrinter> {

  friend class PrintArrayAsyncWorker;

  private:
    Napi::Array array;

  public:
    static Napi::FunctionReference constructor;

    explicit ArrayPrinter(const Napi::CallbackInfo& info);

    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Napi::Value PrintArray(const Napi::CallbackInfo& info);
};