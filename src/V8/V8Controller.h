#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_V8CONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_V8CONTROLLER_CLASS_H

#include <v8.h>

#include <memory>
#include <optional>
#include <string>

namespace v8i
{

/**
 * @brief The V8 JavaScript engine controller. It initializes the whole V8
 * engine, owns an isolate with a single context of it's own and runs the
 * JavaScript code inside of that context.
 *
 * The console object of the context writes into the project logger, see the
 * V8Console class. Nothing throws: the failures are logged and reported
 * through the return values.
 */
class V8Controller
{
 public:
  using result = std::optional<std::string>;
  using V8ControllerPtr = std::shared_ptr<V8Controller>;

  virtual ~V8Controller();
  V8Controller() = default;
  V8Controller(const V8Controller&) = delete;
  V8Controller& operator=(const V8Controller&) = delete;

  /**
   * @brief Initializes the whole V8 engine (once per process, see the
   * V8Platform class) and creates the isolate with the context to run the
   * code in. The calls after a successful one do nothing.
   *
   * @param execPath The executable path, usually the first command line
   * argument. May be empty.
   *
   * @return Returns true on success and false otherwise.
   */
  virtual bool init(const std::string& execPath);

  /**
   * @brief Compiles and runs the JavaScript code inside the context. The
   * globals the code declares stay available to the later runs.
   *
   * @param source The JavaScript code to run.
   * @param name The script name the console messages and the errors refer to.
   *
   * @return Returns the code completion value converted to a string, or
   * nothing if the controller is not initialized or the code fails to compile
   * or throws.
   */
  virtual result run(const std::string& source, const std::string& name);

  /**
   * @brief Creates a controller instance. Call the V8Controller::init method
   * before running any code.
   *
   * @return The created controller.
   */
  static V8ControllerPtr create();

 private:
  std::unique_ptr<v8::ArrayBuffer::Allocator> allocator;
  v8::Isolate* isolate{nullptr};
  v8::Global<v8::Context> context;
};

using V8ControllerPtr = V8Controller::V8ControllerPtr;

}  // namespace v8i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_V8CONTROLLER_CLASS_H
