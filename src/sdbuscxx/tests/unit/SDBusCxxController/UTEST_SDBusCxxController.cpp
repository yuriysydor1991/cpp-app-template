#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/sdbuscxx/SDBusCxxController.h"

using namespace testing;
using namespace sdbuscxxi;

class UTEST_SDBusCxxController : public Test
{
 public:
  UTEST_SDBusCxxController()
      : appCtx{std::make_shared<app::ApplicationContext>(argc, argv)}
  {
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<app::ApplicationContext> appCtx;
};

TEST_F(UTEST_SDBusCxxController, run_returns_false_on_null_context)
{
  SDBusCxxController controller;

  // Asserts are compiled out for the unit tests (NDEBUG), so the explicit
  // nullptr guard inside run() is what is being exercised here.
  EXPECT_FALSE(controller.run(nullptr));
}

TEST_F(UTEST_SDBusCxxController, run_returns_false_when_not_initialized)
{
  // A freshly constructed controller holds no connection, so inited() is false
  // and run() must bail out before entering the (blocking) serve() path.
  SDBusCxxController controller;

  EXPECT_FALSE(controller.run(appCtx));
}
