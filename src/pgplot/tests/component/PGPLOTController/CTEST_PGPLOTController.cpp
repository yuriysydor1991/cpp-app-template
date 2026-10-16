#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"
#include "src/pgplot/PGPLOTController.h"

using namespace pgploti;
using namespace testing;

class CTEST_PGPLOTController : public Test
{
 public:
  CTEST_PGPLOTController()
      : ctx{std::make_shared<app::ApplicationContext>(argc, argv)},
        path{(std::filesystem::temp_directory_path() /
              (std::string{"CTEST_PGPLOTController_"} +
               UnitTest::GetInstance()->current_test_info()->name() + ".ps"))
                 .string()}
  {
  }

  ~CTEST_PGPLOTController() override
  {
    std::error_code ignored;
    std::filesystem::remove(path, ignored);
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<app::ApplicationContext> ctx;
  const std::string path;
};

TEST_F(CTEST_PGPLOTController, draws_onto_the_null_device)
{
  PGPLOTController controller{"/NULL"};

  EXPECT_TRUE(controller.run(ctx));
}

TEST_F(CTEST_PGPLOTController, draws_into_a_postscript_file)
{
  PGPLOTController controller{path + "/PS"};

  ASSERT_TRUE(controller.run(ctx));

  ASSERT_TRUE(std::filesystem::exists(path));
  EXPECT_GT(std::filesystem::file_size(path), 0U);
}

TEST_F(CTEST_PGPLOTController, fails_on_an_unknown_device)
{
  PGPLOTController controller{"/NO-SUCH-DEVICE"};

  EXPECT_FALSE(controller.run(ctx));
}
