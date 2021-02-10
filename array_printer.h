#include <napi.h>

class ArrayPrinter : public Napi::ObjectWrap<ArrayPrinter> {

  friend class PrintArrayAsyncWorker;

  private:
    Napi::Reference<Napi::Array> array_reference;

  public:
    static Napi::FunctionReference constructor;
    static Napi::Object Init(Napi::Env env, Napi::Object exports);

    ArrayPrinter(const Napi::CallbackInfo& info);
    ~ArrayPrinter();

    Napi::Value PrintArray(const Napi::CallbackInfo& info);
};