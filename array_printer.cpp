#include "array_printer.h"

Napi::FunctionReference ArrayPrinter::constructor;

Napi::Object ArrayPrinter::Init(Napi::Env env, Napi::Object exports) {

  Napi::HandleScope scope(env);

  Napi::Function constructorFunction = DefineClass(env, "ArrayPrinter", {
    InstanceMethod("printArray", &ArrayPrinter::PrintArray)
  });

  constructor = Napi::Persistent(constructorFunction);
  constructor.SuppressDestruct();

  return exports;
}

// The constructor
ArrayPrinter::ArrayPrinter(const Napi::CallbackInfo& info) : Napi::ObjectWrap<ArrayPrinter>(info) {
  this->array_reference = Napi::Persistent(info[0].As<Napi::Array>());
}

ArrayPrinter::~ArrayPrinter() {
  return;
}

class PrintArrayAsyncWorker : public Napi::AsyncWorker {

  private:
    ArrayPrinter    *array_printer;

  public:
    PrintArrayAsyncWorker
    (
      ArrayPrinter  *array_printer,
      Napi::Function &callback
    ) 
    :
    AsyncWorker(callback),
    array_printer(array_printer)
    {}

    ~PrintArrayAsyncWorker() {}

    void Execute() {
      // This is where code would execute, but right now I don't really care
      // what happens here, just that we do SOME async work and then go to OnOk.
    }

    void OnOK() {

      printf("OnOk for PrintArray?\n");

      Napi::Env env = Env();
      Napi::HandleScope scope(env);

      printf("ArrayPrinter->Array is Array? %d\n", array_printer->array_reference.Value().IsArray());

      // Now, array should be returned
      std::vector<napi_value> callbackArguments;
      callbackArguments.push_back(env.Null());
      callbackArguments.push_back(array_printer->array_reference.Value().As<Napi::Array>());
      Callback().Call(callbackArguments);
    }
};

Napi::Value ArrayPrinter::PrintArray(const Napi::CallbackInfo& info) {
  
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  Napi::Function callback = info[0].As<Napi::Function>();

  printf("In function call, is this->array an Array? %d\n", this->array_reference.Value().IsArray());

  PrintArrayAsyncWorker *worker = new PrintArrayAsyncWorker(this, callback);
  worker->Queue();

  return env.Undefined();
}
