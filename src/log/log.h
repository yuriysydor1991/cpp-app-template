#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H

#include <log4cpp/Category.hh>

#include "src/log/log4cpp5-init/Log4Cpp5Init.h"
#include "src/log/severity-macro-consts.h"

#ifndef LOG_INIT
/**
 * @brief The logging init macros. Use them in the main function or
 * as by default is used in the app::ApplicationFactory::execute method.
 */
#define LOG_INIT(filepath, logLvl, printMessages)                       \
  {                                                                     \
    static log4cpp5i::Log4Cpp5Init log4cpp5initer{(filepath), (logLvl), \
                                                  (printMessages)};     \
  }
#endif  // LOG_INIT

#ifndef LOG_INIT_DEFAULTS
#define LOG_INIT_DEFAULTS()                        \
  {                                                \
    static log4cpp5i::Log4Cpp5Init log4cpp5initer; \
  }
#endif  // LOG_INIT_DEFAULTS

#ifndef LOG_BODY
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
#endif  // LOG_BODY

#ifndef LOGE
/**
 * @brief Perform the error logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGE(msg)                                                    \
  log4cpp::Category::getRoot().errorStream()                         \
      << log4cpp5i::Log4Cpp5Init::get_filename_only(__FILE__) << ":" \
      << __LINE__ << " - " << msg
#endif  // LOGE

#ifndef LOGI
#if MAX_LOG_LEVEL >= MACRO_LOG_LEVEL_INFO
/**
 * @brief Perform the info logging.
 *
 * @param msg The logging message which may use the << operator
 * and each of the log elements MUST be converted into the std::string.
 */
#define LOGI(msg)                                                    \
  log4cpp::Category::getRoot().noticeStream()                        \
      << log4cpp5i::Log4Cpp5Init::get_filename_only(__FILE__) << ":" \
      << __LINE__ << " - " << msg
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
#define LOGW(msg)                                                    \
  log4cpp::Category::getRoot().warnStream()                          \
      << log4cpp5i::Log4Cpp5Init::get_filename_only(__FILE__) << ":" \
      << __LINE__ << " - " << msg
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
#define LOGD(msg)                                                    \
  log4cpp::Category::getRoot().debugStream()                         \
      << log4cpp5i::Log4Cpp5Init::get_filename_only(__FILE__) << ":" \
      << __LINE__ << " - " << msg
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
#define LOGT(msg)                                                    \
  log4cpp::Category::getRoot().infoStream()                          \
      << log4cpp5i::Log4Cpp5Init::get_filename_only(__FILE__) << ":" \
      << __LINE__ << " - " << msg
#else
#define LOGT(msg)
#endif  // MAX_LOG_LEVEL
#endif  // LOGT

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
