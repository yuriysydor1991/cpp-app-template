#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "src/wt4/Wt4ArgsFilter.h"

using namespace wt4server;
using namespace testing;

class UTEST_Wt4ArgsFilter : public Test
{
 public:
  std::vector<std::string> filter(std::vector<std::string> args)
  {
    std::vector<char*> argv;

    // the main function argv points to the mutable argument buffers
    std::transform(args.begin(), args.end(), std::back_inserter(argv),
                   // cppcheck-suppress constParameterReference
                   [](std::string& arg) { return arg.data(); });

    return argsFilter.filter(static_cast<int>(argv.size()), argv.data());
  }

  Wt4ArgsFilter argsFilter;
};

TEST_F(UTEST_Wt4ArgsFilter, no_args)
{
  EXPECT_TRUE(argsFilter.filter(0, nullptr).empty());
  EXPECT_TRUE(filter({"app"}).empty());
}

TEST_F(UTEST_Wt4ArgsFilter, wt_args_pass_through)
{
  EXPECT_THAT(filter({"app", "--docroot", ".;/resources", "--http-listen",
                      "127.0.0.1:8000"}),
              ElementsAre("--docroot", ".;/resources", "--http-listen",
                          "127.0.0.1:8000"));
}

TEST_F(UTEST_Wt4ArgsFilter, log_file_params_skipped_with_data)
{
  EXPECT_THAT(filter({"app", "-l", "a.log", "--docroot", ".", "--log-file",
                      "b.log", "--http-listen", "127.0.0.1:8000"}),
              ElementsAre("--docroot", ".", "--http-listen", "127.0.0.1:8000"));
}

TEST_F(UTEST_Wt4ArgsFilter, app_flags_skipped)
{
  EXPECT_THAT(
      filter({"app", "-h", "--docroot", ".", "--help", "-v", "--version"}),
      ElementsAre("--docroot", "."));
}

TEST_F(UTEST_Wt4ArgsFilter, trailing_log_file_param_without_data)
{
  EXPECT_THAT(filter({"app", "--docroot", ".", "-l"}),
              ElementsAre("--docroot", "."));
}
