#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H

#include <gmock/gmock.h>

#include <sstream>
#include <string>

#include "src/lib/facade/public/ILogger.h"

class logMock
{
 public:
  inline static testing::MockFunction<void(const std::string& filepath,
                                           const unsigned short& logLvl,
                                           const bool printMessages)>
      LOG_INIT;
  inline static testing::MockFunction<void()> LOG_INIT_DEFAULTS;
  inline static testing::MockFunction<void(const std::string& filepath)>
      LOG_INIT_PATH;
  inline static testing::MockFunction<void()> LOG_INIT_DEFAULTS_IF_OWN;
  inline static testing::MockFunction<void(const logger::ILoggerPtr&)>
      LOG_INIT_REAL_LOGGER;

  inline static testing::MockFunction<void(const std::string&)> LOGE;
  inline static testing::MockFunction<void(const std::string&)> LOGI;
  inline static testing::MockFunction<void(const std::string&)> LOGW;
  inline static testing::MockFunction<void(const std::string&)> LOGD;
  inline static testing::MockFunction<void(const std::string&)> LOGT;

  /// @brief The LOG_INIT_PATH macro result, a false one stands for a log file
  /// which can not be opened.
  inline static bool log_init_path_result{true};

  /// @brief Gives the LOG_INIT macro result the real one gives on success.
  static bool log_init(const std::string& filepath,
                       const unsigned short& logLvl, const bool printMessages)
  {
    LOG_INIT.AsStdFunction()(filepath, logLvl, printMessages);

    return true;
  }

  /// @brief Gives the logMock::log_init_path_result as the LOG_INIT_PATH macro
  /// result.
  static bool log_init_path(const std::string& filepath)
  {
    LOG_INIT_PATH.AsStdFunction()(filepath);

    return log_init_path_result;
  }
};

#define LOG_INIT(filepath, logLvl, printMessages) \
  logMock::log_init(filepath, logLvl, printMessages)
#define LOG_INIT_DEFAULTS() logMock::LOG_INIT_DEFAULTS.AsStdFunction()()
#define LOG_INIT_PATH(filepath) logMock::log_init_path(filepath)
#define LOG_INIT_DEFAULTS_IF_OWN() \
  logMock::LOG_INIT_DEFAULTS_IF_OWN.AsStdFunction()()
#define LOG_INIT_REAL_LOGGER(realLogger) \
  logMock::LOG_INIT_REAL_LOGGER.AsStdFunction()(realLogger)

#define LOG_MOCK_BODY(LOGFUNC, msg)                     \
  do {                                                  \
    std::stringstream logMessageContainer;              \
    logMessageContainer << msg;                         \
    LOGFUNC.AsStdFunction()(logMessageContainer.str()); \
  } while (0)

#define LOGE(msg) LOG_MOCK_BODY(logMock::LOGE, msg)
#define LOGI(msg) LOG_MOCK_BODY(logMock::LOGI, msg)
#define LOGW(msg) LOG_MOCK_BODY(logMock::LOGW, msg)
#define LOGD(msg) LOG_MOCK_BODY(logMock::LOGD, msg)
#define LOGT(msg) LOG_MOCK_BODY(logMock::LOGT, msg)

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
