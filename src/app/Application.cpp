#include "src/app/Application.h"

#include <cassert>
#include <memory>

#include "src/log/log.h"
#include "src/mysqlcppconn/MySQLController.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid context pointer provided");
    return INVALID;
  }

  actx = ctx;

  if (!connect()) {
    LOGE("Fail to connect to the MySQL server");
    return INVALID;
  }

  LOGI("MySQL' current date: " << actx->mysqlconn->get_current_date());

  return 0;
}

bool Application::connect()
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    LOGE("No valid application context");
    return false;
  }

  actx->mysqlconn = create_db_controller();

  assert(actx->mysqlconn != nullptr);

  return actx->mysqlconn != nullptr && actx->mysqlconn->connect(actx);
}

std::shared_ptr<mysqli::MySQLController> Application::create_db_controller()
{
  return std::make_shared<mysqli::MySQLController>();
}

}  // namespace app
