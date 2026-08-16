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
  EXPECT_EQ(appCtx->get_argc(), 0);
  EXPECT_EQ(appCtx->get_argv(), nullptr);

  EXPECT_TRUE(appCtx->get_errors().empty());
  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
  EXPECT_TRUE(appCtx->get_image_path().empty());
  EXPECT_TRUE(appCtx->get_cascade_path().empty());
}

TEST_F(UTEST_ApplicationContext, image_and_cascade_paths_round_trip)
{
  static const std::string expectedImage{"/tmp/face.png"};
  static const std::string expectedCascade{"/usr/share/cascade.xml"};

  appCtx->set_image_path(expectedImage);
  appCtx->set_cascade_path(expectedCascade);

  EXPECT_EQ(appCtx->get_image_path(), expectedImage);
  EXPECT_EQ(appCtx->get_cascade_path(), expectedCascade);
}

TEST_F(UTEST_ApplicationContext, custom_argc)
{
  int margc{expectedRandomInt};

  auto customCtx = create_context(margc, argv);

  EXPECT_EQ(customCtx->get_argc(), expectedRandomInt);
  EXPECT_EQ(customCtx->get_argv(), nullptr);

  EXPECT_TRUE(appCtx->get_errors().empty());
  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
}

TEST_F(UTEST_ApplicationContext, custom_argv)
{
  char* pcustomArgv{nullptr};
  char** customArgv{&pcustomArgv};

  auto customCtx = create_context(argc, customArgv);

  EXPECT_EQ(customCtx->get_argc(), argc);
  EXPECT_EQ(customCtx->get_argv(), customArgv);

  EXPECT_TRUE(appCtx->get_errors().empty());
  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
}

TEST_F(UTEST_ApplicationContext, pushing_an_error)
{
  EXPECT_EQ(appCtx->get_argc(), 0);
  EXPECT_EQ(appCtx->get_argv(), nullptr);

  appCtx->push_error(expectedError);

  EXPECT_FALSE(appCtx->get_errors().empty());

  EXPECT_EQ(appCtx->get_errors().front(), expectedError);

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
}

TEST_F(UTEST_ApplicationContext, pushing_multiple_errors)
{
  EXPECT_EQ(appCtx->get_argc(), 0);
  EXPECT_EQ(appCtx->get_argv(), nullptr);

  appCtx->push_error(expectedError);
  appCtx->push_error(expectedError);

  EXPECT_FALSE(appCtx->get_errors().empty());

  for (const auto& error : appCtx->get_errors()) {
    EXPECT_EQ(error, expectedError);
  }

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
}
