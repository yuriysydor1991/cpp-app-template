#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/CFITSIO/CFITSIOController.h"
#include "src/app/applications/Application.h"

using namespace app;
using namespace cfitsioi;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() override { CFITSIOController::onMockCreate = nullptr; }

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

TEST_F(UTEST_Application, performs_the_fits_round_trip)
{
  MockFunction<void(CFITSIOController&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](CFITSIOController& instance) {
        InSequence roundTrip;

        EXPECT_CALL(instance, create_image(_, _)).WillOnce(Return(true));
        EXPECT_CALL(instance, write(_)).WillOnce(Return(true));
        EXPECT_CALL(instance, write_keyword(_, _, _)).WillOnce(Return(true));
        EXPECT_CALL(instance, close()).WillOnce(Return(true));
        EXPECT_CALL(instance, open(_, _)).WillOnce(Return(true));
        EXPECT_CALL(instance, read()).Times(1);
        EXPECT_CALL(instance, get_image_size()).Times(1);
        EXPECT_CALL(instance, read_keyword(_)).Times(1);
      }));

  CFITSIOController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, controller_failure_returns_invalid)
{
  MockFunction<void(CFITSIOController&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([](CFITSIOController& instance) {
        EXPECT_CALL(instance, create_image(_, _)).WillOnce(Return(false));
        EXPECT_CALL(instance, open(_, _)).Times(0);
      }));

  CFITSIOController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_NE(app->run(appCtx), 0);
}
