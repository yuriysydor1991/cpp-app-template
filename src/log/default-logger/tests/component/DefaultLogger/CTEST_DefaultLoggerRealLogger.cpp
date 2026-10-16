#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>

#include "RecordingLogger.h"
#include "RecordingRealLogger.h"
#include "src/log/ILogger.h"
#include "src/log/default-logger/DefaultLogger.h"
#include "src/log/default-logger/real-default-logger/RealDefaultLogger.h"

using namespace testing;
using namespace default_logger;

/**
 * @brief The DefaultLogger real logger instance holder fixture. It restores the
 * original real logger instance, so the rest of the tests stay unaffected.
 */
class CTEST_DefaultLoggerRealLogger : public Test
{
 public:
  ~CTEST_DefaultLoggerRealLogger()
  {
    DefaultLogger::real_logger(originalRealLogger);
  }

  const DefaultLogger::RealLoggerPtr originalRealLogger{
      DefaultLogger::real_logger()};
};

TEST_F(CTEST_DefaultLoggerRealLogger, real_logger_is_never_null)
{
  EXPECT_NE(DefaultLogger::real_logger(), nullptr);
}

TEST_F(CTEST_DefaultLoggerRealLogger, real_logger_instance_stays_the_same)
{
  EXPECT_EQ(DefaultLogger::real_logger(), DefaultLogger::real_logger());
}

TEST_F(CTEST_DefaultLoggerRealLogger, null_real_logger_is_ignored)
{
  DefaultLogger::real_logger(nullptr);

  EXPECT_EQ(DefaultLogger::real_logger(), originalRealLogger);
}

TEST_F(CTEST_DefaultLoggerRealLogger, given_real_logger_is_marked_as_adopted)
{
  DefaultLogger::real_logger(std::make_shared<RecordingRealLogger>());

  EXPECT_TRUE(DefaultLogger::real_logger_adopted());
}

TEST_F(CTEST_DefaultLoggerRealLogger, given_real_logger_receives_the_logs)
{
  static const std::string expect = "the given real logger message";

  const auto givenLogger = std::make_shared<RecordingRealLogger>();

  DefaultLogger::real_logger(givenLogger);

  EXPECT_EQ(DefaultLogger::real_logger(), givenLogger);

  DefaultLogger::log(DefaultLogger::LVL_ERROR, expect);

  EXPECT_EQ(givenLogger->lastLvl, DefaultLogger::LVL_ERROR);
  EXPECT_EQ(givenLogger->lastMsg, expect);
}

TEST_F(CTEST_DefaultLoggerRealLogger, given_real_logger_receives_the_file_logs)
{
  static const std::string expect = "the given real logger file message";

  const auto givenLogger = std::make_shared<RecordingRealLogger>();

  DefaultLogger::real_logger(givenLogger);

  DefaultLogger::log(DefaultLogger::LVL_ERROR, __FILE__, __LINE__, expect);

  EXPECT_EQ(givenLogger->lastLvl, DefaultLogger::LVL_ERROR);
  EXPECT_THAT(givenLogger->lastMsg, EndsWith(expect));
}

TEST_F(CTEST_DefaultLoggerRealLogger, real_logger_is_held_by_the_interface_ptr)
{
  EXPECT_TRUE(std::is_abstract_v<logger::ILogger>);
  EXPECT_TRUE((std::is_same_v<DefaultLogger::RealLoggerPtr,
                              std::shared_ptr<logger::ILogger>>));
  EXPECT_TRUE((std::is_base_of_v<logger::ILogger, RealDefaultLogger>));
}

TEST_F(CTEST_DefaultLoggerRealLogger, given_interface_logger_is_accepted)
{
  const auto givenLogger = std::make_shared<RecordingLogger>();

  DefaultLogger::real_logger(givenLogger);

  EXPECT_EQ(DefaultLogger::real_logger(), givenLogger);
  EXPECT_TRUE(DefaultLogger::real_logger_adopted());
}

TEST_F(CTEST_DefaultLoggerRealLogger, given_interface_logger_receives_the_logs)
{
  static const std::string expect = "the given interface logger message";

  const auto givenLogger = std::make_shared<RecordingLogger>();

  DefaultLogger::real_logger(givenLogger);

  DefaultLogger::log(DefaultLogger::LVL_ERROR, expect);

  EXPECT_EQ(givenLogger->lastLvl, DefaultLogger::LVL_ERROR);
  EXPECT_EQ(givenLogger->lastMsg, expect);
}

TEST_F(CTEST_DefaultLoggerRealLogger,
       given_interface_logger_receives_the_file_logs)
{
  static const std::string expect = "the given interface logger file message";
  static constexpr const char* const expectedFile = "the-caller-file.cpp";
  static constexpr const int expectedLine = 42;

  const auto givenLogger = std::make_shared<RecordingLogger>();

  DefaultLogger::real_logger(givenLogger);

  DefaultLogger::log(DefaultLogger::LVL_WARNING, expectedFile, expectedLine,
                     expect);

  EXPECT_EQ(givenLogger->lastLvl, DefaultLogger::LVL_WARNING);
  EXPECT_EQ(givenLogger->lastMsg, expect);
  EXPECT_EQ(givenLogger->lastFilePath, expectedFile);
  EXPECT_EQ(givenLogger->lastFileLine, expectedLine);
}

TEST_F(CTEST_DefaultLoggerRealLogger,
       given_interface_logger_receives_the_settings)
{
  static const std::string expect = "the-given-interface-logger.log";

  const auto givenLogger = std::make_shared<RecordingLogger>();

  DefaultLogger::real_logger(givenLogger);

  DefaultLogger::init(expect, DefaultLogger::LVL_DEBUG, false);

  EXPECT_EQ(givenLogger->lastLogfile, expect);
  EXPECT_EQ(givenLogger->lastLevel, DefaultLogger::LVL_DEBUG);
  EXPECT_FALSE(givenLogger->lastPrint);
}

TEST_F(CTEST_DefaultLoggerRealLogger, given_interface_logger_gives_the_lvl_repr)
{
  const auto givenLogger = std::make_shared<RecordingLogger>();

  DefaultLogger::real_logger(givenLogger);

  EXPECT_EQ(DefaultLogger::lvl_repr(DefaultLogger::LVL_TRACE),
            RecordingLogger::lvlRepr);
  EXPECT_EQ(givenLogger->lastReprLvl, DefaultLogger::LVL_TRACE);
}
