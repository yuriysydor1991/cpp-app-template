#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "project-global-decls.h"
#include "src/CURL/CURLController.h"
#include "src/app/applications/Application.h"

using namespace app;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
    curli::CURLController::instance = std::make_shared<curli::CURLController>();
  }

  ~UTEST_Application() override { curli::CURLController::instance.reset(); }

  curli::CURLController& curl() { return *curli::CURLController::instance; }

  void expect_download(const bool successful)
  {
    static const std::string page{"<html>The home page</html>"};

    EXPECT_CALL(curl(), download(project_decls::PROJECT_HOME_URL))
        .WillOnce(Return(curli::CURLController::download_buffer{page.cbegin(),
                                                                page.cend()}));
    EXPECT_CALL(curl(), last_response_successful())
        .WillRepeatedly(Return(successful));
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  expect_download(true);

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->get_errors().empty());

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_Application, failed_download_error)
{
  expect_download(false);

  EXPECT_CALL(curl(), last_response_code()).WillRepeatedly(Return(404L));
  EXPECT_CALL(*appCtx, push_error(_)).Times(1);

  EXPECT_NE(app->run(appCtx), 0);
}
