#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "LibraryContext.h"
#include "LibraryFacade.h"
#include "src/lib/facade/public/ILogger.h"
#include "src/lib/facade/public/severity-macro-consts.h"
#include "src/log/default-logger/real-default-logger/RealDefaultLogger.h"
#include "src/log/log.h"

using namespace testing;
using namespace CppAppTemplate011;
using namespace default_logger;

namespace
{

/**
 * @brief The application owned real logger substitution which records every
 * received message instead of the actual logging.
 */
class RecordingRealLogger : public RealDefaultLogger
{
 public:
  using RealDefaultLogger::log;

  void log(const unsigned short& loglvl, const std::string& msg) override
  {
    lvls.push_back(loglvl);
    msgs.push_back(msg);
  }

  std::vector<unsigned short> lvls;
  std::vector<std::string> msgs;
};

/**
 * @brief The application owned logger which implements the logger::ILogger
 * interface directly instead of deriving from the RealDefaultLogger, the very
 * same way an application built on top of another logging library hands its own
 * logger over to the library. It records every received message instead of the
 * actual logging.
 */
class RecordingLogger : public logger::ILogger
{
 public:
  inline static const std::string lvlRepr{"REC"};

  void log(const unsigned short& loglvl, const std::string& msg) override
  {
    lvls.push_back(loglvl);
    msgs.push_back(msg);
  }

  void log(const unsigned short& loglvl, const char* const filePath,
           const int& fileLine, const std::string& msg) override
  {
    log(loglvl,
        std::string{filePath} + ":" + std::to_string(fileLine) + " : " + msg);
  }

  void logfile([[maybe_unused]] const std::string& filepath) override {}

  void print([[maybe_unused]] const bool toPrintValue) override {}

  void level([[maybe_unused]] const unsigned short& nlvl) override {}

  const std::string& lvl_repr(
      [[maybe_unused]] const unsigned short& glvl) override
  {
    return lvlRepr;
  }

  void init([[maybe_unused]] const std::string& filepath,
            [[maybe_unused]] const unsigned short& nlvl,
            [[maybe_unused]] const bool toPrintValue) override
  {
  }

  std::vector<unsigned short> lvls;
  std::vector<std::string> msgs;
};

}  // namespace

/**
 * @brief Component test which checks that a real logger instance created and
 * owned by the library user is really used by the library code itself.
 *
 * The library is driven through the public LibraryFacade only and the logger
 * is handed over through the public LOG_INIT_REAL_LOGGER macro, so the test
 * stays valid for the branches which swap the underlying logger.
 */
class CTEST_LibraryRealLogger : public Test
{
 public:
  inline static const std::string app_log_file =
      CTEST_LibraryRealLogger_DATA_DIR "/CTEST_LibraryRealLogger.log";

  CTEST_LibraryRealLogger() { clear_log_file(); }

  ~CTEST_LibraryRealLogger()
  {
    LOG_INIT_REAL_LOGGER(originalRealLogger);
    clear_log_file();
  }

  /**
   * @brief Creates the library the very same way its user does and lets the
   * library perform its own logging initialization.
   */
  ILibPtr create_library() { return LibraryFacade::create_default_lib(); }

  std::string log_contents()
  {
    std::fstream log{app_log_file.c_str(), std::fstream::in};

    std::string rt;
    char c{0};

    while (log.get(c)) {
      rt += c;
    }

    log.close();

    return rt;
  }

  void clear_log_file()
  {
    std::fstream log{app_log_file.c_str(),
                     std::fstream::out | std::fstream::trunc};

    log.close();
  }

  const DefaultLogger::RealLoggerPtr originalRealLogger{LOG_REAL_LOGGER()};
};

TEST_F(CTEST_LibraryRealLogger, logger_interface_severities_stay_as_they_are)
{
  // The severity values cross the library boundary along with the class layout
  // of the interface they belong to, so a change to any of them is a change to
  // the ABI of every already installed library. See the logger::ILogger
  // documentation.
  EXPECT_EQ(logger::ILogger::LVL_ERROR, 1U);
  EXPECT_EQ(logger::ILogger::LVL_WARNING, 2U);
  EXPECT_EQ(logger::ILogger::LVL_INFO, 3U);
  EXPECT_EQ(logger::ILogger::LVL_DEBUG, 4U);
  EXPECT_EQ(logger::ILogger::LVL_TRACE, 5U);
}

TEST_F(CTEST_LibraryRealLogger, given_real_logger_is_adopted)
{
  const auto appLogger = std::make_shared<RecordingRealLogger>();

  LOG_INIT_REAL_LOGGER(appLogger);

  EXPECT_EQ(LOG_REAL_LOGGER(), appLogger);
}

TEST_F(CTEST_LibraryRealLogger, null_real_logger_leaves_the_previous_one)
{
  const auto appLogger = std::make_shared<RecordingRealLogger>();

  LOG_INIT_REAL_LOGGER(appLogger);
  LOG_INIT_REAL_LOGGER(nullptr);

  EXPECT_EQ(LOG_REAL_LOGGER(), appLogger);
}

TEST_F(CTEST_LibraryRealLogger, library_logs_reach_the_given_real_logger)
{
  static const std::string expect = "Your library implementation goes here!";

  const auto appLogger = std::make_shared<RecordingRealLogger>();

  LOG_INIT_REAL_LOGGER(appLogger);

  const auto lib = create_library();

  ASSERT_NE(lib, nullptr);

  EXPECT_TRUE(lib->libcall(LibraryFacade::create_library_context()));

  EXPECT_THAT(appLogger->msgs, Contains(EndsWith(expect)));
  EXPECT_THAT(appLogger->lvls, Contains(DefaultLogger::LVL_INFO));
}

TEST_F(CTEST_LibraryRealLogger, library_error_logs_reach_the_given_real_logger)
{
  static const std::string expect = "No valid library context pointer provided";

  const auto appLogger = std::make_shared<RecordingRealLogger>();

  LOG_INIT_REAL_LOGGER(appLogger);

  const auto lib = create_library();

  ASSERT_NE(lib, nullptr);

  EXPECT_FALSE(lib->libcall(nullptr));

  EXPECT_THAT(appLogger->msgs, Contains(EndsWith(expect)));
  EXPECT_THAT(appLogger->lvls, Contains(DefaultLogger::LVL_ERROR));
}

TEST_F(CTEST_LibraryRealLogger, given_interface_logger_is_adopted)
{
  const auto appLogger = std::make_shared<RecordingLogger>();

  LOG_INIT_REAL_LOGGER(appLogger);

  EXPECT_EQ(LOG_REAL_LOGGER(), appLogger);
}

TEST_F(CTEST_LibraryRealLogger, library_logs_reach_the_given_interface_logger)
{
  static const std::string expect = "Your library implementation goes here!";

  const auto appLogger = std::make_shared<RecordingLogger>();

  LOG_INIT_REAL_LOGGER(appLogger);

  const auto lib = create_library();

  ASSERT_NE(lib, nullptr);

  EXPECT_TRUE(lib->libcall(LibraryFacade::create_library_context()));

  EXPECT_THAT(appLogger->msgs, Contains(EndsWith(expect)));
  EXPECT_THAT(appLogger->lvls, Contains(DefaultLogger::LVL_INFO));
}

TEST_F(CTEST_LibraryRealLogger,
       library_error_logs_reach_the_given_interface_logger)
{
  static const std::string expect = "No valid library context pointer provided";

  const auto appLogger = std::make_shared<RecordingLogger>();

  LOG_INIT_REAL_LOGGER(appLogger);

  const auto lib = create_library();

  ASSERT_NE(lib, nullptr);

  EXPECT_FALSE(lib->libcall(nullptr));

  EXPECT_THAT(appLogger->msgs, Contains(EndsWith(expect)));
  EXPECT_THAT(appLogger->lvls, Contains(DefaultLogger::LVL_ERROR));
}

TEST_F(CTEST_LibraryRealLogger, library_logs_land_in_the_application_log_file)
{
  static const std::string expect = "No valid library context pointer provided";

  const auto appLogger = std::make_shared<RealDefaultLogger>();

  appLogger->init(app_log_file, MACRO_LVL_ERROR, false);

  LOG_INIT_REAL_LOGGER(appLogger);

  const auto lib = create_library();

  ASSERT_NE(lib, nullptr);
  EXPECT_EQ(LOG_REAL_LOGGER(), appLogger);

  EXPECT_FALSE(lib->libcall(nullptr));

  EXPECT_THAT(log_contents(), HasSubstr(expect));
}
