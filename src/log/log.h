#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H

#include <log4cpp/Category.hh>

#include "src/log/log4cpp5-init/Log4Cpp5Init.h"

/**
 * @brief The logging init macros. Use them in the main function or
 * as by default is used in the app::ApplicationFactory::execute method.
 */
#define LOG_INIT(filepath, logLvl, printMessages)                       \
  {                                                                     \
    static log4cpp5i::Log4Cpp5Init log4cpp5initer{(filepath), (logLvl), \
                                                  (printMessages)};     \
  }
#define LOG_INIT_DEFAULTS()                        \
  {                                                \
    static log4cpp5i::Log4Cpp5Init log4cpp5initer; \
  }

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

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
