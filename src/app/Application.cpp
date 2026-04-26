#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/log/log.h"
#include "src/sdbuscxx/SDBusCxxController.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  sdbuscxxi::SDBusCxxControllerPtr sdbusconn = sdbuscxxi::SDBusCxxController::create();

  assert(sdbusconn != nullptr);

  if (sdbusconn == nullptr) {
    LOGE("Fail during the SDBus-c++ connection object creation");
    return INVALID;
  }

  if (!sdbusconn->run(ctx)) {
    LOGE("DBus connection object signalled about invalid state");
    return INVALID;
  }

  return 0;
}

}  // namespace app
