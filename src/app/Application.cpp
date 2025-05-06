#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

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

  assert(actx->pg_connection != nullptr);

  std::cout << "PostgreSQL' current date: "
            << actx->pg_connection->get_current_date() << std::endl;

  return 0;
}

std::shared_ptr<pgsqli::PgSQL> Application::create_pg_conn()
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    return {};
  }

  return std::make_shared<pgsqli::PgSQL>();
}

bool Application::connect()
{
  assert(actx != nullptr);

  actx->pg_connection = create_pg_conn();

  return actx->pg_connection->connect(actx);
}

}  // namespace app
