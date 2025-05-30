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

  ctx->db_connection = create_db_controller();

  assert(ctx->db_connection != nullptr);

  if (ctx->db_connection == nullptr || !ctx->db_connection->connect(ctx)) {
    return INVALID;
  }

  const std::string mongoDBDate = ctx->db_connection->get_current_date();

  if (mongoDBDate.empty()) {
    return INVALID;
  }

  std::cout << "The MongoDB current date:" << mongoDBDate << std::endl;

  return 0;
}

std::shared_ptr<mongodbcxxi::MongoDBController>
Application::create_db_controller()
{
  return std::make_shared<mongodbcxxi::MongoDBController>();
}

}  // namespace app
