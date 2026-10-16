#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <unistd.h>

#include <cstdlib>
#include <filesystem>
#include <memory>
#include <string>

#include "project-global-decls.h"
#include "src/app/ApplicationContext.h"
#include "src/sqlite3cpp/SQLiteController.h"

using namespace app;
using namespace sqlite3i;
using namespace testing;

class CTEST_SQLiteController : public Test
{
 public:
  CTEST_SQLiteController()
  {
    std::filesystem::create_directories(root);

    unsetenv("SQLITE_DB_PATH");
    unsetenv("XDG_DATA_HOME");
    setenv("HOME", (root / "home").c_str(), 1);
  }

  ~CTEST_SQLiteController() override { std::filesystem::remove_all(root); }

  /// @brief Checks that a new context points the expected database file and
  /// that the controller creates and queries it.
  void expect_working_database(const std::filesystem::path& expected)
  {
    auto actx = std::make_shared<ApplicationContext>(argc, argv);
    auto controller = std::make_shared<SQLiteController>();

    EXPECT_EQ(std::filesystem::path{actx->get_db_dbname()}, expected);

    ASSERT_TRUE(controller->connect(actx));

    EXPECT_TRUE(std::filesystem::is_regular_file(expected));
    EXPECT_THAT(controller->get_current_date(),
                MatchesRegex("[0-9]{4}-[0-9]{2}-[0-9]{2}"));
  }

  int argc{0};
  char** argv{nullptr};

  const std::filesystem::path root{
      std::filesystem::temp_directory_path() /
      ("CTEST_SQLiteController-" + std::to_string(getpid()))};
  const std::filesystem::path dbfile{
      std::filesystem::path{project_decls::PROJECT_NAME} /
      ApplicationContext::default_db_name};
};

TEST_F(CTEST_SQLiteController, database_lives_in_the_xdg_data_home)
{
  setenv("XDG_DATA_HOME", (root / "xdg").c_str(), 1);

  expect_working_database(root / "xdg" / dbfile);
}

TEST_F(CTEST_SQLiteController, database_falls_back_to_the_home_data_dir)
{
  expect_working_database(root / "home" / ".local" / "share" / dbfile);
}

TEST_F(CTEST_SQLiteController, environment_variable_overrides_the_path)
{
  const auto custom = root / "custom" / "dir" / "test.db";

  setenv("SQLITE_DB_PATH", custom.c_str(), 1);

  expect_working_database(custom);
}

TEST_F(CTEST_SQLiteController, uncreatable_directory_fails_to_connect)
{
  setenv("SQLITE_DB_PATH", "/dev/null/test.db", 1);

  auto actx = std::make_shared<ApplicationContext>(argc, argv);
  auto controller = std::make_shared<SQLiteController>();

  EXPECT_FALSE(controller->connect(actx));
  EXPECT_TRUE(controller->get_current_date().empty());
}
