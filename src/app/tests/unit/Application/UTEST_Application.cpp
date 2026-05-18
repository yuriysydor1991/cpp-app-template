#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/Application.h"
#include "src/opencv/OpenCVController.h"

using namespace app;
using namespace opencvi;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() override { OpenCVController::onMockCreate = nullptr; }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, delegates_to_opencv_controller_run)
{
  MockFunction<void(OpenCVController&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](OpenCVController& instance) {
        EXPECT_CALL(instance, run(_))
            .Times(1)
            .WillOnce(Invoke([&](OpenCVController::appctx ctx) {
              EXPECT_EQ(ctx, appCtx);
              return true;
            }));
        EXPECT_CALL(instance, face_recognition_example(_)).Times(0);
        EXPECT_CALL(instance, load_cascade(_)).Times(0);
        EXPECT_CALL(instance, detect(An<const std::string&>())).Times(0);
      }));

  OpenCVController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);
  EXPECT_TRUE(appCtx->errors.empty());
}

TEST_F(UTEST_Application, opencv_controller_run_failure_returns_invalid)
{
  MockFunction<void(OpenCVController&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](OpenCVController& instance) {
        EXPECT_CALL(instance, run(_)).Times(1).WillOnce(Return(false));
      }));

  OpenCVController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_NE(app->run(appCtx), 0);
}
