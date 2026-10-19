#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/LlamaCPP/ChatTemplate.h"
#include "src/LlamaCPP/Gemma4ChatTemplate.h"

using namespace llamacppi;
using namespace testing;

/**
 * @brief Unit test of the Gemma4ChatTemplate. The expected prompts are the
 * ones the Jinja chat templates of the Gemma 4 models give with no tools and
 * no thinking, but the leading <bos> token, which the tokenizer adds.
 */
class UTEST_Gemma4ChatTemplate : public Test
{
 public:
  /// @brief The pieces of the Jinja templates the prompt depends on: the E4B
  /// model one opens the answer alone, while the 12B model one closes the
  /// thought channel of it in advance.
  inline static constexpr const char* const OPENING_TEMPLATE =
      "{{- '<|turn>model\\n' -}}";
  inline static constexpr const char* const CLOSING_TEMPLATE =
      "{{- '<|turn>model\\n' -}}{{- '<|channel>thought\\n<channel|>' -}}";

  inline static const ChatTemplate::messages CONVERSATION{
      {"user", "Remember the number 7."},
      {"assistant", "OK, I will remember it."},
      {"user", "Яка столиця України?"}};
};

TEST_F(UTEST_Gemma4ChatTemplate, the_turns_end_with_the_model_one)
{
  EXPECT_EQ(Gemma4ChatTemplate{OPENING_TEMPLATE}.apply(CONVERSATION),
            "<|turn>user\nRemember the number 7.<turn|>\n"
            "<|turn>model\nOK, I will remember it.<turn|>\n"
            "<|turn>user\nЯка столиця України?<turn|>\n"
            "<|turn>model\n");
}

TEST_F(UTEST_Gemma4ChatTemplate, the_closing_template_closes_the_thought)
{
  EXPECT_EQ(
      Gemma4ChatTemplate{CLOSING_TEMPLATE}.apply({{"user", "Hi"}}),
      "<|turn>user\nHi<turn|>\n<|turn>model\n<|channel>thought\n<channel|>");
}

TEST_F(UTEST_Gemma4ChatTemplate, the_system_message_takes_a_turn_of_its_own)
{
  EXPECT_EQ(Gemma4ChatTemplate{OPENING_TEMPLATE}.apply(
                {{"system", "Answer briefly."}, {"user", "Hi"}}),
            "<|turn>system\nAnswer briefly.<turn|>\n<|turn>user\nHi<turn|>\n"
            "<|turn>model\n");
}

TEST_F(UTEST_Gemma4ChatTemplate, the_gemma_4_templates_match)
{
  EXPECT_TRUE(Gemma4ChatTemplate::matches(OPENING_TEMPLATE));
  EXPECT_TRUE(Gemma4ChatTemplate::matches(CLOSING_TEMPLATE));
  EXPECT_FALSE(Gemma4ChatTemplate::matches("{{ '<start_of_turn>model\\n' }}"));
  EXPECT_FALSE(Gemma4ChatTemplate::matches(nullptr));
}
