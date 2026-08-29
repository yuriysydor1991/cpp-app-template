#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ILOGGER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ILOGGER_CLASS_H

#include <memory>
#include <string>

#include "severity-macro-consts.h"

/**
 * @brief The implementation independent part of the logging subsystem
 * encapsulation namespace.
 */
namespace logger
{

/**
 * @brief An abstract class to define an interface for the logger
 * implementation variants. Implement it to replace the logging behaviour
 * without touching the src/log/log.h logging macroses.
 *
 * The default logger static proxy holds a pointer to this interface and not to
 * a particular logger class, so an implementation is free to wrap the log4cpp,
 * the boost::log or any other logging library instead of deriving from the
 * default real logger. Hand a new instance over through the
 * LOG_INIT_REAL_LOGGER macro to make the whole binary log through it. The proxy
 * itself lives in the default_logger namespace and is not installed, because
 * every derived library owns a copy of it - kept apart from the copies of the
 * other derived libraries by the library hidden symbol visibility - while this
 * interface is shared. So the macro, and the public
 * LibraryFacade::init_logger behind it, are the only names a library user
 * needs.
 *
 * Current file lives among the installable public headers, because the public
 * LibraryFacade::init_logger accepts this interface and the library user
 * implements it. Unlike the rest of them it deliberately carries neither the
 * version carrying library namespace nor the matching include guard, and it is
 * not marked with the TEMPLATE_LIB_API macro either. It is the single logging
 * contract every library derived from this template accepts, so one
 * application logger implementation serves all of the derived libraries an
 * application depends on at once, and the first installed copy of this header
 * which an application includes stands for all of them. The calls into an
 * implementation of it are plain virtual dispatch through the object own
 * virtual table, so nothing of it has to leave a shared object.
 *
 * That makes the class layout a binary interface shared between an application
 * and every derived library it loads, and the reason this header sits in the
 * installable directory instead of the private logging subsystem one: a change
 * to it is a change to the ABI of every library already installed. Extend it by
 * appending new methods after the existing ones only. Inserting a method,
 * reordering the existing ones, changing a signature or dropping one shifts the
 * virtual table slots, and an application built against one revision of this
 * file then calls a library built against another one through the wrong slot -
 * which is a wrong method at best and a segmentation fault as soon as the
 * arguments do not match. The LVL_* values cross that boundary the very same
 * way, so treat them as a part of the contract too.
 */
class ILogger
{
 public:
  /**
   * @brief The logger instance holder type.
   */
  using ILoggerPtr = std::shared_ptr<ILogger>;

  inline static constexpr const unsigned short LVL_ERROR = MACRO_LVL_ERROR;
  inline static constexpr const unsigned short LVL_WARNING = MACRO_LVL_WARNING;
  inline static constexpr const unsigned short LVL_INFO = MACRO_LVL_INFO;
  inline static constexpr const unsigned short LVL_DEBUG = MACRO_LVL_DEBUG;
  inline static constexpr const unsigned short LVL_TRACE = MACRO_LVL_TRACE;

  virtual ~ILogger() = default;
  ILogger() = default;

  /**
   * @brief Perform a logging message.
   *
   * @param loglvl The level of the log message. The lower the value - more
   * urgent the message.
   * @param msg The actual message for the log file or just stdout stream.
   */
  virtual void log(const unsigned short& loglvl, const std::string& msg) = 0;

  /**
   * @brief Perform a logging message.
   *
   * @param loglvl The level of the log message. The lower the value - more
   * urgent the message.
   * @param filePath The file path of the source of the log message. Usually
   * it's the __FILE__ macro value.
   * @param fileLine The file line of the source of the log message. Usually
   * it's the __LINE__ macro value.
   * @param msg The actual message for the log file or just stdout stream.
   */
  virtual void log(const unsigned short& loglvl, const char* const filePath,
                   const int& fileLine, const std::string& msg) = 0;

  /**
   * @brief Sets the new logfile file path.
   *
   * @param filepath The filepath where the log messages will be appended. If
   * empty string - nothing will be performed.
   */
  virtual void logfile(const std::string& filepath) = 0;

  /**
   * @brief Sets if the logger should print each log message into the stdout.
   *
   * @param toPrintValue New printing boolean value. If the true boolean value
   * given - all the log messages will be duplicated into the stdout.
   */
  virtual void print(const bool toPrintValue) = 0;

  /**
   * @brief Sets the maximum level of log message storage or printing. Above
   * given level all the log messages will be discarded.
   *
   * @param nlvl The new maximum level of log messages.
   */
  virtual void level(const unsigned short& nlvl) = 0;

  /**
   * @brief Searches for the string representation of the given log level.
   *
   * @param glvl The numerical log level for it's representation to search.
   *
   * @return Returns non-empty string representation of the given lvl.
   */
  virtual const std::string& lvl_repr(const unsigned short& glvl) = 0;

  /**
   * @brief Init the logger instance.
   *
   * @param filepath The file path where all the generated by the implemented
   * application messages will be stored in the filesystem. If non empty
   * filepath given and fail to open the file by path - exception is generated.
   * @param nlvl The new maximum log messages level. See the ILogger::level
   * method.
   * @param toPrintValue Defines if the logger should print messages to the
   * stdout stream. See the ILogger::print for more details.
   */
  virtual void init(const std::string& filepath, const unsigned short& nlvl,
                    const bool toPrintValue) = 0;
};

using ILoggerPtr = ILogger::ILoggerPtr;

}  // namespace logger

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ILOGGER_CLASS_H
