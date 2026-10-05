#include "src/V8/V8Controller.h"

#include <v8.h>

#include <memory>
#include <string>

#include "src/V8/V8Console.h"
#include "src/V8/V8Platform.h"
#include "src/log/log.h"

namespace v8i
{

namespace
{

v8::MaybeLocal<v8::String> to_v8(v8::Isolate* isolate, const std::string& str)
{
  return v8::String::NewFromUtf8(isolate, str.data(),
                                 v8::NewStringType::kNormal,
                                 static_cast<int>(str.size()));
}

void report(v8::Isolate* isolate, const v8::TryCatch& tryCatch)
{
  const auto message = tryCatch.Message();

  if (message.IsEmpty()) {
    LOGE("The JavaScript code execution is terminated");
    return;
  }

  const v8::String::Utf8Value script{isolate, message->GetScriptResourceName()};
  const v8::String::Utf8Value text{isolate, message->Get()};

  LOGE((*script != nullptr ? *script : "")
       << ":"
       << message->GetLineNumber(isolate->GetCurrentContext()).FromMaybe(0)
       << " : " << (*text != nullptr ? *text : ""));
}

}  // namespace

V8Controller::~V8Controller()
{
  context.Reset();

  if (isolate != nullptr) {
    isolate->Dispose();
  }
}

bool V8Controller::init(const std::string& execPath)
{
  if (!context.IsEmpty()) {
    return true;
  }

  V8Platform::init(execPath);

  if (isolate == nullptr) {
    allocator.reset(v8::ArrayBuffer::Allocator::NewDefaultAllocator());

    v8::Isolate::CreateParams params;
    params.array_buffer_allocator = allocator.get();

    isolate = v8::Isolate::New(params);
  }

  const v8::Isolate::Scope isolateScope{isolate};
  const v8::HandleScope handleScope{isolate};
  const auto ctx = v8::Context::New(isolate);

  if (ctx.IsEmpty() || !V8Console::install(ctx)) {
    LOGE("Failed to create the V8 context");
    return false;
  }

  context.Reset(isolate, ctx);

  return true;
}

V8Controller::result V8Controller::run(const std::string& source,
                                       const std::string& name)
{
  if (context.IsEmpty()) {
    LOGE("The V8 controller is not initialized");
    return {};
  }

  const v8::Isolate::Scope isolateScope{isolate};
  const v8::HandleScope handleScope{isolate};
  const auto ctx = context.Get(isolate);
  const v8::Context::Scope contextScope{ctx};
  const v8::TryCatch tryCatch{isolate};

  const auto scriptName =
      to_v8(isolate, name).FromMaybe(v8::Local<v8::String>{});

  // The isolate parameter is gone from the ScriptOrigin of the newer V8.
#if V8_MAJOR_VERSION < 12
  v8::ScriptOrigin origin{isolate, scriptName};
#else
  v8::ScriptOrigin origin{scriptName};
#endif

  v8::Local<v8::String> code;
  v8::Local<v8::Script> script;
  v8::Local<v8::Value> value;

  if (!to_v8(isolate, source).ToLocal(&code) ||
      !v8::Script::Compile(ctx, code, &origin).ToLocal(&script) ||
      !script->Run(ctx).ToLocal(&value)) {
    report(isolate, tryCatch);
    return {};
  }

  const v8::String::Utf8Value text{isolate, value};

  return std::string{*text != nullptr ? *text : ""};
}

V8Controller::V8ControllerPtr V8Controller::create()
{
  return std::make_shared<V8Controller>();
}

}  // namespace v8i
