#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/wt4/Wt4Context.h"

using namespace wt4server;
using namespace testing;

class UTEST_Wt4Context : public Test
{
 public:
  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<app::ApplicationContext> appCtx{
      std::make_shared<app::ApplicationContext>(argc, argv)};
};

TEST_F(UTEST_Wt4Context, holds_the_application_context)
{
  Wt4Context wt4ctx{appCtx};

  EXPECT_EQ(wt4ctx.appctx, appCtx);
}
