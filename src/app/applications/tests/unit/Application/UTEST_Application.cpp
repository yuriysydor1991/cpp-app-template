#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <opencv2/core.hpp>

#include "project-global-decls.h"
#include "src/MoCap/MotionCapture.h"
#include "src/app/CMDParamNames.h"
#include "src/app/applications/Application.h"

using namespace app;
using namespace mocap;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  using poses = IPoseEstimator::poses;

  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() override { MotionCapture::onMockCreate = nullptr; }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  ApplicationContextPtr appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, captures_the_default_camera_with_the_default_model)
{
  MotionCapture::onMockCreate = [](MotionCapture& capture) {
    InSequence order;

    EXPECT_CALL(capture, init(project_decls::PROJECT_POSE_MODEL))
        .WillOnce(Return(true));
    EXPECT_CALL(capture, open(CMDParamNames::DEFAULT_INPUT))
        .WillOnce(Return(true));
    EXPECT_CALL(capture, capture()).WillOnce(Return(MotionCapture::result{}));
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, captures_the_given_input_with_the_given_model)
{
  appCtx->set_input("dance.mp4");
  appCtx->set_model_path("a-model.onnx");

  MotionCapture::onMockCreate = [](MotionCapture& capture) {
    EXPECT_CALL(capture, init("a-model.onnx")).WillOnce(Return(true));
    EXPECT_CALL(capture, open("dance.mp4")).WillOnce(Return(true));
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, captures_every_frame_till_the_end_of_the_input)
{
  const poses captured{{{cv::Point3f{1.0F, 2.0F, 0.0F}, 0.5F}}, {}};

  MotionCapture::onMockCreate = [&](MotionCapture& capture) {
    EXPECT_CALL(capture, capture())
        .WillOnce(Return(captured))
        .WillOnce(Return(poses{}))
        .WillOnce(Return(MotionCapture::result{}));
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, stop_request_ends_the_capture)
{
  appCtx->set_stop(true);

  MotionCapture::onMockCreate = [](MotionCapture& capture) {
    EXPECT_CALL(capture, capture()).Times(0);
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, model_load_failure_returns_invalid)
{
  MotionCapture::onMockCreate = [](MotionCapture& capture) {
    EXPECT_CALL(capture, init(_)).WillOnce(Return(false));
    EXPECT_CALL(capture, open(_)).Times(0);
    EXPECT_CALL(capture, capture()).Times(0);
  };

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, input_open_failure_returns_invalid)
{
  MotionCapture::onMockCreate = [](MotionCapture& capture) {
    EXPECT_CALL(capture, open(_)).WillOnce(Return(false));
    EXPECT_CALL(capture, capture()).Times(0);
  };

  EXPECT_NE(app->run(appCtx), 0);
}
