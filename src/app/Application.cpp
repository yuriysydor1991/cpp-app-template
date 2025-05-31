#include "src/app/Application.h"

#include <cassert>
#include <iostream>
#include <memory>

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

  actx = ctx;

  if (!connect()) {
    LOGE("Failure to connect");
    return INVALID;
  }

  assert(actx->pg_connection != nullptr);

  const std::string pgsqlDate = actx->pg_connection->get_current_date();

  LOGI("PostgreSQL' current date: " << pgsqlDate);

  return 0;
}

std::shared_ptr<pgsqli::PgSQL> Application::create_pg_conn()
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    LOGE("No valid context pointer provided");
    return {};
  }

  return std::make_shared<pgsqli::PgSQL>();
}

bool Application::connect()
{
  assert(actx != nullptr);

  actx->pg_connection = create_pg_conn();

  return actx->pg_connection != nullptr && actx->pg_connection->connect(actx);
}

}  // namespace app
