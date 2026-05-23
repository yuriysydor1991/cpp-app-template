#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/sdbuscxx/SDBusCxxController.h"

using namespace testing;
using namespace sdbuscxxi;

namespace
{

/**
 * @brief Test double that neutralises the bus-touching seams so the run()
 * orchestration can be exercised without a live system bus.
 *
 * init() never opens a real connection and inited() reports the controller as
 * initialized, letting the test drive run() past its initialization guard and
 * into the demo call - which then fails gracefully because no real connection
 * was established.
 */
class TestableSDBusCxxController : public SDBusCxxController
{
 protected:
  bool init() override { return true; }
  bool inited() override { return true; }
};

}  // namespace

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
  // and run() must bail out before attempting any bus interaction.
  SDBusCxxController controller;

  EXPECT_FALSE(controller.run(appCtx));
}

TEST_F(UTEST_SDBusCxxController, run_returns_false_when_query_cannot_reach_bus)
{
  // Past the initialization guard the demo call still has no live connection to
  // talk to, so the orchestration must report the failure back as false.
  TestableSDBusCxxController controller;

  EXPECT_FALSE(controller.run(appCtx));
}
