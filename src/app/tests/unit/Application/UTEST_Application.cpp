#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/Application.h"

using namespace app;
using namespace testing;
using namespace firebirdi;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application()
  {
    Firebird::onMockCreate = nullptr;
    app.reset();
    appCtx.reset();
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  static const std::string random_date{"2025-05-07"};

  MockFunction<void(Firebird&)> firebirdEnsurer;

  EXPECT_CALL(firebirdEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](Firebird& instance) {
        EXPECT_CALL(instance, connect(_)).Times(1).WillOnce(Return(true));
        EXPECT_CALL(instance, get_current_date)
            .Times(1)
            .WillOnce(Return(random_date));
      }));

  Firebird::onMockCreate = firebirdEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, failure_to_connect)
{
  static const std::string random_date{"2025-05-07"};

  MockFunction<void(Firebird&)> firebirdEnsurer;

  EXPECT_CALL(firebirdEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](Firebird& instance) {
        EXPECT_CALL(instance, connect(_)).Times(1).WillOnce(Return(false));
        EXPECT_CALL(instance, get_current_date).Times(0);
      }));

  Firebird::onMockCreate = firebirdEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}
