#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUSCXXCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUSCXXCONTROLLER_CLASS_H

#include <memory>

#include <sdbus-c++/sdbus-c++.h>

#include "src/app/ApplicationContext.h"
#include "src/sdbuscxx/server-objects/IDBusServerObject.h"

namespace sdbuscxxi
{

/**
 * @brief Owns the bus connection life cycle and runs the simple D-Bus server:
 * it exports the default server object, requests its well known name and enters
 * the bus event loop.
 */
class SDBusCxxController
{
 public:
  using SDBusCxxControllerPtr = std::shared_ptr<SDBusCxxController>;

  virtual ~SDBusCxxController() = default;
  SDBusCxxController() = default;

  /**
   * @brief Sets up and runs the D-Bus server. Blocks in the bus event loop
   * until the connection leaves it (e.g. on process termination).
   *
   * @param ctx A filled application context.
   *
   * @return Returns false on any setup error. On success returns true once the
   * event loop has been left.
   */
  virtual bool run(std::shared_ptr<app::ApplicationContext> ctx);

  static SDBusCxxControllerPtr create();

 protected:
  virtual bool init();
  virtual bool inited();

  std::shared_ptr<app::ApplicationContext> appctx;

 private:
  bool serve();

  std::unique_ptr<sdbus::IConnection> conn;
  IDBusServerObjectPtr serverObject;
  std::unique_ptr<sdbus::IObject> object;
};

using SDBusCxxControllerPtr = SDBusCxxController::SDBusCxxControllerPtr;

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUSCXXCONTROLLER_CLASS_H
