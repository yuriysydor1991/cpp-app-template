#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "project-global-decls.h"
#include "src/DarknetXX/DarknetXXController.h"
#include "src/DarknetXX/weights/Dxxwjz1Weights.h"
#include "src/DarknetXX/weights/OrigWeights.h"
#include "src/app/applications/Application.h"

using namespace app;
using namespace darknetxxi;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() override { DarknetXXController::onMockCreate = nullptr; }

  /// @brief Matches the weights file of the given format and path.
  template <class Weights>
  static auto weights_of(const std::string& path)
  {
    return WhenDynamicCastTo<const Weights&>(
        Property(&NetworkWeights::path, path));
  }

  inline static const std::string CFG{"/tmp/a.cfg"};
  inline static const std::string WEIGHTS{"/tmp/a.weights"};
  inline static const std::string DXXWJZ1{"/tmp/a.dxxwjz1"};
  inline static const std::string NAMES{"/tmp/a.names"};
  inline static const std::string IMAGE{"/tmp/an-image.jpg"};

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

TEST_F(UTEST_Application, detects_with_the_defaults_without_the_parameters)
{
  DarknetXXController::onMockCreate = [](DarknetXXController& darknetxx) {
    EXPECT_CALL(darknetxx,
                init(project_decls::PROJECT_DARKNETXX_CFG_PATH,
                     weights_of<OrigWeights>(
                         project_decls::PROJECT_DARKNETXX_WEIGHTS_PATH),
                     project_decls::PROJECT_DARKNETXX_NAMES_PATH));
    EXPECT_CALL(darknetxx, detect(project_decls::PROJECT_DARKNETXX_IMAGE_PATH));
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, detects_with_the_files_of_the_parameters)
{
  appCtx->set_cfg_path(CFG);
  appCtx->set_weights_path(WEIGHTS);
  appCtx->set_names_path(NAMES);
  appCtx->set_image_path(IMAGE);

  DarknetXXController::onMockCreate = [](DarknetXXController& darknetxx) {
    EXPECT_CALL(darknetxx, init(CFG, weights_of<OrigWeights>(WEIGHTS), NAMES));
    EXPECT_CALL(darknetxx, detect(IMAGE));
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, loads_the_dxxwjz1_weights_of_the_parameter)
{
  appCtx->set_dxxwjz1_path(DXXWJZ1);

  DarknetXXController::onMockCreate = [](DarknetXXController& darknetxx) {
    EXPECT_CALL(darknetxx, init(project_decls::PROJECT_DARKNETXX_CFG_PATH,
                                weights_of<Dxxwjz1Weights>(DXXWJZ1),
                                project_decls::PROJECT_DARKNETXX_NAMES_PATH));
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, both_weights_files_fail_the_run)
{
  appCtx->set_weights_path(WEIGHTS);
  appCtx->set_dxxwjz1_path(DXXWJZ1);

  DarknetXXController::onMockCreate = [](DarknetXXController& darknetxx) {
    EXPECT_CALL(darknetxx, init(_, _, _)).Times(0);
    EXPECT_CALL(darknetxx, detect(_)).Times(0);
  };

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, failed_init_detects_nothing)
{
  DarknetXXController::onMockCreate = [](DarknetXXController& darknetxx) {
    EXPECT_CALL(darknetxx, init(_, _, _)).WillOnce(Return(false));
    EXPECT_CALL(darknetxx, detect(_)).Times(0);
  };

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, failed_detection_fails_the_run)
{
  DarknetXXController::onMockCreate = [](DarknetXXController& darknetxx) {
    EXPECT_CALL(darknetxx, detect(_))
        .WillOnce(Return(DarknetXXController::detections{}));
  };

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, detected_objects_end_the_run)
{
  DarknetXXController::onMockCreate = [](DarknetXXController& darknetxx) {
    EXPECT_CALL(darknetxx, detect(_))
        .WillOnce(Return(DarknetXXController::detections{
            {{"dog", 0.98F, 1, 2, 3, 4}, {"bicycle", 0.5F, 5, 6, 7, 8}}}));
  };

  EXPECT_EQ(app->run(appCtx), 0);
}
