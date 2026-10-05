#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_V8CONSOLE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_V8CONSOLE_CLASS_H

#include <v8.h>

namespace v8i
{

/**
 * @brief Binds the JavaScript console object to the project logger, so the
 * console.log and it's siblings write into the very same log the LOGx macros
 * do.
 *
 * The messages go to the LOG_REAL_LOGGER instance carrying the JavaScript file
 * name and line of the call instead of the C++ ones.
 */
class V8Console
{
 public:
  /**
   * @brief Replaces the console object of the given context with the logging
   * one. The log and the info methods log at the info level, while the warn,
   * the error, the debug and the trace ones log at their namesake levels.
   *
   * @param context The context to install the console object into.
   *
   * @return Returns true on success and false otherwise.
   */
  static bool install(v8::Local<v8::Context> context);

 private:
  /**
   * @brief The console methods callback. Logs the call arguments converted to
   * strings and joined by the spaces at the level the callback data holds.
   *
   * @param info The JavaScript call arguments and the callback data.
   */
  static void print(const v8::FunctionCallbackInfo<v8::Value>& info);
};

}  // namespace v8i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_V8CONSOLE_CLASS_H
