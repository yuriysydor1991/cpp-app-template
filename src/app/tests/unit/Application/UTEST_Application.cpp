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
        appCtx{std::make_shared<ApplicationContext>(argc, argv)},
        cascadePathHolder{"/usr/share/opencv4/haarcascades/"
                          "haarcascade_frontalface_default.xml"}
  {
  }

  ~UTEST_Application() override { OpenCVController::onMockCreate = nullptr; }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
  std::string cascadePathHolder;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit_loads_cascade_without_image)
{
  MockFunction<void(OpenCVController&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](OpenCVController& instance) {
        EXPECT_CALL(instance, load_cascade(_)).Times(1).WillOnce(Return(true));
        EXPECT_CALL(instance, get_cascade_path())
            .WillRepeatedly(ReturnRef(cascadePathHolder));
        EXPECT_CALL(instance, detect(An<const std::string&>())).Times(0);
      }));

  OpenCVController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);
  EXPECT_TRUE(appCtx->errors.empty());
}

TEST_F(UTEST_Application, normal_exit_scans_image_when_path_provided)
{
  MockFunction<void(OpenCVController&)> onMockCreateEnsurer;

  appCtx->image_path = "/tmp/face-fixture.png";

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](OpenCVController& instance) {
        EXPECT_CALL(instance, load_cascade(_)).Times(1).WillOnce(Return(true));
        EXPECT_CALL(instance, get_cascade_path())
            .WillRepeatedly(ReturnRef(cascadePathHolder));
        EXPECT_CALL(instance, detect(An<const std::string&>()))
            .Times(1)
            .WillOnce(Invoke([&](const std::string& path) {
              EXPECT_EQ(path, appCtx->image_path);
              return OpenCVController::faces_buffer{cv::Rect{1, 2, 3, 4}};
            }));
      }));

  OpenCVController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, cascade_load_failure_returns_invalid)
{
  MockFunction<void(OpenCVController&)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](OpenCVController& instance) {
        EXPECT_CALL(instance, load_cascade(_)).Times(1).WillOnce(Return(false));
        EXPECT_CALL(instance, detect(An<const std::string&>())).Times(0);
      }));

  OpenCVController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, forwards_custom_cascade_path)
{
  MockFunction<void(OpenCVController&)> onMockCreateEnsurer;

  appCtx->cascade_path = "/tmp/custom-cascade.xml";

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](OpenCVController& instance) {
        EXPECT_CALL(instance, load_cascade(_))
            .Times(1)
            .WillOnce(Invoke([&](const std::string& path) {
              EXPECT_EQ(path, appCtx->cascade_path);
              return true;
            }));
        EXPECT_CALL(instance, get_cascade_path())
            .WillRepeatedly(ReturnRef(cascadePathHolder));
      }));

  OpenCVController::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  EXPECT_EQ(app->run(appCtx), 0);
}
