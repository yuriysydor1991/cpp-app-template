#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "src/gettext/CatalogsLocator.h"

using namespace gettexti;
using namespace testing;

namespace fs = std::filesystem;

/**
 * @brief The CatalogsLocator test cases look into an installation alike tree
 * of the test build directory: the prefix/bin directory of the executable,
 * the prefix/share/locale one of the catalogs next to it and the build/locale
 * one of the build tree catalogs.
 */
class UTEST_CatalogsLocator : public Test
{
 public:
  UTEST_CatalogsLocator()
  {
    fs::create_directories(root / "prefix" / "bin");
    fs::create_directories(nextToExec);
    fs::create_directories(buildDir);
  }

  ~UTEST_CatalogsLocator() override { fs::current_path(previousDir); }

  inline static const fs::path root{UTEST_CatalogsLocator_DATA_DIR};
  inline static const std::string exec{(root / "prefix/bin/app").string()};
  inline static const std::string nextToExec{
      (root / "prefix/share/locale").string()};
  inline static const std::string buildDir{(root / "build/locale").string()};
  inline static const std::string installDir{
      (root / "missing/locale").string()};

  const fs::path previousDir{fs::current_path()};
};

TEST_F(UTEST_CatalogsLocator, prefers_the_catalogs_next_to_the_executable)
{
  const CatalogsLocator locator{"../share/locale", buildDir, installDir};

  EXPECT_EQ(locator.locate(exec), nextToExec);
}

TEST_F(UTEST_CatalogsLocator, gives_an_absolute_directory_for_a_relative_exec)
{
  const CatalogsLocator locator{"../share/locale", buildDir, installDir};

  fs::current_path(root / "prefix");

  EXPECT_EQ(locator.locate("bin/app"), nextToExec);
}

TEST_F(UTEST_CatalogsLocator, falls_back_to_the_build_tree_catalogs)
{
  const CatalogsLocator locator{"../missing/locale", buildDir, installDir};

  EXPECT_EQ(locator.locate(exec), buildDir);
}

TEST_F(UTEST_CatalogsLocator, falls_back_to_the_installation_catalogs)
{
  const CatalogsLocator locator{"../missing/locale", installDir, installDir};

  EXPECT_EQ(locator.locate(exec), installDir);
}

TEST_F(UTEST_CatalogsLocator, names_the_running_executable)
{
  const std::string running = CatalogsLocator::executable("given/exec");

  // The /proc/self/exe link names the test executable itself on Linux.
  EXPECT_TRUE(running == "given/exec" ||
              fs::equivalent(running, "/proc/self/exe"));
}

TEST_F(UTEST_CatalogsLocator, ignores_the_bare_executable_name)
{
  const CatalogsLocator locator{"../share/locale", buildDir, installDir};

  // The ../share/locale directory is next to the current one, while a bare
  // executable name, looked up through the PATH, tells nothing about the
  // directory of the executable.
  fs::current_path(root / "prefix/bin");

  EXPECT_EQ(locator.locate("app"), buildDir);
  EXPECT_EQ(locator.locate(""), buildDir);
}
