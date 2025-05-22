#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "src/mysqlcppconn/MySQLController.h"

namespace app
{

int Application::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    return INVALID;
  }

  actx = ctx;

  if (!connect()) {
    return INVALID;
  }

  std::cout << "MySQL' current date: " << actx->mysqlconn->get_current_date()
            << std::endl;

  return 0;
}

bool Application::connect()
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    return false;
  }

  actx->mysqlconn = create_db_controller();

  assert(actx->mysqlconn != nullptr);

  return actx->mysqlconn != nullptr;
}

std::shared_ptr<mysqli::MySQLController> Application::create_db_controller()
{
  return std::make_shared<mysqli::MySQLController>();
}

}  // namespace app
