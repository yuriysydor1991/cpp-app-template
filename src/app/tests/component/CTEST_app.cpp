#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <csignal>
#include <filesystem>
#include <iterator>
#include <string>
#include <vector>

#include "project-global-decls.h"
#include "src/app/ApplicationFactory.h"
#include "src/log/log.h"

using namespace app;
using namespace testing;

class CTEST_app : public Test
{
 public:
  CTEST_app() { std::filesystem::remove(default_log_file()); }

  /// @brief The default log file of the factory, which the current working
  /// directory of the test case keeps.
  static std::filesystem::path default_log_file()
  {
    return log4cpp5i::Log4Cpp5Init::get_default_full_log_path();
  }

  /// @brief Runs the ApplicationFactory::execute with the given command line
  /// parameters, which follow the binary name.
  int execute_with(const std::vector<std::string>& params)
  {
    args = params;
    args.insert(args.begin(), "CTEST_app");

    argPointers.clear();

    // False positive: the char* of the argv needs the non const data().
    // cppcheck-suppress constParameterReference
    const auto toArg = [](std::string& param) { return param.data(); };

    std::transform(args.begin(), args.end(), std::back_inserter(argPointers),
                   toArg);

    realArgc = static_cast<int>(argPointers.size());
    realArgv = argPointers.data();

    return ApplicationFactory::execute(realArgc, realArgv);
  }

  int argc{0};
  char** argv{nullptr};

  std::vector<std::string> args;
  std::vector<char*> argPointers;
  int realArgc{0};
  char** realArgv{nullptr};

  ApplicationFactory facade;
};

TEST_F(CTEST_app, create_default_context_success)
{
  auto actx = facade.create_default_context(argc, argv);

  EXPECT_NE(actx, nullptr);
}

TEST_F(CTEST_app, create_default_arg_parser_success)
{
  auto argp = facade.create_default_arg_parser();

  EXPECT_NE(argp, nullptr);
}

TEST_F(CTEST_app, create_default_signals_handler_success)
{
  auto shandler = facade.create_default_signals_handler();

  EXPECT_NE(shandler, nullptr);
}

TEST_F(CTEST_app, create_default_application_success)
{
  auto dapp = facade.create_default_application();

  EXPECT_NE(dapp, nullptr);
}

TEST_F(CTEST_app, create_help_printer_success)
{
  auto hpapp = facade.create_help_printer();

  EXPECT_NE(hpapp, nullptr);
}

TEST_F(CTEST_app, create_context_success)
{
  auto ctx = facade.create_context(argc, argv);

  EXPECT_NE(ctx, nullptr);
}

TEST_F(CTEST_app, create_application_success)
{
  auto actx = facade.create_default_context(argc, argv);

  EXPECT_NE(actx, nullptr);

  auto app = facade.create_application(actx);

  EXPECT_NE(app, nullptr);
}

TEST_F(CTEST_app, signals_handler_stops_the_context)
{
  auto actx = facade.create_default_context(argc, argv);
  auto shandler = facade.create_default_signals_handler();

  EXPECT_TRUE(shandler->install(actx));
  EXPECT_FALSE(actx->get_stop());

  std::raise(SIGTERM);

  // False positive: the raise does return, since the installed handler
  // does return too.
  // cppcheck-suppress unreachableCode
  EXPECT_TRUE(actx->get_stop());
}

TEST_F(CTEST_app, signals_handler_pauses_and_resumes_the_context)
{
#if defined(SIGTSTP) && defined(SIGCONT)
  auto actx = facade.create_default_context(argc, argv);
  auto shandler = facade.create_default_signals_handler();

  EXPECT_TRUE(shandler->install(actx));
  EXPECT_FALSE(actx->get_pause());

  // The installed handler replaces the OS default disposition, so the current
  // process is not suspended by the raise below.
  std::raise(SIGTSTP);

  // False positive: the raise does return, since the installed handler
  // does return too.
  // cppcheck-suppress unreachableCode
  EXPECT_TRUE(actx->get_pause());
  EXPECT_FALSE(actx->get_stop());

  std::raise(SIGCONT);

  EXPECT_FALSE(actx->get_pause());
  EXPECT_FALSE(actx->get_stop());
#endif  // defined(SIGTSTP) && defined(SIGCONT)
}

TEST_F(CTEST_app, signals_handler_reloads_the_context)
{
#ifdef SIGHUP
  auto actx = facade.create_default_context(argc, argv);
  auto shandler = facade.create_default_signals_handler();

  EXPECT_TRUE(shandler->install(actx));
  EXPECT_FALSE(actx->get_reload());

  // The SIGHUP signal asks for a configuration reload here and terminates the
  // process under the OS default disposition, so the raise below proves the
  // handler took it over.
  std::raise(SIGHUP);

  // False positive: the raise does return, since the installed handler
  // does return too.
  // cppcheck-suppress unreachableCode
  EXPECT_TRUE(actx->get_reload());
  EXPECT_FALSE(actx->get_stop());
#endif  // SIGHUP
}

TEST_F(CTEST_app, signals_handler_serves_the_user_requests)
{
#if defined(SIGUSR1) && defined(SIGUSR2)
  auto actx = facade.create_default_context(argc, argv);
  auto shandler = facade.create_default_signals_handler();

  EXPECT_TRUE(shandler->install(actx));
  EXPECT_FALSE(actx->get_first_user_request());
  EXPECT_FALSE(actx->get_second_user_request());

  std::raise(SIGUSR1);

  // False positive: the raise does return, since the installed handler
  // does return too.
  // cppcheck-suppress unreachableCode
  EXPECT_TRUE(actx->get_first_user_request());
  EXPECT_FALSE(actx->get_second_user_request());

  std::raise(SIGUSR2);

  EXPECT_TRUE(actx->get_second_user_request());

  EXPECT_FALSE(actx->get_stop());
#endif  // defined(SIGUSR1) && defined(SIGUSR2)
}

TEST_F(CTEST_app, signals_handler_ignores_the_broken_pipe)
{
#ifdef SIGPIPE
  auto actx = facade.create_default_context(argc, argv);
  auto shandler = facade.create_default_signals_handler();

  EXPECT_TRUE(shandler->install(actx));

  // The OS default disposition terminates the process here, so the test case
  // simply reaching its end proves the signal is ignored.
  std::raise(SIGPIPE);

  // False positive: the raise does return, since the signal is ignored.
  // cppcheck-suppress unreachableCode
  EXPECT_FALSE(actx->get_stop());
  EXPECT_FALSE(actx->get_pause());
  EXPECT_FALSE(actx->get_reload());
#endif  // SIGPIPE
}

TEST_F(CTEST_app, execute_success)
{
  int status = ApplicationFactory::execute(argc, argv);

  EXPECT_EQ(status, 0);
}

TEST_F(CTEST_app, help_prints_the_options_without_a_log_file)
{
  testing::internal::CaptureStdout();

  EXPECT_EQ(execute_with({"--help"}), 0);

  EXPECT_THAT(testing::internal::GetCapturedStdout(), HasSubstr("--log-file"));
  EXPECT_FALSE(std::filesystem::exists(default_log_file()));
}

TEST_F(CTEST_app, version_prints_the_version_without_a_log_file)
{
  testing::internal::CaptureStdout();

  EXPECT_EQ(execute_with({"--version"}), 0);

  EXPECT_THAT(testing::internal::GetCapturedStdout(),
              HasSubstr(project_decls::PROJECT_BUILD_VERSION));
  EXPECT_FALSE(std::filesystem::exists(default_log_file()));
}

TEST_F(CTEST_app, unknown_option_fails_with_the_help)
{
  testing::internal::CaptureStdout();
  testing::internal::CaptureStderr();

  EXPECT_NE(execute_with({"--bogus"}), 0);

  EXPECT_THAT(testing::internal::GetCapturedStderr(),
              HasSubstr("Unknown parameter: --bogus"));
  EXPECT_THAT(testing::internal::GetCapturedStdout(), HasSubstr("Usage:"));
  EXPECT_FALSE(std::filesystem::exists(default_log_file()));
}

TEST_F(CTEST_app, missing_log_file_path_fails_with_the_help)
{
  testing::internal::CaptureStdout();
  testing::internal::CaptureStderr();

  EXPECT_NE(execute_with({"--log-file"}), 0);

  testing::internal::GetCapturedStderr();

  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_THAT(out, HasSubstr("Usage:"));
  EXPECT_THAT(out, Not(HasSubstr(project_decls::PROJECT_BUILD_COMMIT)));
}

TEST_F(CTEST_app, unopenable_log_file_fails_before_the_run)
{
  static const std::string unopenable =
      "no-such-directory-of-CTEST_app/CTEST_app.log";

  testing::internal::CaptureStderr();

  EXPECT_NE(execute_with({"-l", unopenable}), 0);

  EXPECT_THAT(testing::internal::GetCapturedStderr(),
              HasSubstr("Fail to open the log file at " + unopenable));
  EXPECT_FALSE(std::filesystem::exists(default_log_file()));
}

TEST_F(CTEST_app, custom_log_file_is_used)
{
  static const std::filesystem::path customLog{"CTEST_app.custom.log"};

  std::filesystem::remove(customLog);

  EXPECT_EQ(execute_with({"--log-file", customLog.string()}), 0);

  EXPECT_TRUE(std::filesystem::exists(customLog));
  EXPECT_FALSE(std::filesystem::exists(default_log_file()));
}
