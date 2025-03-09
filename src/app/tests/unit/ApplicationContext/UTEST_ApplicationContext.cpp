#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/ApplicationContext.h"

using namespace app;
using namespace testing;

class UTEST_ApplicationContext : public Test
{
 public:
  inline static constexpr const int expectedRandomInt{123};
  inline static const std::string expectedError{"random error description"};

  UTEST_ApplicationContext() : appCtx{create_context(argc, argv)} {}

  std::shared_ptr<ApplicationContext> create_context(int& gargc, char**& gargv)
  {
    return std::make_shared<ApplicationContext>(gargc, gargv);
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_ApplicationContext, empty_context)
{
  EXPECT_EQ(appCtx->argc, 0);
  EXPECT_EQ(appCtx->argv, nullptr);

  EXPECT_TRUE(appCtx->errors.empty());
  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_ApplicationContext, custom_argc)
{
  int margc{expectedRandomInt};

  auto customCtx = create_context(margc, argv);

  EXPECT_EQ(customCtx->argc, expectedRandomInt);
  EXPECT_EQ(customCtx->argv, nullptr);

  EXPECT_TRUE(appCtx->errors.empty());
  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_ApplicationContext, custom_argv)
{
  char* pcustomArgv{nullptr};
  char** customArgv{&pcustomArgv};

  auto customCtx = create_context(argc, customArgv);

  EXPECT_EQ(customCtx->argc, argc);
  EXPECT_EQ(customCtx->argv, customArgv);

  EXPECT_TRUE(appCtx->errors.empty());
  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_ApplicationContext, pushing_an_error)
{
  EXPECT_EQ(appCtx->argc, 0);
  EXPECT_EQ(appCtx->argv, nullptr);

  appCtx->push_error(expectedError);

  EXPECT_FALSE(appCtx->errors.empty());

  EXPECT_EQ(appCtx->errors.front(), expectedError);

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_ApplicationContext, pushing_multiple_errors)
{
  EXPECT_EQ(appCtx->argc, 0);
  EXPECT_EQ(appCtx->argv, nullptr);

  appCtx->push_error(expectedError);
  appCtx->push_error(expectedError);

  EXPECT_FALSE(appCtx->errors.empty());

  for (const auto& error : appCtx->errors) {
    EXPECT_EQ(error, expectedError);
  }

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}
