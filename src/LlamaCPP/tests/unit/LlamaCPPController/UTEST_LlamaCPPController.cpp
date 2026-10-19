#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

#include "src/LlamaCPP/LlamaCPPController.h"

using namespace llamacppi;
using namespace testing;

/**
 * @brief Unit test of the LlamaCPPController over the real llama.cpp with the
 * tiny model of the TinyStories, the one the llama.cpp own tests run, which
 * the configure downloads. The model has no chat template, so it gets the
 * ChatML one, and continues the prompt with a story of no sense. The test
 * cases needing the model skip themselves while it is not downloaded.
 */
class UTEST_LlamaCPPController : public Test
{
 public:
  static bool has_test_model() { return std::ifstream{TEST_MODEL}.good(); }

  /// @brief Asks the question, collecting the pieces of the answer, and stops
  /// the answer after the given count of them.
  LlamaCPPController::result ask(const std::string& question,
                                 const std::size_t maxPieces = 100U)
  {
    pieces.clear();

    return controller->ask(question, [this, maxPieces](const auto& piece) {
      pieces.push_back(piece);
      return pieces.size() < maxPieces;
    });
  }

  std::string heard() const
  {
    return std::accumulate(pieces.cbegin(), pieces.cend(), std::string{});
  }

  inline static constexpr const char* const TEST_MODEL =
      UTEST_LlamaCPPController_MODEL;
  inline static constexpr const char* const ABSENT_MODEL =
      "an-absent-model.gguf";
  inline static const std::string QUESTION{
      "Tell me a long story about a little cat, a big dog and their friends "
      "in the park."};

  LlamaCPPControllerPtr controller{LlamaCPPController::create()};
  std::vector<std::string> pieces;
};

TEST_F(UTEST_LlamaCPPController, create_gives_an_instance)
{
  EXPECT_NE(LlamaCPPController::create(), nullptr);
}

TEST_F(UTEST_LlamaCPPController, nothing_is_answered_before_the_init)
{
  EXPECT_FALSE(ask(QUESTION).has_value());
  EXPECT_TRUE(pieces.empty());
}

TEST_F(UTEST_LlamaCPPController, an_absent_model_fails_the_init)
{
  EXPECT_FALSE(controller->init(ABSENT_MODEL));
  EXPECT_FALSE(ask(QUESTION).has_value());
}

TEST_F(UTEST_LlamaCPPController, the_answer_comes_piece_by_piece)
{
  if (!has_test_model()) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  ASSERT_TRUE(controller->init(TEST_MODEL));

  const auto answer = ask(QUESTION);

  ASSERT_TRUE(answer.has_value());
  EXPECT_FALSE(pieces.empty());
  EXPECT_EQ(*answer, heard());
}

TEST_F(UTEST_LlamaCPPController, the_handler_stops_the_answer)
{
  if (!has_test_model()) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  ASSERT_TRUE(controller->init(TEST_MODEL));

  const auto answer = ask(QUESTION, 1U);

  ASSERT_TRUE(answer.has_value());
  EXPECT_LE(pieces.size(), 1U);
  EXPECT_EQ(*answer, heard());
}

TEST_F(UTEST_LlamaCPPController, an_empty_handler_leaves_the_answer_whole)
{
  if (!has_test_model()) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  ASSERT_TRUE(controller->init(TEST_MODEL));

  EXPECT_TRUE(controller->ask(QUESTION, {}).has_value());
}

TEST_F(UTEST_LlamaCPPController, the_conversation_outgrows_the_context)
{
  if (!has_test_model()) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  ASSERT_TRUE(controller->init(TEST_MODEL));

  // The questions alone take more than the 2048 tokens of the model context.
  for (int question = 0; question < 50; ++question) {
    EXPECT_TRUE(ask(QUESTION).has_value()) << question;
  }
}

TEST_F(UTEST_LlamaCPPController, a_question_beyond_the_context_fails)
{
  if (!has_test_model()) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  ASSERT_TRUE(controller->init(TEST_MODEL));

  std::string question;

  for (int sentence = 0; sentence < 100; ++sentence) {
    question += QUESTION;
  }

  EXPECT_FALSE(ask(question).has_value());
  EXPECT_TRUE(pieces.empty());

  // The controller answers the next question all the same.
  EXPECT_TRUE(ask(QUESTION).has_value());
}

TEST_F(UTEST_LlamaCPPController, a_reloaded_model_starts_a_new_conversation)
{
  if (!has_test_model()) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  ASSERT_TRUE(controller->init(TEST_MODEL));
  EXPECT_TRUE(ask(QUESTION).has_value());

  ASSERT_TRUE(controller->init(TEST_MODEL));
  EXPECT_TRUE(ask(QUESTION).has_value());
}

TEST_F(UTEST_LlamaCPPController, a_failed_reload_leaves_no_model)
{
  if (!has_test_model()) {
    GTEST_SKIP() << "No " << TEST_MODEL << " test model downloaded";
  }

  ASSERT_TRUE(controller->init(TEST_MODEL));
  EXPECT_FALSE(controller->init(ABSENT_MODEL));

  EXPECT_FALSE(ask(QUESTION).has_value());
}
