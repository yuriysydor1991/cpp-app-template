#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/Application.h"
#include "src/gtkmm3/GtkmmIniter.h"

using namespace app;
using namespace Gtkmm3i;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() { GtkmmIniter::onMockCreate = nullptr; }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  MockFunction<void(GtkmmIniter & instance)> initerEnsurer;

  EXPECT_CALL(initerEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](GtkmmIniter& instance) {
        EXPECT_CALL(instance, run(appCtx)).Times(1).WillOnce(Return(0));
      }));

  GtkmmIniter::onMockCreate = initerEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, invalid_exit_status)
{
  MockFunction<void(GtkmmIniter & instance)> initerEnsurer;

  EXPECT_CALL(initerEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](GtkmmIniter& instance) {
        EXPECT_CALL(instance, run(appCtx)).Times(1).WillOnce(Return(1));
      }));

  GtkmmIniter::onMockCreate = initerEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}
