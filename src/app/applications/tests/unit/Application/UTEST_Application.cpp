#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/V8/V8Controller.h"
#include "src/app/applications/Application.h"

using namespace app;
using namespace v8i;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() override { V8Controller::onMockCreate = nullptr; }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->get_errors().empty());

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_Application, runs_the_hello_script_by_the_v8)
{
  MockFunction<void(V8Controller&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .WillOnce(Invoke([](V8Controller& instance) {
        InSequence initFirst;

        EXPECT_CALL(instance, init(std::string{}));
        EXPECT_CALL(instance,
                    run(HasSubstr("console.log(\"Hello, V8! Insert your "
                                  "JavaScript code here!\")"),
                        "main.js"));
      }));

  V8Controller::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, failed_init_runs_no_script)
{
  V8Controller::onMockCreate = [](V8Controller& instance) {
    EXPECT_CALL(instance, init(_)).WillOnce(Return(false));
    EXPECT_CALL(instance, run(_, _)).Times(0);
  };

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, failed_script_fails_the_run)
{
  V8Controller::onMockCreate = [](V8Controller& instance) {
    EXPECT_CALL(instance, run(_, _)).WillOnce(Return(V8Controller::result{}));
  };

  EXPECT_NE(app->run(appCtx), 0);
}
