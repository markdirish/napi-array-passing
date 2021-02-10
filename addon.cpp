#include "addon.h"

Napi::Object Addon::Init(Napi::Env env, Napi::Object exports) {

  Napi::HandleScope scope(env);

  Napi::Function constructorFunction = DefineClass(env, "Addon", {
    InstanceMethod("passArray", Addon::PassArray)
  });

  constructor = Napi::Persistent(constructorFunction);
  constructor.SuppressDestruct();

  return exports;
}

class PassArrayAsyncWorker : public Napi::AsyncWorker {

  private:
    Napi::Reference<Napi::Array> array_reference;

  public:
    PassArrayAsyncWorker
    (
      Napi::Array     array,
      Napi::Function &callback
    ) 
    :
    AsyncWorker(callback),
    array_reference(Napi::Persistent(array))
    {}

    ~PassArrayAsyncWorker() {}

    void Execute() {
      // This is where code would execute, but right now I don't really care
      // what happens here, just that we do SOME async work and then go to OnOk.
    }

    void OnOK() {

      Napi::Env env = Env();
      Napi::HandleScope scope(env);

      // In OnOk, the Array should have survived the trip through Execute
      printf("Size of Array is %d\n", array_reference.Value().Length());

      // arguments for the ArrayPrinter constructor
      std::vector<napi_value> printer_arguments;
      printer_arguments.push_back(array_reference.Value());

      // create a new ArrayPrinter object as a Napi::Value
      Napi::Value array_printer = ArrayPrinter::constructor.New(printer_arguments);

      // return ArrayPrinter
      std::vector<napi_value> callbackArguments;
      callbackArguments.push_back(env.Null());
      callbackArguments.push_back(array_printer);

      Callback().Call(callbackArguments);
    }
};

Napi::Value Addon::PassArray(const Napi::CallbackInfo& info) {
  
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  Napi::Array array       = info[0].As<Napi::Array>();
  Napi::Function callback = info[1].As<Napi::Function>();

  PassArrayAsyncWorker *worker = new PassArrayAsyncWorker(array, callback);
  worker->Queue();

  return env.Undefined();
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {

  Addon::Init(env, exports);
  ArrayPrinter::Init(env, exports);

  return exports;
}