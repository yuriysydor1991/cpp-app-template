#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_V8CONSOLE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_V8CONSOLE_CLASS_H

#include <v8.h>

#include <functional>

namespace v8i
{

class V8Console
{
 public:
  /// @brief Hand a test own mock function over, so it's expectations live and
  /// get verified within that very test.
  inline static std::function<bool()> onInstall;

  static bool install(v8::Local<v8::Context>)
  {
    return onInstall ? onInstall() : true;
  }
};

}  // namespace v8i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_V8CONSOLE_CLASS_H
