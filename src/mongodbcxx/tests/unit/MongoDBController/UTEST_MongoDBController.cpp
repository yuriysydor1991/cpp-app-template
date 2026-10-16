#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <string>

#include "MongoDBControllerSpy.h"
#include "src/app/ApplicationContext.h"
#include "src/mongodbcxx/MongoDBController.h"
#include "src/mongodbcxx/mongocxx-includes.h"

using namespace mongodbcxxi;
using namespace app;
using namespace testing;
using namespace bsoncxx::builder;

class UTEST_MongoDBController : public Test
{
 public:
  using DBJsonRes = MongoDBController::DBJsonRes;

  UTEST_MongoDBController()
      : ctx{std::make_shared<ApplicationContext>(argc, argv)},
        spy{std::make_shared<NiceMock<MongoDBControllerSpy>>()}
  {
    setenv("TZ", "UTC", 1);
    tzset();
  }

  static std::shared_ptr<DBJsonRes> ok_answer()
  {
    return std::make_shared<DBJsonRes>(stream::document{} << "ok" << 1.0
                                                          << stream::finalize);
  }

  static std::shared_ptr<DBJsonRes> date_answer()
  {
    // 2025-05-31T12:00:00Z
    const bsoncxx::types::b_date date{std::chrono::milliseconds{1748692800000}};

    return std::make_shared<DBJsonRes>(stream::document{} << "localTime" << date
                                                          << "ok" << 1.0
                                                          << stream::finalize);
  }

  static bool is_command(const MongoDBController::JsonDoc& doc,
                         const std::string& command)
  {
    return static_cast<bool>(doc.view()[command]);
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> ctx;
  std::shared_ptr<NiceMock<MongoDBControllerSpy>> spy;
};

TEST_F(UTEST_MongoDBController, null_context_fails_to_connect)
{
  EXPECT_CALL(*spy, execute_query(_)).Times(0);

  EXPECT_FALSE(spy->connect(nullptr));
}

TEST_F(UTEST_MongoDBController, connect_pings_the_server)
{
  EXPECT_CALL(*spy, execute_query(Truly([](const auto& doc) {
    return is_command(doc, "ping");
  }))).WillOnce(Return(ok_answer()));

  EXPECT_TRUE(spy->connect(ctx));
}

TEST_F(UTEST_MongoDBController, connect_fails_without_the_ping_answer)
{
  EXPECT_CALL(*spy, execute_query(_)).WillOnce(Return(nullptr));

  EXPECT_FALSE(spy->connect(ctx));
}

TEST_F(UTEST_MongoDBController, invalid_connection_string_fails_to_connect)
{
  ctx->set_db_tls("maybe");

  EXPECT_CALL(*spy, execute_query(_)).Times(0);

  EXPECT_FALSE(spy->connect(ctx));
}

TEST_F(UTEST_MongoDBController, current_date_is_the_server_local_time)
{
  EXPECT_CALL(*spy, execute_query(_))
      .WillRepeatedly(Invoke([](const MongoDBController::JsonDoc& doc) {
        return is_command(doc, "hello") ? date_answer() : ok_answer();
      }));

  ASSERT_TRUE(spy->connect(ctx));

  EXPECT_EQ(spy->get_current_date(), "2025-05-31");
}

TEST_F(UTEST_MongoDBController, answer_without_the_local_time_gives_no_date)
{
  EXPECT_CALL(*spy, execute_query(_)).WillRepeatedly(Return(ok_answer()));

  ASSERT_TRUE(spy->connect(ctx));

  EXPECT_TRUE(spy->get_current_date().empty());
}

TEST_F(UTEST_MongoDBController, lost_connection_gives_no_date)
{
  EXPECT_CALL(*spy, execute_query(_))
      .WillOnce(Return(ok_answer()))
      .WillRepeatedly(Return(nullptr));

  ASSERT_TRUE(spy->connect(ctx));

  EXPECT_TRUE(spy->get_current_date().empty());
}

TEST_F(UTEST_MongoDBController, context_owning_the_connection_is_released)
{
  EXPECT_CALL(*spy, execute_query(_)).WillRepeatedly(Return(ok_answer()));

  ctx->set_db_connection(spy);

  ASSERT_TRUE(spy->connect(ctx));

  const std::weak_ptr<ApplicationContext> weakCtx = ctx;
  const std::weak_ptr<MongoDBController> weakConnection = spy;

  spy.reset();
  ctx.reset();

  EXPECT_TRUE(weakCtx.expired());
  EXPECT_TRUE(weakConnection.expired());
}

TEST_F(UTEST_MongoDBController, unreachable_server_fails_to_connect)
{
  ctx->set_db_host("127.0.0.1");
  ctx->set_db_port("1");
  ctx->set_db_timeout_ms("1000");

  const auto controller = std::make_shared<MongoDBController>();

  EXPECT_FALSE(controller->connect(ctx));
  EXPECT_FALSE(controller->connected());
  EXPECT_TRUE(controller->get_current_date().empty());
}
