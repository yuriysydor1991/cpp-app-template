#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/SDL3/SDL3Context.h"
#include "src/app/ApplicationContext.h"

using namespace app;
using namespace templateSDL3;
using namespace testing;

class UTEST_SDLContext : public Test
{
 public:
  UTEST_SDLContext()
      : appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_SDLContext, default_construction_stores_app_ctx)
{
  SDL3Context ctx{appCtx};

  EXPECT_EQ(ctx.appCtx, appCtx);
  EXPECT_EQ(ctx.window, nullptr);
  EXPECT_EQ(ctx.glContext, nullptr);
}

TEST_F(UTEST_SDLContext, destructor_safe_without_window)
{
  {
    SDL3Context ctx{appCtx};
  }

  SUCCEED();
}

TEST_F(UTEST_SDLContext, fresh_context_does_not_request_stop)
{
  SDL3Context ctx{appCtx};

  EXPECT_FALSE(ctx.appCtx->stop());
}
