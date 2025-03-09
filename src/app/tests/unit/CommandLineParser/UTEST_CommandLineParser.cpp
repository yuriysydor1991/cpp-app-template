#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/CommandLineParser.h"

using namespace app;
using namespace testing;

class UTEST_CommandLineParser : public Test
{
 public:
  UTEST_CommandLineParser()
      : parser{std::make_shared<CommandLineParser>()},
        appctx{create_context(argc, argv)}
  {
  }

  std::shared_ptr<ApplicationContext> create_context(int& gargc, char**& gargv)
  {
    return std::make_shared<ApplicationContext>(gargc, gargv);
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<CommandLineParser> parser;
  std::shared_ptr<ApplicationContext> appctx;
};

TEST_F(UTEST_CommandLineParser, no_context_error)
{
  EXPECT_FALSE(parser->parse_args({}));
}

TEST_F(UTEST_CommandLineParser, empty_context)
{
  EXPECT_TRUE(parser->parse_args(appctx));
}

TEST_F(UTEST_CommandLineParser, help_short)
{
  char* customArgv[] = {"binaryName", "-h"};

  argc = 2;
  argv = customArgv;

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_TRUE(appctx->print_help_and_exit);
  EXPECT_FALSE(appctx->print_version_and_exit);
  EXPECT_TRUE(appctx->errors.empty());
}

TEST_F(UTEST_CommandLineParser, help_long)
{
  char* customArgv[] = {"binaryName", "--help"};

  argc = 2;
  argv = customArgv;

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_TRUE(appctx->print_help_and_exit);
  EXPECT_FALSE(appctx->print_version_and_exit);
  EXPECT_TRUE(appctx->errors.empty());
}

TEST_F(UTEST_CommandLineParser, version_short)
{
  char* customArgv[] = {"binaryName", "-v"};

  argc = 2;
  argv = customArgv;

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_FALSE(appctx->print_help_and_exit);
  EXPECT_TRUE(appctx->print_version_and_exit);
  EXPECT_TRUE(appctx->errors.empty());
}

TEST_F(UTEST_CommandLineParser, version_long)
{
  char* customArgv[] = {"binaryName", "--version"};

  argc = 2;
  argv = customArgv;

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_FALSE(appctx->print_help_and_exit);
  EXPECT_TRUE(appctx->print_version_and_exit);
  EXPECT_TRUE(appctx->errors.empty());
}

TEST_F(UTEST_CommandLineParser, unknown_flag)
{
  static constexpr char* unknownFlag = "--unknown";
  static const std::string expectedError =
      std::string{"Unknown parameter: "} + unknownFlag;

  char* customArgv[] = {"binaryName", unknownFlag};

  argc = 2;
  argv = customArgv;

  EXPECT_CALL(*appctx, push_error(expectedError)).Times(1);

  EXPECT_FALSE(parser->parse_args(appctx));

  EXPECT_TRUE(appctx->print_help_and_exit);
  EXPECT_FALSE(appctx->print_version_and_exit);
  EXPECT_TRUE(appctx->errors.empty());
}
