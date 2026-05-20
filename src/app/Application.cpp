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

  assert(actx->db_connection != nullptr);

  const std::string firebirdDate = actx->db_connection->get_current_date();

  LOGI("Firebird' current date: " << firebirdDate);

  return 0;
}

std::shared_ptr<firebirdi::Firebird> Application::create_db_conn()
{
  assert(actx != nullptr);

  if (actx == nullptr) {
    LOGE("No valid context pointer provided");
    return {};
  }

  return std::make_shared<firebirdi::Firebird>();
}

bool Application::connect()
{
  assert(actx != nullptr);

  actx->db_connection = create_db_conn();

  return actx->db_connection != nullptr && actx->db_connection->connect(actx);
}

}  // namespace app
