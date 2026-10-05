#include "src/V8/V8Console.h"

#include <v8.h>

#include <array>
#include <string>
#include <utility>

#include "src/log/log.h"

namespace v8i
{

bool V8Console::install(v8::Local<v8::Context> context)
{
  using logger::ILogger;

  static const std::array<std::pair<const char*, unsigned short>, 6U> methods{{
      {"log", ILogger::LVL_INFO},
      {"info", ILogger::LVL_INFO},
      {"warn", ILogger::LVL_WARNING},
      {"error", ILogger::LVL_ERROR},
      {"debug", ILogger::LVL_DEBUG},
      {"trace", ILogger::LVL_TRACE},
  }};

  auto* isolate = context->GetIsolate();
  const v8::Context::Scope contextScope{context};
  const auto console = v8::Object::New(isolate);

  for (const auto& [name, level] : methods) {
    const auto data = v8::Integer::NewFromUnsigned(isolate, level);
    v8::Local<v8::Function> method;

    if (!v8::FunctionTemplate::New(isolate, print, data)
             ->GetFunction(context)
             .ToLocal(&method) ||
        !console
             ->Set(context,
                   v8::String::NewFromUtf8(isolate, name).ToLocalChecked(),
                   method)
             .FromMaybe(false)) {
      return false;
    }
  }

  return context->Global()
      ->Set(context, v8::String::NewFromUtf8Literal(isolate, "console"),
            console)
      .FromMaybe(false);
}

void V8Console::print(const v8::FunctionCallbackInfo<v8::Value>& info)
{
  auto* isolate = info.GetIsolate();
  const auto level =
      static_cast<unsigned short>(info.Data().As<v8::Uint32>()->Value());
  std::string message;

  for (int i = 0; i < info.Length(); ++i) {
    const v8::String::Utf8Value text{isolate, info[i]};

    message.append(i > 0 ? " " : "").append(*text != nullptr ? *text : "");
  }

  const auto trace = v8::StackTrace::CurrentStackTrace(isolate, 1);

  if (trace->GetFrameCount() == 0) {
    LOG_REAL_LOGGER()->log(level, message);
    return;
  }

  const auto frame = trace->GetFrame(isolate, 0);
  const v8::String::Utf8Value script{isolate, frame->GetScriptName()};

  LOG_REAL_LOGGER()->log(level, *script != nullptr ? *script : "",
                         frame->GetLineNumber(), message);
}

}  // namespace v8i
