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

  void two_args(const char* const secondParam)
  {
    static std::string binaryName{"binaryName"};
    static std::string secondArg;

    static char* customArgv[] = {binaryName.data(), secondArg.data()};

    secondArg = secondParam;

    // False positive: the secondArg has a static storage duration.
    // cppcheck-suppress invalidContainer
    customArgv[1] = secondArg.data();

    argc = 2;
    argv = customArgv;
  }

  void three_args(const char* const secondParam, const char* const thirdParam)
  {
    static std::string binaryName{"binaryName"};
    static std::string secondArg;
    static std::string thirdArg;

    static char* customArgv[] = {binaryName.data(), secondArg.data(),
                                 thirdArg.data()};

    secondArg = secondParam;
    thirdArg = thirdParam;

    // False positive: both of the args have a static storage duration.
    // cppcheck-suppress invalidContainer
    customArgv[1] = secondArg.data();
    customArgv[2] = thirdArg.data();

    argc = 3;
    argv = customArgv;
  }

  inline static const std::string expectedModelPath{"/tmp/a-model.bin"};

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
  two_args("-h");

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_TRUE(appctx->get_print_help_and_exit());
  EXPECT_FALSE(appctx->get_print_version_and_exit());
  EXPECT_TRUE(appctx->get_errors().empty());
}

TEST_F(UTEST_CommandLineParser, help_long)
{
  two_args("--help");

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_TRUE(appctx->get_print_help_and_exit());
  EXPECT_FALSE(appctx->get_print_version_and_exit());
  EXPECT_TRUE(appctx->get_errors().empty());
}

TEST_F(UTEST_CommandLineParser, version_short)
{
  two_args("-v");

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_FALSE(appctx->get_print_help_and_exit());
  EXPECT_TRUE(appctx->get_print_version_and_exit());
  EXPECT_TRUE(appctx->get_errors().empty());
}

TEST_F(UTEST_CommandLineParser, version_long)
{
  two_args("--version");

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_FALSE(appctx->get_print_help_and_exit());
  EXPECT_TRUE(appctx->get_print_version_and_exit());
  EXPECT_TRUE(appctx->get_errors().empty());
}

TEST_F(UTEST_CommandLineParser, model_short)
{
  three_args("-m", expectedModelPath.c_str());

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_EQ(appctx->get_model_path(), expectedModelPath);
  EXPECT_FALSE(appctx->get_print_help_and_exit());
  EXPECT_FALSE(appctx->get_print_version_and_exit());
  EXPECT_TRUE(appctx->get_errors().empty());
}

TEST_F(UTEST_CommandLineParser, model_long)
{
  three_args("--model", expectedModelPath.c_str());

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_EQ(appctx->get_model_path(), expectedModelPath);
  EXPECT_FALSE(appctx->get_print_help_and_exit());
  EXPECT_FALSE(appctx->get_print_version_and_exit());
  EXPECT_TRUE(appctx->get_errors().empty());
}

TEST_F(UTEST_CommandLineParser, model_without_the_path)
{
  two_args("--model");

  EXPECT_CALL(*appctx, push_error(_)).Times(1);

  EXPECT_FALSE(parser->parse_args(appctx));

  EXPECT_TRUE(appctx->get_model_path().empty());
}

TEST_F(UTEST_CommandLineParser, unknown_flag)
{
  static constexpr const char* const unknownFlag = "--unknown";
  static std::string unknownFlagStr{unknownFlag};
  static const std::string expectedError =
      std::string{"Unknown parameter: "} + unknownFlagStr;

  two_args(unknownFlag);

  EXPECT_CALL(*appctx, push_error(expectedError)).Times(1);

  EXPECT_FALSE(parser->parse_args(appctx));

  EXPECT_TRUE(appctx->get_print_help_and_exit());
  EXPECT_FALSE(appctx->get_print_version_and_exit());
  EXPECT_TRUE(appctx->get_errors().empty());
}
