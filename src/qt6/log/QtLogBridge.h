#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QT6_QTLOGBRIDGE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QT6_QTLOGBRIDGE_CLASS_H

#include <QtGlobal>
#include <string>

#include "src/log/severity-macro-consts.h"

/**
 * @brief The toolkit messages routing encapsulation namespace.
 */
namespace Qt6i::qtlog
{

/**
 * @brief Puts every message the toolkit reports into the application log.
 *
 * Qt Core, Qt Gui, Qt Quick, the QML engine, the platform plugins and every
 * other module report through the Qt logging, which writes into the standard
 * error stream of the process by it's own default message handler. So without
 * this class a toolkit complaint is seen by whoever watches the terminal and
 * by nobody else: it never reaches the log file, it carries no timestamp of
 * the application format, no thread id and it obeys no level setting of the
 * application.
 *
 * The QtLogBridge::install call replaces that default handler with an own one,
 * so a single log file carries the whole story of a run - the application
 * messages and the toolkit ones together.
 *
 * The handler is a process wide one, so it catches the Qt messages of every
 * library of the binary, not only the ones of the toolkit itself. The QML
 * console calls of the interface files land in it as well, because the QML
 * console is a front of the very same Qt logging.
 */
class QtLogBridge
{
 public:
  virtual ~QtLogBridge() = default;
  QtLogBridge() = default;

  /**
   * @brief Takes the Qt logging of the whole process over.
   *
   * Call it before anything of the toolkit is touched - the message handler
   * needs no QCoreApplication instance behind it - so the complaints of the
   * application object construction and of the platform plugin start up are
   * caught as well. Every call after the first one is ignored, so that the
   * bridge never takes the single handler slot away from a handler the
   * application installed for itself later on.
   */
  static void install();

 private:
  /**
   * @brief The Qt message handler which stands in the place of the default one
   * and receives every message of the process.
   *
   * @param type The Qt type of the message, which carries it's severity.
   * @param context The source coordinates and the logging category of the
   * message. Every field of it is an optional one.
   * @param message The message text itself, with no severity and no source
   * coordinates in it.
   */
  static void handler(QtMsgType type, const QMessageLogContext& context,
                      const QString& message);

  /**
   * @brief Hands a ready toolkit message over to the logging macroses.
   *
   * @param severity The application severity to log the message with.
   * @param message The message text to log.
   */
  static void log_message(const unsigned short severity,
                          const std::string& message);

  /**
   * @brief Converts a Qt message type into the application severity.
   *
   * The Qt fatal and critical types both stand for a broken invariant, which
   * is why both of them become the error severity. The Qt logging declares no
   * type below the debug one, so the trace severity of the application is
   * never reached from here.
   *
   * @param type The Qt type of a message.
   *
   * @return Returns the MACRO_LVL_* severity of the given Qt message type.
   */
  static unsigned short severity_of(const QtMsgType type);

  /**
   * @brief Builds the front of a log line out of the message context - the
   * logging category, the source file, the source line and the function which
   * reported the message.
   *
   * Every one of those is an optional field: a release build of a Qt module
   * carries no source coordinates at all, because the QT_MESSAGELOGCONTEXT
   * definition of the build decides whether they are assembled, and an
   * uncategorized message carries the default category which is not named in
   * the log line, exactly the way the Qt own default message pattern leaves it
   * out.
   *
   * @param context The context the message handler received.
   *
   * @return Returns the ready front of the log line, an empty string included
   * while the context carries nothing at all.
   */
  static std::string source_of(const QMessageLogContext& context);

  /**
   * @brief Tells whether this build keeps the given severity at all.
   *
   * The error severity is always kept, the very way the LOGE macro of
   * src/log/log.h carries no compile time test of it's own, because the error
   * level is the lowest one a build may keep.
   *
   * @param severity The MACRO_LVL_* severity to ask about.
   *
   * @return Returns true while a message of that severity is to be logged.
   */
  static constexpr bool build_keeps(const unsigned short severity)
  {
    return severity == MACRO_LVL_ERROR || severity <= compiled_max_level;
  }

  /**
   * @brief The highest severity this build keeps. It is the very
   * MAX_LOG_LEVEL the logging macroses of src/log/log.h are gated on, applied
   * here by hand because the toolkit message type is known at a run time only.
   */
  inline static constexpr const unsigned short compiled_max_level =
      static_cast<unsigned short>(MAX_LOG_LEVEL);

  /**
   * @brief The name of the category every message which names none of it's own
   * carries. It is left out of the log line, the very way the Qt own default
   * message pattern leaves it out.
   */
  inline static constexpr const char* const default_category = "default";

  /**
   * @brief Whether the Qt logging is taken over already.
   */
  inline static bool installed{false};
};

}  // namespace Qt6i::qtlog

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QT6_QTLOGBRIDGE_CLASS_H
