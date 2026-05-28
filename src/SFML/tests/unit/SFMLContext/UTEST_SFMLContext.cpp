#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/SFML/SFMLContext.h"
#include "src/app/ApplicationContext.h"

using namespace app;
using namespace templateSFML;
using namespace testing;

class UTEST_SFMLContext : public Test
{
 public:
  UTEST_SFMLContext()
      : appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_SFMLContext, default_construction_stores_app_ctx)
{
  SFMLContext ctx{appCtx};

  EXPECT_EQ(ctx.appCtx, appCtx);
  EXPECT_EQ(ctx.window, nullptr);
}

TEST_F(UTEST_SFMLContext, destructor_safe_without_window)
{
  {
    SFMLContext ctx{appCtx};
  }

  SUCCEED();
}

TEST_F(UTEST_SFMLContext, fresh_context_does_not_request_stop)
{
  SFMLContext ctx{appCtx};

  EXPECT_FALSE(ctx.appCtx->stop());
}
