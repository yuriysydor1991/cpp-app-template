#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>

#include "project-global-decls.h"
#include "src/app/DataLocator.h"

using namespace app;
using namespace testing;

class UTEST_DataLocator : public Test
{
 public:
  void TearDown() override
  {
    for (const auto& file : {installed, configured, prefixed}) {
      std::error_code error;

      std::filesystem::remove(file, error);
      std::filesystem::remove(file.parent_path(), error);
    }
  }

  static void touch(const std::filesystem::path& file)
  {
    std::filesystem::create_directories(file.parent_path());
    std::ofstream{file};
  }

  static bool no_executable_directory()
  {
    return DataLocator::executable_directory().empty();
  }

  inline static const std::string name{"UTEST_DataLocator.bin"};

  const std::filesystem::path installed{
      (std::filesystem::path{DataLocator::executable_directory()} /
       project_decls::PROJECT_DATA_INSTALLED_RELATIVE_DIR / name)
          .lexically_normal()};
  const std::filesystem::path configured{
      std::filesystem::path{"mock-build-data"} / name};
  const std::filesystem::path prefixed{
      std::filesystem::path{project_decls::PROJECT_DATA_INSTALLED_DIR} / name};
};

TEST_F(UTEST_DataLocator, gives_the_given_path_while_no_copy_exists)
{
  EXPECT_EQ(DataLocator::locate(configured.string()), configured.string());
}

TEST_F(UTEST_DataLocator, prefers_the_copy_installed_relative_to_the_binary)
{
  if (no_executable_directory()) {
    GTEST_SKIP() << "The system names no running executable";
  }

  touch(installed);
  touch(configured);
  touch(prefixed);

  EXPECT_EQ(DataLocator::locate(configured.string()), installed.string());
}

TEST_F(UTEST_DataLocator, locates_the_installed_directories_too)
{
  if (no_executable_directory()) {
    GTEST_SKIP() << "The system names no running executable";
  }

  std::filesystem::create_directories(installed);

  EXPECT_EQ(DataLocator::locate(configured.string()), installed.string());
}

TEST_F(UTEST_DataLocator, prefers_the_given_path_to_the_copy_under_the_prefix)
{
  touch(configured);
  touch(prefixed);

  EXPECT_EQ(DataLocator::locate(configured.string()), configured.string());
}

TEST_F(UTEST_DataLocator, falls_back_to_the_copy_under_the_prefix)
{
  touch(prefixed);

  EXPECT_EQ(DataLocator::locate(configured.string()), prefixed.string());
}

TEST_F(UTEST_DataLocator, gives_the_path_of_the_trailing_separator_as_is)
{
  touch(installed);

  EXPECT_EQ(DataLocator::locate("mock-build-data/"), "mock-build-data/");
}

TEST_F(UTEST_DataLocator, finds_the_running_executable_directory)
{
  if (no_executable_directory()) {
    GTEST_SKIP() << "The system names no running executable";
  }

  EXPECT_TRUE(std::filesystem::is_regular_file(
      std::filesystem::path{DataLocator::executable_directory()} /
      "UTEST_DataLocator"));
}
