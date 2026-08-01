#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H

#include <sstream>

#include "src/log/default-logger/DefaultLogger.h"

/**
 * @brief The logging init macros. Use them in the main function or
 * as by default is used in the app::ApplicationFactory::execute method.
 */
#define LOG_INIT(filepath, logLvl, printMessages) \
  default_logger::DefaultLogger::init(filepath, logLvl, printMessages);

#ifndef LOG_INIT_PATH
#define LOG_INIT_PATH(filepath) default_logger::DefaultLogger::init(filepath);
#endif  // LOG_INIT_PATH

#define LOG_INIT_DEFAULTS() default_logger::DefaultLogger::init();

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

/**
 * @brief Perform the error logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGE(msg) LOG_BODY(default_logger::DefaultLogger::LVL_ERROR, msg)

/**
 * @brief Perform the info logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGI(msg) LOG_BODY(default_logger::DefaultLogger::LVL_INFO, msg)

/**
 * @brief Perform the warning logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGW(msg) LOG_BODY(default_logger::DefaultLogger::LVL_WARNING, msg)

/**
 * @brief Perform the debug logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGD(msg) LOG_BODY(default_logger::DefaultLogger::LVL_DEBUG, msg)

/**
 * @brief Perform the trace logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGT(msg) LOG_BODY(default_logger::DefaultLogger::LVL_TRACE, msg)

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
