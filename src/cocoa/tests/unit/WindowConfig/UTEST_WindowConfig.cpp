#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/cocoa/helpers/WindowConfig.h"

using namespace cocoa::helpers;
using namespace testing;

class UTEST_WindowConfig : public Test
{
 public:
  WindowConfig config{"TemplateApp", "1.2.3"};
};

TEST_F(UTEST_WindowConfig, title_joins_name_and_version)
{
  EXPECT_EQ(config.title(), "TemplateApp 1.2.3");
}

TEST_F(UTEST_WindowConfig, texts_are_not_empty)
{
  EXPECT_FALSE(config.header_text().empty());
  EXPECT_FALSE(config.explanation_text().empty());
}

TEST_F(UTEST_WindowConfig, header_mentions_cocoa)
{
  EXPECT_THAT(config.header_text(), HasSubstr("Cocoa"));
}

TEST_F(UTEST_WindowConfig, sizes_are_positive_and_consistent)
{
  EXPECT_GT(config.width(), 0);
  EXPECT_GT(config.height(), 0);
  EXPECT_GT(config.min_width(), 0);
  EXPECT_GT(config.min_height(), 0);

  EXPECT_LE(config.min_width(), config.width());
  EXPECT_LE(config.min_height(), config.height());
}
