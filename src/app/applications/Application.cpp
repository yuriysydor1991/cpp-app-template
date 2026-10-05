#include "src/app/applications/Application.h"

#include <cassert>
#include <memory>

#include "src/V8/V8Controller.h"
#include "src/log/log.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  // Insert your JavaScript code here. The console object of the V8 context
  // writes into the project logger.
  static constexpr const char* const code =
      R"(console.log("Hello, V8! Insert your JavaScript code here!");)";

  auto engine = v8i::V8Controller::create();

  assert(engine != nullptr);

  if (!engine->init(ctx->get_argc() > 0 ? ctx->get_argv()[0] : "") ||
      !engine->run(code, "main.js")) {
    LOGE("Failed to run the JavaScript code by the V8 engine");
    return INVALID;
  }

  return 0;
}

}  // namespace app
