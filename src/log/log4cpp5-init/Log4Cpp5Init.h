#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LOG4CPPV5INIT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LOG4CPPV5INIT_CLASS_H

#include <log4cpp/Category.hh>
#include <string>

#include "project-global-decls.h"
#include "src/log/severity-macro-consts.h"

/**
 * @brief The namespace to encapsulate the log4cpp v5 init and log
 * code. Create an instance of the Log4Cpp5Init with appropriate parameters
 * values given to it's constructor to achieve desired log storage and output.
 */
namespace log4cpp5i
{

/**
 * @brief The log4cpp5 library controller. Inits the logging system.
 */
class Log4Cpp5Init
{
 public:
  inline static const unsigned short default_priority = MAX_LOG_LEVEL;
  inline static const std::string default_log_name =
      project_decls::PROJECT_NAME + "-" + project_decls::PROJECT_BUILD_VERSION +
      ".log";
  inline static const std::string default_conversation_pattern =
      "%d{%Y-%m-%d %H:%M:%S.%l} [%p] %m%n";

  ~Log4Cpp5Init();

  /**
   * @brief Create an instance of the Log4Cpp5Init with appropriate parameters
   * values given to it's constructor to achieve desired log storage and output.
   *
   * @param filepath The file path or name for the new log file to create or to
   * append new log messages. Defaults to Log4Cpp5Init::default_log_name.
   * @param nlvl The minimum log level to be printed/stored. Defaults to
   * default_priority value.
   * @param toPrintValue If the true boolean value passed - all the log message
   * will be printed into the stdout also.
   */
  explicit Log4Cpp5Init(
      const std::string& filepath = get_default_full_log_path(),
      const unsigned short& nlvl = default_priority,
      const bool toPrintValue = true);

  static std::string get_filename_only(const char* const filePath);

 protected:
  /**
   * @brief The log4cpp v5 initer.
   */
  void init();

  /**
   * @brief Inits the log4cpp5 file log storing.
   */
  void init_file();

  /**
   * @brief Inits the console log output if print specified.
   */
  void init_console();

  /**
   * @brief The graceful log4cpp deiniter.
   */
  static void deinit();

  static log4cpp::Priority::PriorityLevel get_log4cpp_priority(
      const unsigned short& prjsev);

 private:
  static std::string get_full_log_path(const std::string& logname);

  static std::string get_default_full_log_path();

  bool print{false};
  std::string log_name;
  log4cpp::Priority::PriorityLevel log_lvl;
};

}  // namespace log4cpp5i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LOG4CPPV5INIT_CLASS_H
