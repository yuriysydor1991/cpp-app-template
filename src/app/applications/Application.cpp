#include "src/app/applications/Application.h"

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

  assert(actx->get_pg_connection() != nullptr);

  const std::string pgsqlDate = actx->get_pg_connection()->get_current_date();

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

  actx->set_pg_connection(create_pg_conn());

  return actx->get_pg_connection() != nullptr &&
         actx->get_pg_connection()->connect(actx);
}

}  // namespace app
