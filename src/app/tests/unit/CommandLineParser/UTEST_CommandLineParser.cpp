#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

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

    // False positive: the secondArg has a static storage duration.
    // cppcheck-suppress invalidContainer
    customArgv[1] = secondArg.data();
    customArgv[2] = thirdArg.data();

    argc = 3;
    argv = customArgv;
  }

  /// @brief Makes the given parameters the command line ones, which follow the
  /// binary name.
  void set_args(const std::vector<std::string>& params)
  {
    static std::vector<std::string> storage;
    static std::vector<char*> pointers;

    storage = params;
    storage.insert(storage.begin(), "binaryName");

    pointers.clear();

    // False positive: the char* of the argv needs the non const data().
    // cppcheck-suppress constParameterReference
    const auto toArg = [](std::string& param) { return param.data(); };

    std::transform(storage.begin(), storage.end(), std::back_inserter(pointers),
                   toArg);

    argc = static_cast<int>(pointers.size());
    argv = pointers.data();
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
  EXPECT_THAT(appctx->get_errors(), ElementsAre(expectedError));
}

TEST_F(UTEST_CommandLineParser, token_long)
{
  static const std::string token{"an-anthropic-api-token"};

  three_args("--token", token.c_str());

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_EQ(appctx->get_claude_token(), token);
  EXPECT_TRUE(appctx->get_claude_question().empty());
  EXPECT_FALSE(appctx->get_print_help_and_exit());
  EXPECT_FALSE(appctx->get_print_version_and_exit());
}

TEST_F(UTEST_CommandLineParser, token_short)
{
  static const std::string token{"an-anthropic-api-token"};

  three_args("-t", token.c_str());

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_EQ(appctx->get_claude_token(), token);
}

TEST_F(UTEST_CommandLineParser, question_long)
{
  static const std::string question{"What is the point of taxes?"};

  three_args("--question", question.c_str());

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_EQ(appctx->get_claude_question(), question);
  EXPECT_TRUE(appctx->get_claude_token().empty());
}

TEST_F(UTEST_CommandLineParser, question_short)
{
  static const std::string question{"What is the point of taxes?"};

  three_args("-q", question.c_str());

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_EQ(appctx->get_claude_question(), question);
}

TEST_F(UTEST_CommandLineParser, model_long)
{
  static const std::string model{"claude-sonnet-5-5"};

  three_args("--model", model.c_str());

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_EQ(appctx->get_claude_model(), model);
}

TEST_F(UTEST_CommandLineParser, model_short)
{
  static const std::string model{"claude-sonnet-5-5"};

  three_args("-m", model.c_str());

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_EQ(appctx->get_claude_model(), model);
}

TEST_F(UTEST_CommandLineParser, token_without_data)
{
  static const std::string expectedError{
      "Parameter --token requires the data next to it."};

  two_args("--token");

  EXPECT_CALL(*appctx, push_error(expectedError)).Times(1);

  EXPECT_FALSE(parser->parse_args(appctx));

  EXPECT_TRUE(appctx->get_claude_token().empty());
}

TEST_F(UTEST_CommandLineParser, question_without_data)
{
  static const std::string expectedError{
      "Parameter --question requires the data next to it."};

  two_args("--question");

  EXPECT_CALL(*appctx, push_error(expectedError)).Times(1);

  EXPECT_FALSE(parser->parse_args(appctx));

  EXPECT_TRUE(appctx->get_claude_question().empty());
}

TEST_F(UTEST_CommandLineParser, log_file_short)
{
  set_args({"-l", "custom.log"});

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_FALSE(appctx->get_print_help_and_exit());
  EXPECT_FALSE(appctx->get_print_version_and_exit());
  EXPECT_TRUE(appctx->get_errors().empty());
  EXPECT_EQ(CommandLineParser::get_custom_logfile(argc, argv), "custom.log");
}

TEST_F(UTEST_CommandLineParser, log_file_long)
{
  set_args({"--log-file", "custom.log"});

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_FALSE(appctx->get_print_help_and_exit());
  EXPECT_FALSE(appctx->get_print_version_and_exit());
  EXPECT_TRUE(appctx->get_errors().empty());
  EXPECT_EQ(CommandLineParser::get_custom_logfile(argc, argv), "custom.log");
}

TEST_F(UTEST_CommandLineParser, log_file_value_is_skipped)
{
  set_args({"--log-file", "custom.log", "--version"});

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_FALSE(appctx->get_print_help_and_exit());
  EXPECT_TRUE(appctx->get_print_version_and_exit());
  EXPECT_TRUE(appctx->get_errors().empty());
}

TEST_F(UTEST_CommandLineParser, log_file_missing_value)
{
  static const std::string expectedError =
      "Parameter --log-file requires the data next to it.";

  set_args({"--log-file"});

  EXPECT_CALL(*appctx, push_error(expectedError)).Times(1);

  EXPECT_FALSE(parser->parse_args(appctx));

  EXPECT_TRUE(appctx->get_print_help_and_exit());
  EXPECT_FALSE(appctx->get_print_version_and_exit());
  EXPECT_THAT(appctx->get_errors(), ElementsAre(expectedError));
  EXPECT_TRUE(CommandLineParser::get_custom_logfile(argc, argv).empty());
}
