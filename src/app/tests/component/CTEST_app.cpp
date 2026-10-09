#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <clocale>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "src/app/ApplicationFactory.h"
#include "src/gettext/tr.h"

using namespace app;
using namespace testing;

class CTEST_app : public Test
{
 public:
  CTEST_app() = default;

  int argc{0};
  char** argv{nullptr};

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

TEST_F(CTEST_app, help_printer_speaks_the_language_of_the_user)
{
  if (setlocale(LC_MESSAGES, "uk_UA.UTF-8") == nullptr) {
    GTEST_SKIP() << "The uk_UA.UTF-8 locale is not installed";
  }

  static std::string program{"CppAppTemplate"};
  static std::string help{"--help"};
  static std::array<char*, 3> helpArgv{program.data(), help.data(), nullptr};

  int helpArgc{2};
  char** helpArgvPtr = helpArgv.data();

  setenv("LC_ALL", "uk_UA.UTF-8", 1);
  unsetenv("LANGUAGE");

  std::stringstream output;
  std::streambuf* const coutBuffer = std::cout.rdbuf(output.rdbuf());

  const int status = ApplicationFactory::execute(helpArgc, helpArgvPtr);

  std::cout.rdbuf(coutBuffer);

  // The exact translation is the business of the po/uk.po file alone, while
  // the gmock warnings about the log mock calls share the standard output.
  const std::string usage{gettexti::tr("Usage:")};

  unsetenv("LC_ALL");
  setlocale(LC_MESSAGES, "C");

  EXPECT_EQ(status, 0);
  EXPECT_NE(usage, "Usage:");
  EXPECT_THAT(output.str(), HasSubstr(usage));
}
