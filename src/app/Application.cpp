#include "src/app/Application.h"

#include <cassert>
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

  ctx->db_connection = create_db_controller();

  assert(ctx->db_connection != nullptr);

  if (ctx->db_connection == nullptr || !ctx->db_connection->connect(ctx)) {
    LOGE("Fail to create a new db connection");
    return INVALID;
  }

  const std::string mongoDBDate = ctx->db_connection->get_current_date();

  if (mongoDBDate.empty()) {
    LOGE("Empty current date retrieved");
    return INVALID;
  }

  LOGI("The MongoDB current date: " << mongoDBDate);

  return 0;
}

std::shared_ptr<mongodbcxxi::MongoDBController>
Application::create_db_controller()
{
  LOGT("Creating a new MongoDB controller");

  return std::make_shared<mongodbcxxi::MongoDBController>();
}

}  // namespace app
