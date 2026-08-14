#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H

#include <sstream>

#include "src/log/default-logger/DefaultLogger.h"
#include "src/log/severity-macro-consts.h"

#ifndef LOG_INIT
/**
 * @brief The logging init macros. Use them in the main function or
 * as by default is used in the app::ApplicationFactory::execute method.
 */
#define LOG_INIT(filepath, logLvl, printMessages) \
  default_logger::DefaultLogger::init(filepath, logLvl, printMessages);
#endif  // LOG_INIT

#ifndef LOG_INIT_DEFAULTS
#define LOG_INIT_DEFAULTS() default_logger::DefaultLogger::init();
#endif  // LOG_INIT_DEFAULTS

#ifndef LOG_REAL_LOGGER
/**
 * @brief Returns the logger::ILoggerPtr real logger instance which stands
 * behind all the logging macroses. Pass it into a `lib`-style project through
 * it's LOG_INIT_REAL_LOGGER macro to make the whole binary log into the very
 * same logger instance.
 */
#define LOG_REAL_LOGGER() default_logger::DefaultLogger::real_logger()
#endif  // LOG_REAL_LOGGER

#ifndef LOG_INIT_REAL_LOGGER
/**
 * @brief The logging init macro which adopts the already existing real logger
 * instance instead of creating an own one. Use it in a `lib`-style project
 * initialization routine to accept the LOG_REAL_LOGGER value of the project
 * which uses that library.
 *
 * It accepts any logger::ILogger implementation, so it is also the place to
 * hand an own logging library wrapper over to the logging macroses.
 */
#define LOG_INIT_REAL_LOGGER(realLogger) \
  default_logger::DefaultLogger::real_logger(realLogger);
#endif  // LOG_INIT_REAL_LOGGER

#ifndef LOG_INIT_DEFAULTS_IF_OWN
/**
 * @brief The logging init macro which applies the default logging settings
 * only while no real logger instance was adopted through the
 * LOG_INIT_REAL_LOGGER macro. Use it instead of the LOG_INIT_DEFAULTS in a
 * `lib`-style project initialization routine to keep the log file, level and
 * printing settings of the adopted logger instance untouched.
 */
#define LOG_INIT_DEFAULTS_IF_OWN()                               \
  {                                                              \
    if (!default_logger::DefaultLogger::real_logger_adopted()) { \
      LOG_INIT_DEFAULTS();                                       \
    }                                                            \
  }
#endif  // LOG_INIT_DEFAULTS_IF_OWN

#ifndef LOG_BODY
/**
 * @brief The internal logger macro to define the general logging code body.
 */
#define LOG_BODY(LOGLVL, msg)                                      \
  {                                                                \
    std::stringstream logMessageContainer;                         \
    logMessageContainer << msg;                                    \
    default_logger::DefaultLogger::log(LOGLVL, __FILE__, __LINE__, \
                                       logMessageContainer.str()); \
  }
#endif  // LOG_BODY

#ifndef LOGE
/**
 * @brief Perform the error logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGE(msg) LOG_BODY(default_logger::DefaultLogger::LVL_ERROR, msg)
#endif  // LOGE

#ifndef LOGI
#if MAX_LOG_LEVEL >= MACRO_LOG_LEVEL_INFO
/**
 * @brief Perform the info logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGI(msg) LOG_BODY(default_logger::DefaultLogger::LVL_INFO, msg)
#else
#define LOGI(msg)
#endif  // MAX_LOG_LEVEL
#endif  // LOGI

#ifndef LOGW
#if MAX_LOG_LEVEL >= MACRO_LOG_LEVEL_WARNING
/**
 * @brief Perform the warning logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGW(msg) LOG_BODY(default_logger::DefaultLogger::LVL_WARNING, msg)
#else
#define LOGW(msg)
#endif  // MAX_LOG_LEVEL
#endif  // LOGW

#ifndef LOGD
#if MAX_LOG_LEVEL >= MACRO_LOG_LEVEL_DEBUG
/**
 * @brief Perform the debug logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGD(msg) LOG_BODY(default_logger::DefaultLogger::LVL_DEBUG, msg)
#else
#define LOGD(msg)
#endif  // MAX_LOG_LEVEL
#endif  // LOGD

#ifndef LOGT
#if MAX_LOG_LEVEL >= MACRO_LOG_LEVEL_TRACE
/**
 * @brief Perform the trace logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGT(msg) LOG_BODY(default_logger::DefaultLogger::LVL_TRACE, msg)
#else
#define LOGT(msg)
#endif  // MAX_LOG_LEVEL
#endif  // LOGT

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
