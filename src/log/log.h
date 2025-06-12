#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H

#include "src/log/boost-log/BoostLogController.h"

/**
 * @brief The logging init macros. Use them in the main function or
 * as by default is used in the app::ApplicationFactory::execute method.
 */
#define LOG_INIT(filepath, logLvl, printMessages) \
  boost_log::BoostLogController::init(filepath, logLvl, printMessages);
#define LOG_INIT_DEFAULTS() boost_log::BoostLogController::init();

/**
 * @brief Perform the error logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGE(msg)                                                     \
  BOOST_LOG_SEV(boost_log::BoostLogController::get_lg(),              \
                boost_log::logging::trivial::error)                   \
      << boost_log::BoostLogController::get_filename(__FILE__) << ":" \
      << __LINE__ << " : " << msg

/**
 * @brief Perform the info logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGI(msg)                                                     \
  BOOST_LOG_SEV(boost_log::BoostLogController::get_lg(),              \
                boost_log::logging::trivial::info)                    \
      << boost_log::BoostLogController::get_filename(__FILE__) << ":" \
      << __LINE__ << " : " << msg

/**
 * @brief Perform the warning logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGW(msg)                                                     \
  BOOST_LOG_SEV(boost_log::BoostLogController::get_lg(),              \
                boost_log::logging::trivial::warning)                 \
      << boost_log::BoostLogController::get_filename(__FILE__) << ":" \
      << __LINE__ << " : " << msg

/**
 * @brief Perform the debug logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGD(msg)                                                     \
  BOOST_LOG_SEV(boost_log::BoostLogController::get_lg(),              \
                boost_log::logging::trivial::debug)                   \
      << boost_log::BoostLogController::get_filename(__FILE__) << ":" \
      << __LINE__ << " : " << msg

/**
 * @brief Perform the trace logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGT(msg)                                                     \
  BOOST_LOG_SEV(boost_log::BoostLogController::get_lg(),              \
                boost_log::logging::trivial::trace)                   \
      << boost_log::BoostLogController::get_filename(__FILE__) << ":" \
      << __LINE__ << " : " << msg

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
