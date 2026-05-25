#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "plotgen.h"
#include "src/app/ApplicationContext.h"
#include "src/plotgencpp/PlotGenCppController.h"

using namespace plotgencppi;
using namespace testing;

class UTEST_PlotGenCppController : public Test
{
 public:
  UTEST_PlotGenCppController()
      : controller{PlotGenCppController::create()},
        ctx{std::make_shared<app::ApplicationContext>(argc, argv)}
  {
    PlotGen::reset();
  }

  ~UTEST_PlotGenCppController() override { PlotGen::reset(); }

  int argc{0};
  char** argv{nullptr};

  PlotGenCppControllerPtr controller;
  std::shared_ptr<app::ApplicationContext> ctx;
};

TEST_F(UTEST_PlotGenCppController, create_returns_valid_instance)
{
  EXPECT_NE(controller, nullptr);
}

TEST_F(UTEST_PlotGenCppController, run_with_null_context_returns_false)
{
  EXPECT_FALSE(controller->run({}));

  // A rejected context must short-circuit before any rendering happens.
  EXPECT_EQ(PlotGen::constructed, 0u);
  EXPECT_EQ(PlotGen::show_calls, 0u);
}

TEST_F(UTEST_PlotGenCppController, run_with_valid_context_returns_true)
{
  EXPECT_TRUE(controller->run(ctx));
}

TEST_F(UTEST_PlotGenCppController, run_drives_the_plotting_backend)
{
  EXPECT_TRUE(controller->run(ctx));

  EXPECT_EQ(PlotGen::constructed, 1u);
  EXPECT_EQ(PlotGen::plot_calls, 1u);
  EXPECT_EQ(PlotGen::show_calls, 1u);
}
