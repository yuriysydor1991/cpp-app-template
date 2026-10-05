#include "src/V8/V8Platform.h"

#include <libplatform/libplatform.h>
#include <v8.h>

#include <string>

#include "src/log/log.h"

namespace v8i
{

void V8Platform::init(const std::string& execPath)
{
  [[maybe_unused]] static const V8Platform instance{execPath};
}

V8Platform::V8Platform(const std::string& execPath)
    : platform{v8::platform::NewDefaultPlatform()}
{
  if (!v8::V8::InitializeICUDefaultLocation(execPath.c_str())) {
    LOGW("No ICU data found, the V8 internationalization is unavailable");
  }

  v8::V8::InitializeExternalStartupData(execPath.c_str());
  v8::V8::InitializePlatform(platform.get());
  v8::V8::Initialize();

  LOGD("The V8 " << v8::V8::GetVersion() << " engine is initialized");
}

V8Platform::~V8Platform()
{
  v8::V8::Dispose();
  v8::V8::DisposePlatform();
}

}  // namespace v8i
