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

TEST_F(UTEST_ApplicationContext, firebird_defaults_without_environment)
{
  for (const char* name : {"FIREBIRD_DATABASE", "ISC_USER", "ISC_PASSWORD",
                           "FIREBIRD_HOST", "FIREBIRD_PORT"}) {
    unsetenv(name);
  }

  const auto ctx = create_context(argc, argv);

  EXPECT_EQ(ctx->get_fb_dbname(), ApplicationContext::default_fb_name);
  EXPECT_EQ(ctx->get_fb_user(), ApplicationContext::default_fb_user);
  EXPECT_EQ(ctx->get_fb_password(), ApplicationContext::default_fb_password);
  EXPECT_TRUE(ctx->get_fb_host().empty());
  EXPECT_TRUE(ctx->get_fb_port().empty());
}

TEST_F(UTEST_ApplicationContext, firebird_settings_from_environment)
{
  setenv("FIREBIRD_DATABASE", "/var/lib/firebird/data/test.fdb", 1);
  setenv("ISC_USER", "template_user", 1);
  setenv("ISC_PASSWORD", "template password", 1);
  setenv("FIREBIRD_HOST", "db.example.org", 1);
  setenv("FIREBIRD_PORT", "3051", 1);

  const auto ctx = create_context(argc, argv);

  for (const char* name : {"FIREBIRD_DATABASE", "ISC_USER", "ISC_PASSWORD",
                           "FIREBIRD_HOST", "FIREBIRD_PORT"}) {
    unsetenv(name);
  }

  EXPECT_EQ(ctx->get_fb_dbname(), "/var/lib/firebird/data/test.fdb");
  EXPECT_EQ(ctx->get_fb_user(), "template_user");
  EXPECT_EQ(ctx->get_fb_password(), "template password");
  EXPECT_EQ(ctx->get_fb_host(), "db.example.org");
  EXPECT_EQ(ctx->get_fb_port(), "3051");
}
