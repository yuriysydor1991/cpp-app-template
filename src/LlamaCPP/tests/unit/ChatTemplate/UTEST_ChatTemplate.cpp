#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/LlamaCPP/BuiltinChatTemplate.h"
#include "src/LlamaCPP/ChatTemplate.h"
#include "src/LlamaCPP/Gemma4ChatTemplate.h"

using namespace llamacppi;
using namespace testing;

/**
 * @brief Unit test of the ChatTemplate::create call, which picks the template
 * implementation of the Jinja chat template of a model.
 */
class UTEST_ChatTemplate : public Test
{
};

TEST_F(UTEST_ChatTemplate, no_model_template_gives_the_builtin_one)
{
  EXPECT_NE(std::dynamic_pointer_cast<BuiltinChatTemplate>(
                ChatTemplate::create(nullptr)),
            nullptr);
}

TEST_F(UTEST_ChatTemplate, a_known_model_template_gives_the_builtin_one)
{
  EXPECT_NE(std::dynamic_pointer_cast<BuiltinChatTemplate>(
                ChatTemplate::create("{{ '<|im_start|>' + role }}")),
            nullptr);
}

TEST_F(UTEST_ChatTemplate, the_gemma_4_template_gives_the_gemma_4_one)
{
  EXPECT_NE(std::dynamic_pointer_cast<Gemma4ChatTemplate>(
                ChatTemplate::create("{{ '<|turn>' + role }}")),
            nullptr);
}

TEST_F(UTEST_ChatTemplate, an_unknown_model_template_gives_none)
{
  EXPECT_EQ(ChatTemplate::create("{{ unknown }}"), nullptr);
}
