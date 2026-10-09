#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <clocale>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

#include "src/gettext/GettextController.h"
#include "src/gettext/tr.h"
#include "src/log/log.h"
#include "src/log/severity-macro-consts.h"

using namespace gettexti;
using namespace testing;

/**
 * @brief Component test of the GettextController with the libintl and the
 * project logger.
 *
 * The test cases bind the catalog of the uk.po file next to the test. The
 * ones translating into the Ukrainian language skip themselves while the
 * uk_UA.UTF-8 locale is not installed (e.g. inside a container without the
 * locales-all package), since the libintl translates nothing then.
 */
class CTEST_GettextController : public Test
{
 public:
  CTEST_GettextController()
  {
    std::ofstream truncating{logFile, std::ofstream::trunc};

    LOG_INIT(logFile, MACRO_LVL_TRACE, false);

    // The LANGUAGE variable of the developer environment would take over the
    // language the test cases ask for.
    unsetenv("LANGUAGE");
  }

  ~CTEST_GettextController() override
  {
    unsetenv("LC_ALL");
    setlocale(LC_MESSAGES, "C");
  }

  /// @brief Reopens the log file to flush it, since the logger flushes the
  /// warnings and the errors alone, and gives the log written so far.
  std::string log_contents() const
  {
    LOG_INIT(logFile, MACRO_LVL_TRACE, false);

    std::stringstream contents;

    contents << std::ifstream{logFile}.rdbuf();

    return contents.str();
  }

  /// @brief Binds the test catalog under the locale the environment asks for.
  bool bind_under(const char* const locale)
  {
    return setenv("LC_ALL", locale, 1) == 0 &&
           controller->bind(domain, catalogs);
  }

  static bool ukrainian_installed()
  {
    const bool installed = setlocale(LC_MESSAGES, "uk_UA.UTF-8") != nullptr;

    setlocale(LC_MESSAGES, "C");

    return installed;
  }

  inline static constexpr const char* const domain = "CTEST_GettextController";
  inline static constexpr const char* const catalogs =
      CTEST_GettextController_DATA_DIR "/locale";

  /// @brief Every test case gets a log file of it's own, so the parallel
  /// ctest runs keep their logs apart.
  const std::string logFile{
      std::string{CTEST_GettextController_DATA_DIR "/"} +
      UnitTest::GetInstance()->current_test_info()->name() + ".log"};

  GettextControllerPtr controller{GettextController::create()};
};

TEST_F(CTEST_GettextController, translates_into_the_ukrainian_language)
{
  if (!ukrainian_installed()) {
    GTEST_SKIP() << "The uk_UA.UTF-8 locale is not installed";
  }

  ASSERT_TRUE(bind_under("uk_UA.UTF-8"));

  EXPECT_STREQ(tr("Hello, gettext!"), "Привіт, gettext!");
  EXPECT_STREQ(tr("No translation of this one"), "No translation of this one");
}

TEST_F(CTEST_GettextController, chooses_the_ukrainian_plural_forms)
{
  if (!ukrainian_installed()) {
    GTEST_SKIP() << "The uk_UA.UTF-8 locale is not installed";
  }

  ASSERT_TRUE(bind_under("uk_UA.UTF-8"));

  EXPECT_STREQ(trn("file", "files", 1), "файл");
  EXPECT_STREQ(trn("file", "files", 2), "файли");
  EXPECT_STREQ(trn("file", "files", 5), "файлів");
  EXPECT_STREQ(trn("file", "files", 11), "файлів");
  EXPECT_STREQ(trn("file", "files", 21), "файл");
  EXPECT_STREQ(trn("file", "files", 24), "файли");
  EXPECT_STREQ(trn("file", "files", 112), "файлів");
}

TEST_F(CTEST_GettextController, keeps_the_english_messages_in_the_c_locale)
{
  ASSERT_TRUE(bind_under("C"));

  EXPECT_STREQ(tr("Hello, gettext!"), "Hello, gettext!");
  EXPECT_STREQ(trn("file", "files", 1), "file");
  EXPECT_STREQ(trn("file", "files", 5), "files");
}

TEST_F(CTEST_GettextController, warns_about_the_locale_not_installed)
{
  ASSERT_TRUE(bind_under("xx_XX.UTF-8"));

  EXPECT_STREQ(tr("Hello, gettext!"), "Hello, gettext!");
  EXPECT_THAT(log_contents(), HasSubstr("is not installed"));
}

TEST_F(CTEST_GettextController, keeps_the_numbers_formatting)
{
  if (!ukrainian_installed()) {
    GTEST_SKIP() << "The uk_UA.UTF-8 locale is not installed";
  }

  ASSERT_TRUE(bind_under("uk_UA.UTF-8"));

  // The uk_UA locale writes the 1,5 decimal comma, which the binding keeps
  // away from the rest of the code.
  EXPECT_DOUBLE_EQ(std::stod("1.5"), 1.5);
  EXPECT_EQ(std::to_string(1.5), "1.500000");
}

TEST_F(CTEST_GettextController, fails_to_bind_the_empty_domain)
{
  EXPECT_FALSE(controller->bind("", catalogs));
  EXPECT_THAT(log_contents(), HasSubstr("Failed to bind"));
}

TEST_F(CTEST_GettextController, init_binds_the_project_catalogs)
{
  EXPECT_TRUE(controller->init(""));
}
