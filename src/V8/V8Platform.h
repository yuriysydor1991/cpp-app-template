#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_V8PLATFORM_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_V8PLATFORM_CLASS_H

#include <libplatform/libplatform.h>

#include <memory>
#include <string>

/**
 * @brief The V8 JavaScript engine adaptor subsystem namespace.
 */
namespace v8i
{

/**
 * @brief The process wide V8 engine initializer.
 *
 * The V8 is initialized once per process and never again after it's disposal,
 * so the single instance lives till the process exit and disposes the V8 right
 * there, after every isolate of the V8Controller instances is gone.
 */
class V8Platform
{
 public:
  V8Platform(const V8Platform&) = delete;
  V8Platform& operator=(const V8Platform&) = delete;

  /**
   * @brief Initializes the whole V8 engine on the very first call and does
   * nothing on the later ones.
   *
   * @param execPath The executable path. The V8 builds which keep the ICU data
   * and the startup snapshot in separate files look for them next to it.
   */
  static void init(const std::string& execPath);

 private:
  explicit V8Platform(const std::string& execPath);
  ~V8Platform();

  /// @brief The platform the V8 runs it's worker threads and tasks on.
  std::unique_ptr<v8::Platform> platform;
};

}  // namespace v8i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_V8PLATFORM_CLASS_H
