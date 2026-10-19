#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "src/LlamaCPP/BuiltinChatTemplate.h"
#include "src/LlamaCPP/ChatTemplate.h"

using namespace llamacppi;
using namespace testing;

/**
 * @brief Unit test of the BuiltinChatTemplate over the real llama.cpp, which
 * tells it's built in templates by the markers of the Jinja ones.
 */
class UTEST_BuiltinChatTemplate : public Test
{
 public:
  inline static const ChatTemplate::messages CONVERSATION{
      {"user", "Hi"}, {"assistant", "Hello!"}, {"user", "Bye"}};
};

TEST_F(UTEST_BuiltinChatTemplate, no_model_template_formats_the_chatml)
{
  EXPECT_EQ(BuiltinChatTemplate{nullptr}.apply(CONVERSATION),
            "<|im_start|>user\nHi<|im_end|>\n"
            "<|im_start|>assistant\nHello!<|im_end|>\n"
            "<|im_start|>user\nBye<|im_end|>\n"
            "<|im_start|>assistant\n");
}

TEST_F(UTEST_BuiltinChatTemplate, the_gemma_template_is_known)
{
  EXPECT_EQ(
      BuiltinChatTemplate{"{{ '<start_of_turn>' + role }}"}.apply(CONVERSATION),
      "<start_of_turn>user\nHi<end_of_turn>\n"
      "<start_of_turn>model\nHello!<end_of_turn>\n"
      "<start_of_turn>user\nBye<end_of_turn>\n"
      "<start_of_turn>model\n");
}

TEST_F(UTEST_BuiltinChatTemplate, an_unknown_template_formats_nothing)
{
  EXPECT_FALSE(
      BuiltinChatTemplate{"{{ unknown }}"}.apply(CONVERSATION).has_value());
  EXPECT_FALSE(BuiltinChatTemplate{"{{ '<|turn>' + role }}"}
                   .apply(CONVERSATION)
                   .has_value());
}

TEST_F(UTEST_BuiltinChatTemplate, a_long_conversation_formats_whole)
{
  const std::string text(100000U, 'a');

  EXPECT_THAT(BuiltinChatTemplate{nullptr}.apply({{"user", text}}),
              Optional(HasSubstr(text)));
}
