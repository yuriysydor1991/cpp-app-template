#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <string>
#include <utility>
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

  /// @brief Makes the command line of the binary name and the given
  /// parameters.
  void args(const std::vector<std::string>& params)
  {
    storage = params;
    storage.insert(storage.begin(), "binaryName");
    pointers.clear();

    // False positive: the argv points at the modifiable characters.
    // cppcheck-suppress constParameterReference
    const auto modifiable = [](std::string& param) { return param.data(); };

    std::transform(storage.begin(), storage.end(), std::back_inserter(pointers),
                   modifiable);

    argc = static_cast<int>(pointers.size());
    argv = pointers.data();
  }

  using PathGetter = const std::string& (ApplicationContext::*)() const;

  /// @brief The file parameters of both forms with the context fields of
  /// theirs.
  inline static const std::vector<std::pair<std::string, PathGetter>>
      fileParams{{"--cfg", &ApplicationContext::get_cfg_path},
                 {"-c", &ApplicationContext::get_cfg_path},
                 {"--weights", &ApplicationContext::get_weights_path},
                 {"-w", &ApplicationContext::get_weights_path},
                 {"--dxxwjz1", &ApplicationContext::get_dxxwjz1_path},
                 {"--dxxwjz2", &ApplicationContext::get_dxxwjz2_path},
                 {"--names", &ApplicationContext::get_names_path},
                 {"-n", &ApplicationContext::get_names_path},
                 {"--image", &ApplicationContext::get_image_path},
                 {"-i", &ApplicationContext::get_image_path}};

  inline static const std::string expectedPath{"/tmp/a-file"};

  std::vector<std::string> storage;
  std::vector<char*> pointers;

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

TEST_F(UTEST_CommandLineParser, file_parameters_fill_their_context_fields)
{
  for (const auto& [param, getter] : fileParams) {
    SCOPED_TRACE(param);

    args({param, expectedPath});

    const auto ctx = create_context(argc, argv);

    EXPECT_CALL(*ctx, push_error(_)).Times(0);

    EXPECT_TRUE(parser->parse_args(ctx));

    EXPECT_EQ(((*ctx).*getter)(), expectedPath);
    EXPECT_FALSE(ctx->get_print_help_and_exit());
    EXPECT_FALSE(ctx->get_print_version_and_exit());
  }
}

TEST_F(UTEST_CommandLineParser, file_parameters_without_the_path_fail)
{
  for (const auto& [param, getter] : fileParams) {
    SCOPED_TRACE(param);

    args({param});

    const auto ctx = create_context(argc, argv);

    EXPECT_CALL(*ctx, push_error(_)).Times(1);

    EXPECT_FALSE(parser->parse_args(ctx));

    EXPECT_TRUE(((*ctx).*getter)().empty());
  }
}

TEST_F(UTEST_CommandLineParser, all_the_file_parameters_together)
{
  args({"-c", "a.cfg", "-w", "a.weights", "--dxxwjz1", "a.dxxwjz1", "--dxxwjz2",
        "a.dxxwjz2", "-n", "a.names", "-i", "an-image.jpg"});

  EXPECT_CALL(*appctx, push_error(_)).Times(0);

  EXPECT_TRUE(parser->parse_args(appctx));

  EXPECT_EQ(appctx->get_cfg_path(), "a.cfg");
  EXPECT_EQ(appctx->get_weights_path(), "a.weights");
  EXPECT_EQ(appctx->get_dxxwjz1_path(), "a.dxxwjz1");
  EXPECT_EQ(appctx->get_dxxwjz2_path(), "a.dxxwjz2");
  EXPECT_EQ(appctx->get_names_path(), "a.names");
  EXPECT_EQ(appctx->get_image_path(), "an-image.jpg");
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
