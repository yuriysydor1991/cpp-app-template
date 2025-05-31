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

  ctx->dbconn = create_db_controller(ctx);

  if (!ctx->dbconn->connect(ctx)) {
    LOGE("Fail to connect to the SQLite database");
    return INVALID;
  }

  LOGI("SQLite3Cpp date: " << ctx->dbconn->get_current_date());

  return 0;
}

std::shared_ptr<sqlite3i::SQLiteController> Application::create_db_controller(
    [[maybe_unused]] std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  return std::make_shared<sqlite3i::SQLiteController>();
}

}  // namespace app
