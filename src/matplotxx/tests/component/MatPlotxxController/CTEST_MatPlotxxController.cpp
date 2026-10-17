#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <unistd.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <thread>

#include "src/app/ApplicationContext.h"
#include "src/matplotxx/MatPlotxxController.h"

using namespace matplotxxi;
using namespace testing;

class CTEST_MatPlotxxController : public Test
{
 public:
  CTEST_MatPlotxxController()
      : controller{MatPlotxxController::create()},
        ctx{std::make_shared<app::ApplicationContext>(argc, argv)},
        path{(std::filesystem::temp_directory_path() /
              (std::string{"CTEST_MatPlotxxController_"} +
               UnitTest::GetInstance()->current_test_info()->name() + ".svg"))
                 .string()}
  {
  }

  ~CTEST_MatPlotxxController() override
  {
    std::error_code ignored;
    std::filesystem::remove(path, ignored);
  }

  int argc{0};
  char** argv{nullptr};

  MatPlotxxControllerPtr controller;
  std::shared_ptr<app::ApplicationContext> ctx;
  const std::string path;
};

TEST_F(CTEST_MatPlotxxController, saves_the_plot_into_an_svg_file)
{
  ASSERT_TRUE(controller->save(path));

  EXPECT_GT(std::filesystem::file_size(path), 0U);
}

TEST_F(CTEST_MatPlotxxController, fails_to_save_under_a_regular_file)
{
  // The path names a regular file, so no directory may be made out of it.
  std::ofstream{path}.put('x');

  EXPECT_FALSE(controller->save(path + "/plot.svg"));
}

TEST_F(CTEST_MatPlotxxController, show_ends_on_the_stop_flag)
{
  ctx->set_stop(true);

  EXPECT_TRUE(controller->run(ctx));
}

TEST_F(CTEST_MatPlotxxController, show_ends_on_the_stop_flag_while_no_key_comes)
{
  // The pipe nobody writes into stands for the terminal nobody types into.
  int keys[2]{-1, -1};
  ASSERT_EQ(pipe(keys), 0);

  const int terminal = dup(STDIN_FILENO);
  ASSERT_EQ(dup2(keys[0], STDIN_FILENO), STDIN_FILENO);

  std::thread stopper{[this]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    ctx->set_stop(true);
  }};

  EXPECT_TRUE(controller->run(ctx));

  stopper.join();

  dup2(terminal, STDIN_FILENO);
  close(terminal);
  close(keys[0]);
  close(keys[1]);
}
