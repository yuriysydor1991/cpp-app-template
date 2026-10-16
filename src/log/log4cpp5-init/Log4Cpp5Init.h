#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LOG4CPPV5INIT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LOG4CPPV5INIT_CLASS_H

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <string>

#include "project-global-decls.h"
#include "src/log/severity-macro-consts.h"

/**
 * @brief The namespace to encapsulate the log4cpp v5 init and log
 * code. Call the Log4Cpp5Init::init with appropriate parameters values to
 * achieve desired log storage and output.
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

  /**
   * @brief The log4cpp knows no trace priority, so the trace messages take
   * one between the DEBUG and the NOTSET ones (printed as DEBUG).
   */
  static constexpr log4cpp::Priority::Value trace_priority =
      log4cpp::Priority::DEBUG + 50;

  /**
   * @brief (Re)initializes the log4cpp root category: the appenders of any
   * previous call are replaced, so the log storage and output follow the last
   * call only. If the log file can't be opened a warning is printed into the
   * stderr and the messages go into the stdout only.
   *
   * @param filepath The file path or name for the new log file to create or to
   * append new log messages. Defaults to Log4Cpp5Init::default_log_name.
   * @param nlvl The minimum log level to be printed/stored. Defaults to
   * default_priority value.
   * @param toPrintValue If the true boolean value passed - all the log message
   * will be printed into the stdout also.
   */
  static void init(const std::string& filepath = get_default_full_log_path(),
                   const unsigned short& nlvl = default_priority,
                   bool toPrintValue = true);

  static std::string get_filename_only(const char* filePath);

  static log4cpp::Priority::Value get_log4cpp_priority(
      const unsigned short& prjsev);

 private:
  /**
   * @brief Adds the file appender to the given category.
   *
   * @return Returns false if the log file can't be opened.
   */
  static bool add_file_appender(log4cpp::Category& root,
                                const std::string& filepath);

  static void add_console_appender(log4cpp::Category& root);

  static std::string get_full_log_path(const std::string& logname);

  static std::string get_default_full_log_path();
};

}  // namespace log4cpp5i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LOG4CPPV5INIT_CLASS_H
