#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "project-global-decls.h"
#include "src/app/applications/ApplicationHelpPrinter.h"

using namespace app;
using namespace testing;

class UTEST_ApplicationHelpPrinter : public Test
{
 public:
  UTEST_ApplicationHelpPrinter()
      : app{std::make_shared<ApplicationHelpPrinter>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationHelpPrinter> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_ApplicationHelpPrinter, no_context_error)
{
  EXPECT_NE(app->run({}), 0);
}

TEST_F(UTEST_ApplicationHelpPrinter, normal_exit)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->get_errors().empty());

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_ApplicationHelpPrinter, the_command_line_errors_fail_the_run)
{
  static const std::string error = "Unknown parameter: --bogus";

  appCtx->push_error(error);

  testing::internal::CaptureStderr();

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_THAT(testing::internal::GetCapturedStderr(), HasSubstr(error));
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_ApplicationHelpPrinter, the_log_file_option_is_listed)
{
  testing::internal::CaptureStdout();

  EXPECT_EQ(app->run(appCtx), 0);

  const std::string help = testing::internal::GetCapturedStdout();

  EXPECT_THAT(help, HasSubstr("--log-file"));
  EXPECT_THAT(help, HasSubstr("-l"));
}

TEST_F(UTEST_ApplicationHelpPrinter, the_speech_options_are_listed)
{
  testing::internal::CaptureStdout();

  EXPECT_EQ(app->run(appCtx), 0);

  const std::string help = testing::internal::GetCapturedStdout();

  for (const char* const option :
       {"--text or -t", "--voice or -s", "--output or -o"}) {
    EXPECT_THAT(help, HasSubstr(option));
  }

  EXPECT_THAT(help, HasSubstr(project_decls::PROJECT_TTS_TEXT));
  EXPECT_THAT(help, HasSubstr(project_decls::PROJECT_TTS_VOICE));
}
