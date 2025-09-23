#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/PgSQLxx/PgSQL.h"
#include "src/app/ApplicationFactory.h"

using namespace app;
using namespace testing;
using namespace testing;
using namespace pgsqli;

class CTEST_app : public Test
{
 public:
  CTEST_app() = default;
  ~CTEST_app() { PgSQL::onMockCreate = nullptr; }

  int argc{0};
  char** argv{nullptr};

  ApplicationFactory facade;
};

TEST_F(CTEST_app, create_default_context_success)
{
  auto actx = facade.create_default_context(argc, argv);

  EXPECT_NE(actx, nullptr);
}

TEST_F(CTEST_app, create_default_arg_parser_success)
{
  auto argp = facade.create_default_arg_parser();

  EXPECT_NE(argp, nullptr);
}

TEST_F(CTEST_app, create_default_application_success)
{
  auto dapp = facade.create_default_application();

  EXPECT_NE(dapp, nullptr);
}

TEST_F(CTEST_app, create_help_printer_success)
{
  auto hpapp = facade.create_help_printer();

  EXPECT_NE(hpapp, nullptr);
}

TEST_F(CTEST_app, create_context_success)
{
  auto ctx = facade.create_context(argc, argv);

  EXPECT_NE(ctx, nullptr);
}

TEST_F(CTEST_app, create_application_success)
{
  auto actx = facade.create_default_context(argc, argv);

  EXPECT_NE(actx, nullptr);

  auto app = facade.create_application(actx);

  EXPECT_NE(app, nullptr);
}

TEST_F(CTEST_app, execute_success)
{
  static const std::string random_date{"2025-09-23"};

  MockFunction<void(PgSQL&)> pgsqlEnsurer;

  EXPECT_CALL(pgsqlEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](PgSQL& instance) {
        EXPECT_CALL(instance, connect(_)).Times(1).WillOnce(Return(true));
        EXPECT_CALL(instance, get_current_date)
            .Times(1)
            .WillOnce(Return(random_date));
      }));

  PgSQL::onMockCreate = pgsqlEnsurer.AsStdFunction();

  int status = ApplicationFactory::execute(argc, argv);

  EXPECT_EQ(status, 0);
}
