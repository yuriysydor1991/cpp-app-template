#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/app/applications/Application.h"
#include "src/lzma/LzmaController.h"

using namespace app;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() override { lzmai::LzmaController::instance.reset(); }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->get_errors().empty());

  EXPECT_FALSE(appCtx->get_print_help_and_exit());
  EXPECT_FALSE(appCtx->get_print_version_and_exit());
  EXPECT_FALSE(appCtx->get_stop());
}

TEST_F(UTEST_Application, round_trip_mismatch)
{
  lzmai::LzmaController::instance = std::make_shared<lzmai::LzmaController>();

  EXPECT_CALL(*lzmai::LzmaController::instance, compress(_)).Times(1);
  EXPECT_CALL(*lzmai::LzmaController::instance, uncompress(_))
      .WillOnce(Return(lzmai::LzmaController::buffer{0x00}));

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_FALSE(appCtx->get_stop());
}
