#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <thread>

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
  EXPECT_FALSE(appCtx->get_stop());
  EXPECT_FALSE(appCtx->get_pause());
  EXPECT_FALSE(appCtx->get_reload());
  EXPECT_FALSE(appCtx->get_first_user_request());
  EXPECT_FALSE(appCtx->get_second_user_request());
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
  EXPECT_FALSE(appCtx->get_stop());
  EXPECT_FALSE(appCtx->get_pause());
  EXPECT_FALSE(appCtx->get_reload());
  EXPECT_FALSE(appCtx->get_first_user_request());
  EXPECT_FALSE(appCtx->get_second_user_request());
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
  EXPECT_FALSE(appCtx->get_stop());
  EXPECT_FALSE(appCtx->get_pause());
  EXPECT_FALSE(appCtx->get_reload());
  EXPECT_FALSE(appCtx->get_first_user_request());
  EXPECT_FALSE(appCtx->get_second_user_request());
}

TEST_F(UTEST_ApplicationContext, args_are_referenced_and_not_copied)
{
  char* pcustomArgv{nullptr};
  char** customArgv{&pcustomArgv};

  auto customCtx = create_context(argc, customArgv);

  EXPECT_EQ(&customCtx->get_argc(), &argc);
  EXPECT_EQ(&customCtx->get_argv(), &customArgv);

  argc = expectedRandomInt;
  customArgv = nullptr;

  EXPECT_EQ(customCtx->get_argc(), expectedRandomInt);
  EXPECT_EQ(customCtx->get_argv(), nullptr);
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

TEST_F(UTEST_ApplicationContext, setting_the_print_help_and_exit_flag)
{
  EXPECT_FALSE(appCtx->get_print_help_and_exit());

  appCtx->set_print_help_and_exit(true);

  EXPECT_TRUE(appCtx->get_print_help_and_exit());

  appCtx->set_print_help_and_exit(false);

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
}

TEST_F(UTEST_ApplicationContext, setting_the_print_version_and_exit_flag)
{
  EXPECT_FALSE(appCtx->get_print_version_and_exit());

  appCtx->set_print_version_and_exit(true);

  EXPECT_TRUE(appCtx->get_print_version_and_exit());

  appCtx->set_print_version_and_exit(false);

  EXPECT_FALSE(appCtx->get_print_version_and_exit());
  EXPECT_FALSE(appCtx->get_print_help_and_exit());
}

TEST_F(UTEST_ApplicationContext, setting_the_stop_flag)
{
  EXPECT_FALSE(appCtx->get_stop());

  appCtx->set_stop(true);

  EXPECT_TRUE(appCtx->get_stop());

  appCtx->set_stop(false);

  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_ApplicationContext, raising_the_stop_flag_from_another_thread)
{
  EXPECT_FALSE(appCtx->get_stop());

  std::thread stopper{[this]() { appCtx->set_stop(true); }};

  stopper.join();

  EXPECT_TRUE(appCtx->get_stop());

  EXPECT_TRUE(appCtx->get_errors().empty());
  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
}

TEST_F(UTEST_ApplicationContext, setting_the_pause_flag)
{
  EXPECT_FALSE(appCtx->get_pause());

  appCtx->set_pause(true);

  EXPECT_TRUE(appCtx->get_pause());
  EXPECT_FALSE(appCtx->get_stop());

  appCtx->set_pause(false);

  EXPECT_FALSE(appCtx->get_pause());
}

TEST_F(UTEST_ApplicationContext, raising_the_pause_flag_from_another_thread)
{
  EXPECT_FALSE(appCtx->get_pause());

  std::thread pauser{[this]() { appCtx->set_pause(true); }};

  pauser.join();

  EXPECT_TRUE(appCtx->get_pause());

  EXPECT_TRUE(appCtx->get_errors().empty());
  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_ApplicationContext, setting_the_reload_flag)
{
  EXPECT_FALSE(appCtx->get_reload());

  appCtx->set_reload(true);

  EXPECT_TRUE(appCtx->get_reload());
  EXPECT_FALSE(appCtx->get_stop());
  EXPECT_FALSE(appCtx->get_pause());

  appCtx->set_reload(false);

  EXPECT_FALSE(appCtx->get_reload());
}

TEST_F(UTEST_ApplicationContext, setting_the_user_request_flags)
{
  EXPECT_FALSE(appCtx->get_first_user_request());
  EXPECT_FALSE(appCtx->get_second_user_request());

  appCtx->set_first_user_request(true);

  EXPECT_TRUE(appCtx->get_first_user_request());
  EXPECT_FALSE(appCtx->get_second_user_request());

  appCtx->set_second_user_request(true);

  EXPECT_TRUE(appCtx->get_first_user_request());
  EXPECT_TRUE(appCtx->get_second_user_request());

  appCtx->set_first_user_request(false);
  appCtx->set_second_user_request(false);

  EXPECT_FALSE(appCtx->get_first_user_request());
  EXPECT_FALSE(appCtx->get_second_user_request());

  EXPECT_FALSE(appCtx->get_stop());
  EXPECT_FALSE(appCtx->get_pause());
  EXPECT_FALSE(appCtx->get_reload());
}

TEST_F(UTEST_ApplicationContext, raising_the_reload_flag_from_another_thread)
{
  EXPECT_FALSE(appCtx->get_reload());

  std::thread reloader{[this]() { appCtx->set_reload(true); }};

  reloader.join();

  EXPECT_TRUE(appCtx->get_reload());

  EXPECT_TRUE(appCtx->get_errors().empty());
  EXPECT_FALSE(appCtx->get_stop());
  EXPECT_FALSE(appCtx->get_pause());
}

TEST_F(UTEST_ApplicationContext, default_mysql_credentials)
{
  for (const char* name : {"MYSQL_DATABASE", "MYSQL_USER", "MYSQL_PASSWORD",
                           "MYSQL_HOST", "MYSQL_TCP_PORT"}) {
    unsetenv(name);
  }

  auto ctx = create_context(argc, argv);

  EXPECT_EQ(ctx->get_mysql_dbname(), ApplicationContext::default_mysql_name);
  EXPECT_EQ(ctx->get_mysql_user(), ApplicationContext::default_mysql_user);
  EXPECT_EQ(ctx->get_mysql_password(),
            ApplicationContext::default_mysql_password);
  EXPECT_EQ(ctx->get_mysql_host(), ApplicationContext::default_mysql_host);
  EXPECT_EQ(ctx->get_mysql_port(), ApplicationContext::default_mysql_port);
}

TEST_F(UTEST_ApplicationContext, mysql_credentials_from_the_environment)
{
  setenv("MYSQL_DATABASE", "env_db", 1);
  setenv("MYSQL_USER", "env_user", 1);
  setenv("MYSQL_PASSWORD", "env pass'word", 1);
  setenv("MYSQL_HOST", "db.example.org", 1);
  setenv("MYSQL_TCP_PORT", "13306", 1);

  auto ctx = create_context(argc, argv);

  EXPECT_EQ(ctx->get_mysql_dbname(), "env_db");
  EXPECT_EQ(ctx->get_mysql_user(), "env_user");
  EXPECT_EQ(ctx->get_mysql_password(), "env pass'word");
  EXPECT_EQ(ctx->get_mysql_host(), "db.example.org");
  EXPECT_EQ(ctx->get_mysql_port(), "13306");

  for (const char* name : {"MYSQL_DATABASE", "MYSQL_USER", "MYSQL_PASSWORD",
                           "MYSQL_HOST", "MYSQL_TCP_PORT"}) {
    unsetenv(name);
  }
}
