#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/mongodbcxx/MongoDBController.h"

using namespace mongodbcxxi;
using namespace app;
using namespace testing;

/**
 * The component test talks to the MongoDB server the MONGODB_* environment
 * variables point to (the localhost one by default) and skips when the server
 * is not reachable.
 */
class CTEST_MongoDBController : public Test
{
 public:
  CTEST_MongoDBController()
      : ctx{std::make_shared<ApplicationContext>(argc, argv)},
        controller{std::make_shared<MongoDBController>()}
  {
  }

  void SetUp() override
  {
    if (!controller->connect(ctx)) {
      GTEST_SKIP() << "No MongoDB server is reachable at the "
                   << (ctx->get_db_host().empty() ? "localhost"
                                                  : ctx->get_db_host())
                   << " host, see the MONGODB_* environment variables";
    }
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> ctx;
  std::shared_ptr<MongoDBController> controller;
};

TEST_F(CTEST_MongoDBController, connected_server_answers_the_ping)
{
  EXPECT_TRUE(controller->connected());
}

TEST_F(CTEST_MongoDBController, current_date_is_an_iso_date)
{
  EXPECT_THAT(controller->get_current_date(),
              MatchesRegex("[0-9]{4}-[0-9]{2}-[0-9]{2}"));
}
