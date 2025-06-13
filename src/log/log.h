#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H

#include <sstream>

#include "src/log/boost-log/BoostLogController.h"
#include "src/log/severity-macro-consts.h"

#ifndef LOG_INIT
/**
 * @brief The logging init macros. Use them in the main function or
 * as by default is used in the app::ApplicationFactory::execute method.
 */
#define LOG_INIT(filepath, logLvl, printMessages) \
  boost_log::BoostLogController::init(filepath, logLvl, printMessages);
#endif  // LOG_INIT

#ifndef LOG_INIT_DEFAULTS
#define LOG_INIT_DEFAULTS() boost_log::BoostLogController::init();
#endif  // LOG_INIT_DEFAULTS

#ifndef LOG_BODY
/**
 * @brief The internal logger macro to define the general logging code body.
 */
#define LOG_BODY(sev, msg)                                            \
  BOOST_LOG_SEV(boost_log::BoostLogController::get_lg(),              \
                boost_log::logging::trivial::sev)                     \
      << boost_log::BoostLogController::get_filename(__FILE__) << ":" \
      << __LINE__ << " : " << msg
#endif  // LOG_BODY

#ifndef LOGE
/**
 * @brief Perform the error logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGE(msg) LOG_BODY(error, msg)
#endif  // LOGE

#ifndef LOGI
#if MAX_LOG_LEVEL >= MACRO_LOG_LEVEL_INFO
/**
 * @brief Perform the info logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGI(msg) LOG_BODY(info, msg)
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
#define LOGW(msg) LOG_BODY(warning, msg)
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
#define LOGD(msg) LOG_BODY(debug, msg)
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
#define LOGT(msg) LOG_BODY(trace, msg)
#else
#define LOGT(msg)
#endif  // MAX_LOG_LEVEL
#endif  // LOGT

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
