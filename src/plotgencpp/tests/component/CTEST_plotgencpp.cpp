#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "plotgen.h"
#include "src/app/ApplicationContext.h"
#include "src/plotgencpp/PlotGenCppController.h"

using namespace plotgencppi;
using namespace testing;

/**
 * @brief Component test for the plotgencpp component. It drives the real
 * PlotGenCppController through its public facade (create() + run()) and asserts
 * the integration end to end. The PlotGenCpp/SFML backend is replaced by the
 * test plotgen.h stand-in, so the render path is exercised and verified without
 * ever opening an on-screen window.
 */
class CTEST_plotgencpp : public Test
{
 public:
  CTEST_plotgencpp()
      : controller{PlotGenCppController::create()},
        ctx{std::make_shared<app::ApplicationContext>(argc, argv)}
  {
    PlotGen::reset();
  }

  ~CTEST_plotgencpp() override { PlotGen::reset(); }

  int argc{0};
  char** argv{nullptr};

  PlotGenCppControllerPtr controller;
  std::shared_ptr<app::ApplicationContext> ctx;
};

TEST_F(CTEST_plotgencpp, create_default_controller_success)
{
  EXPECT_NE(controller, nullptr);
}

TEST_F(CTEST_plotgencpp, run_renders_with_valid_context)
{
  EXPECT_TRUE(controller->run(ctx));

  EXPECT_EQ(PlotGen::constructed, 1u);
  EXPECT_EQ(PlotGen::plot_calls, 1u);
  EXPECT_EQ(PlotGen::show_calls, 1u);
}

TEST_F(CTEST_plotgencpp, run_rejects_null_context)
{
  EXPECT_FALSE(controller->run({}));

  EXPECT_EQ(PlotGen::show_calls, 0u);
}
