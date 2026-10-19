#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "project-global-decls.h"
#include "src/LlamaCPP/LlamaCPPController.h"
#include "src/app/applications/Application.h"

using namespace app;
using namespace llamacppi;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  /// @brief The standard input of the chat is the input field, the empty one
  /// unless a test case types the questions into it.
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)},
        standardInput{std::cin.rdbuf(input.rdbuf())}
  {
  }

  ~UTEST_Application() override
  {
    LlamaCPPController::onMockCreate = nullptr;
    std::cin.rdbuf(standardInput);
    std::cin.clear();
  }

  /// @brief Makes the mocked controller answer the given question with the
  /// given pieces handed over one by one.
  static void answer_with(LlamaCPPController& llama,
                          const std::string& question,
                          const std::vector<std::string>& pieces)
  {
    EXPECT_CALL(llama, ask(question, _))
        .WillOnce([pieces](const std::string&,
                           const LlamaCPPController::piece_handler& onPiece) {
          std::string answer;

          for (const auto& piece : pieces) {
            answer += piece;

            if (!onPiece(piece)) {
              break;
            }
          }

          return LlamaCPPController::result{answer};
        });
  }

  inline static const std::string MODEL_PATH{"/tmp/a-model.gguf"};
  inline static const std::string QUESTION{"Яка столиця України?"};

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
  std::istringstream input;
  std::streambuf* const standardInput;
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

TEST_F(UTEST_Application, loads_the_default_model_without_the_parameter)
{
  LlamaCPPController::onMockCreate = [](LlamaCPPController& llama) {
    EXPECT_CALL(llama, init(project_decls::PROJECT_LLAMACPP_MODEL_PATH));
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, loads_the_model_of_the_parameter)
{
  appCtx->set_model_path(MODEL_PATH);

  LlamaCPPController::onMockCreate = [](LlamaCPPController& llama) {
    EXPECT_CALL(llama, init(MODEL_PATH));
  };

  EXPECT_EQ(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, failed_init_asks_nothing)
{
  appCtx->set_question(QUESTION);

  LlamaCPPController::onMockCreate = [](LlamaCPPController& llama) {
    EXPECT_CALL(llama, init(_)).WillOnce(Return(false));
    EXPECT_CALL(llama, ask(_, _)).Times(0);
  };

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, prints_the_answer_of_the_question_parameter)
{
  appCtx->set_question(QUESTION);
  input.str("an ignored question\n");

  LlamaCPPController::onMockCreate = [](LlamaCPPController& llama) {
    answer_with(llama, QUESTION, {"Ки", "їв"});
  };

  testing::internal::CaptureStdout();

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_EQ(testing::internal::GetCapturedStdout(), "Київ\n");
}

TEST_F(UTEST_Application, failed_answer_fails_the_run)
{
  appCtx->set_question(QUESTION);

  LlamaCPPController::onMockCreate = [](LlamaCPPController& llama) {
    EXPECT_CALL(llama, ask(QUESTION, _))
        .WillOnce(Return(LlamaCPPController::result{}));
  };

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, answers_the_typed_questions_line_by_line)
{
  input.str("first\n\nsecond\n");

  LlamaCPPController::onMockCreate = [](LlamaCPPController& llama) {
    InSequence chat;

    answer_with(llama, "first", {"one"});
    answer_with(llama, "second", {"two"});
  };

  testing::internal::CaptureStdout();

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_THAT(testing::internal::GetCapturedStdout(), EndsWith("one\ntwo\n"));
}

TEST_F(UTEST_Application, failed_chat_answer_fails_the_run)
{
  input.str("first\nsecond\n");

  LlamaCPPController::onMockCreate = [](LlamaCPPController& llama) {
    EXPECT_CALL(llama, ask("first", _))
        .WillOnce(Return(LlamaCPPController::result{}));
    EXPECT_CALL(llama, ask("second", _)).Times(0);
  };

  EXPECT_NE(app->run(appCtx), 0);
}

TEST_F(UTEST_Application, the_stop_flag_stops_the_answer_and_the_chat)
{
  input.str("first\nsecond\n");

  LlamaCPPController::onMockCreate = [this](LlamaCPPController& llama) {
    EXPECT_CALL(llama, ask("first", _))
        .WillOnce([this](const std::string&,
                         const LlamaCPPController::piece_handler& onPiece) {
          EXPECT_TRUE(onPiece("one"));
          appCtx->set_stop(true);
          EXPECT_FALSE(onPiece(" two"));
          return LlamaCPPController::result{"one two"};
        });
    EXPECT_CALL(llama, ask("second", _)).Times(0);
  };

  testing::internal::CaptureStdout();

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_THAT(testing::internal::GetCapturedStdout(), EndsWith("one two\n"));
}
