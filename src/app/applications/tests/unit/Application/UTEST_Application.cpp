#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <string>
#include <vector>

#include "project-global-decls.h"
#include "src/WhisperCPP/WhisperController.h"
#include "src/app/applications/Application.h"

using namespace app;
using namespace whisperi;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() override { WhisperController::onMockCreate = nullptr; }

  /// @brief Makes the given mocked controller hear the given texts one by one
  /// and raises the stop flag of the context along with the last one, the
  /// way the Ctrl+C keys do.
  void hear(WhisperController& whisper,
            const std::vector<WhisperController::result>& texts)
  {
    auto& listening = EXPECT_CALL(whisper, listen());

    for (std::size_t call = 0U; call < texts.size(); ++call) {
      listening.WillOnce(
          Invoke([this, text = texts[call], last = call + 1U == texts.size()] {
            appCtx->set_stop(last);
            return text;
          }));
    }
  }

  inline static const std::string MODEL_PATH{"/tmp/a-model.bin"};

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  WhisperController::onMockCreate = [this](WhisperController& whisper) {
    hear(whisper, {""});
  };

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->get_errors().empty());

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
}

TEST_F(UTEST_Application, loads_the_default_model_without_the_parameter)
{
  WhisperController::onMockCreate = [this](WhisperController& whisper) {
    EXPECT_CALL(whisper, init(project_decls::PROJECT_WHISPER_MODEL_PATH,
                              project_decls::PROJECT_WHISPER_LANGUAGE));
    hear(whisper, {""});
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, loads_the_model_of_the_parameter)
{
  appCtx->set_model_path(MODEL_PATH);

  WhisperController::onMockCreate = [this](WhisperController& whisper) {
    EXPECT_CALL(whisper,
                init(MODEL_PATH, project_decls::PROJECT_WHISPER_LANGUAGE));
    hear(whisper, {""});
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, failed_init_listens_to_nothing)
{
  WhisperController::onMockCreate = [](WhisperController& whisper) {
    EXPECT_CALL(whisper, init(_, _)).WillOnce(Return(false));
    EXPECT_CALL(whisper, listen()).Times(0);
  };

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, stopped_context_listens_to_nothing)
{
  appCtx->set_stop(true);

  WhisperController::onMockCreate = [](WhisperController& whisper) {
    EXPECT_CALL(whisper, listen()).Times(0);
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, listens_till_the_stop)
{
  WhisperController::onMockCreate = [this](WhisperController& whisper) {
    hear(whisper, {"Hello", "", "world"});
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, failed_listening_fails_the_run)
{
  WhisperController::onMockCreate = [](WhisperController& whisper) {
    EXPECT_CALL(whisper, listen())
        .WillOnce(Return(WhisperController::result{}));
  };

  EXPECT_NE(app->run(appCtx), 0);
}
