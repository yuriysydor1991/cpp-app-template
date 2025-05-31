#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H

#include <sstream>

#include "src/log/simple-logger/SimpleLogger.h"

/**
 * @brief The logging init macros. Use them in the main function or
 * as by default is used in the app::ApplicationFactory::execute method.
 */
#define LOG_INIT(filepath, logLvl, printMessages) \
  simple_logger::SimpleLogger::init(filepath, logLvl, printMessages);
#define LOG_INIT_DEFAULTS() simple_logger::SimpleLogger::init();

/**
 * @brief The internal logger macro to define the general logging code body.
 */
#define LOG_BODY(LOGLVL, msg)                                    \
  {                                                              \
    std::stringstream logMessageContainer;                       \
    logMessageContainer << msg;                                  \
    simple_logger::SimpleLogger::log(LOGLVL, __FILE__, __LINE__, \
                                     logMessageContainer.str()); \
  }

/**
 * @brief Perform the error logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGE(msg) LOG_BODY(simple_logger::SimpleLogger::LVL_ERROR, msg)

/**
 * @brief Perform the info logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGI(msg) LOG_BODY(simple_logger::SimpleLogger::LVL_INFO, msg)

/**
 * @brief Perform the warning logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGW(msg) LOG_BODY(simple_logger::SimpleLogger::LVL_WARNING, msg)

/**
 * @brief Perform the debug logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGD(msg) LOG_BODY(simple_logger::SimpleLogger::LVL_DEBUG, msg)

/**
 * @brief Perform the trace logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGT(msg) LOG_BODY(simple_logger::SimpleLogger::LVL_TRACE, msg)

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
