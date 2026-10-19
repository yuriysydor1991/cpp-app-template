#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <sstream>
#include <string>

#include "src/LlamaCPP/LlamaCPPController.h"
#include "src/log/log.h"
#include "src/log/severity-macro-consts.h"

using namespace llamacppi;
using namespace testing;

/**
 * @brief Component test of the LlamaCPPController driving the real llama.cpp
 * with the real project logger.
 *
 * The tiny model of the llama.cpp own tests proves the whole chain, while the
 * model of the PROJECT_LLAMACPP_MODEL_PATH CMake variable proves the answers
 * themselves once downloaded. The errors alone are checked in the log, since
 * the builds of the lower MAX_LOG_LEVEL values drop the rest. The test cases
 * skip themselves while the models they need are not available.
 */
class CTEST_LlamaCPPController : public Test
{
 public:
  CTEST_LlamaCPPController()
  {
    std::ofstream truncating{logFile, std::ofstream::trunc};

    LOG_INIT(logFile, MACRO_LVL_TRACE, false);
  }

  /// @brief Reopens the log file to flush it, since the logger flushes the
  /// warnings and the errors alone, and gives the log written so far.
  std::string log_contents() const
  {
    LOG_INIT(logFile, MACRO_LVL_TRACE, false);

    std::stringstream contents;

    contents << std::ifstream{logFile}.rdbuf();

    return contents.str();
  }

  static bool available(const char* const path)
  {
    return std::ifstream{path}.good();
  }

  /// @brief Asks the question and gives the whole answer, the empty one on a
  /// failure.
  std::string answer_to(const std::string& question)
  {
    return controller->ask(question, {}).value_or("");
  }

  inline static constexpr const char* const TEST_MODEL =
      CTEST_LlamaCPPController_TEST_MODEL;
  inline static constexpr const char* const MODEL =
      CTEST_LlamaCPPController_MODEL;
  inline static constexpr const char* const NO_MODEL =
      " downloaded, configure with the -DENABLE_LLAMACPP_MODEL_DOWNLOAD=ON "
      "for the model";

  /// @brief Every test case gets the log of it's own, so the parallel ctest
  /// runs keep them apart.
  const std::string logFile{
      CTEST_LlamaCPPController_DATA_DIR "/" +
      std::string{UnitTest::GetInstance()->current_test_info()->name()} +
      ".log"};

  LlamaCPPControllerPtr controller{LlamaCPPController::create()};
};

TEST_F(CTEST_LlamaCPPController, an_absent_model_is_logged)
{
  EXPECT_FALSE(controller->init("an-absent-model.gguf"));

  const std::string log = log_contents();

  // The llama.cpp error comes ahead of the controller one.
  EXPECT_THAT(log, HasSubstr("error loading model"));
  EXPECT_THAT(
      log, HasSubstr("Fail to load the an-absent-model.gguf llama.cpp model"));
}

TEST_F(CTEST_LlamaCPPController, the_test_model_answers_with_no_errors)
{
  if (!available(TEST_MODEL)) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  ASSERT_TRUE(controller->init(TEST_MODEL));

  int pieces{0};

  EXPECT_TRUE(controller
                  ->ask("Once upon a time",
                        [&pieces](const auto&) { return ++pieces < 100; })
                  .has_value());
  EXPECT_THAT(log_contents(), Not(HasSubstr(" ERR ")));
}

TEST_F(CTEST_LlamaCPPController, the_question_gets_answered)
{
  if (!available(MODEL)) {
    GTEST_SKIP() << "No " << MODEL << NO_MODEL;
  }

  ASSERT_TRUE(controller->init(MODEL));

  EXPECT_THAT(
      answer_to("What is the capital of France? Answer with a single word."),
      HasSubstr("Paris"));
}

TEST_F(CTEST_LlamaCPPController, the_ukrainian_question_gets_answered)
{
  if (!available(MODEL)) {
    GTEST_SKIP() << "No " << MODEL << NO_MODEL;
  }

  ASSERT_TRUE(controller->init(MODEL));

  EXPECT_THAT(answer_to("Яка столиця України? Відповідай одним словом."),
              HasSubstr("Київ"));
}

TEST_F(CTEST_LlamaCPPController, the_conversation_is_remembered)
{
  if (!available(MODEL)) {
    GTEST_SKIP() << "No " << MODEL << NO_MODEL;
  }

  ASSERT_TRUE(controller->init(MODEL));

  ASSERT_THAT(answer_to("Remember the number 7. Reply with OK alone."),
              Not(IsEmpty()));
  EXPECT_THAT(answer_to("Which number did I ask you to remember? Reply with "
                        "the digit alone."),
              HasSubstr("7"));
}
