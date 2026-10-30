#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <string>
#include <vector>

#include "project-global-decls.h"
#include "src/STT/SpeechListener.h"
#include "src/app/applications/Application.h"

using namespace app;
using namespace stt;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() override { SpeechListener::onMockCreate = nullptr; }

  /// @brief Makes the given mocked controller hear the given texts one by one
  /// and raises the stop flag of the context along with the last one, the
  /// way the Ctrl+C keys do.
  void hear(SpeechListener& listener,
            const std::vector<SpeechListener::result>& texts)
  {
    auto& listening = EXPECT_CALL(listener, listen());

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
  SpeechListener::onMockCreate = [this](SpeechListener& listener) {
    hear(listener, {""});
  };

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->get_errors().empty());

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
}

TEST_F(UTEST_Application, loads_the_default_model_without_the_parameter)
{
  SpeechListener::onMockCreate = [this](SpeechListener& listener) {
    EXPECT_CALL(listener, init(project_decls::PROJECT_STT_MODEL));
    hear(listener, {""});
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, loads_the_model_of_the_parameter)
{
  appCtx->set_model_path(MODEL_PATH);

  SpeechListener::onMockCreate = [this](SpeechListener& listener) {
    EXPECT_CALL(listener, init(MODEL_PATH));
    hear(listener, {""});
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, failed_init_listens_to_nothing)
{
  SpeechListener::onMockCreate = [](SpeechListener& listener) {
    EXPECT_CALL(listener, init(_)).WillOnce(Return(false));
    EXPECT_CALL(listener, listen()).Times(0);
  };

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, stopped_context_listens_to_nothing)
{
  appCtx->set_stop(true);

  SpeechListener::onMockCreate = [](SpeechListener& listener) {
    EXPECT_CALL(listener, listen()).Times(0);
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, listens_till_the_stop)
{
  SpeechListener::onMockCreate = [this](SpeechListener& listener) {
    hear(listener, {"Hello", "", "world"});
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, failed_listening_fails_the_run)
{
  SpeechListener::onMockCreate = [](SpeechListener& listener) {
    EXPECT_CALL(listener, listen()).WillOnce(Return(SpeechListener::result{}));
  };

  EXPECT_NE(app->run(appCtx), 0);
}
