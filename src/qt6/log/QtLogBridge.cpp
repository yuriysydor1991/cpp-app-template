#include "src/qt6/log/QtLogBridge.h"

#include <QString>
#include <QtGlobal>
#include <cstring>
#include <filesystem>
#include <string>

#include "src/log/log.h"

namespace Qt6i::qtlog
{

void QtLogBridge::install()
{
  // The single handler slot of the process is taken once. Qt replaces a
  // handler as many times as it is asked to, unlike the GLib logging which
  // kills the process on a second writer, so the guard is here to keep the
  // bridge out of the way of a handler the application installs for itself.
  if (installed) {
    return;
  }

  installed = true;

  qInstallMessageHandler(&QtLogBridge::handler);

  LOGD("The toolkit messages are routed into the application log");
}

void QtLogBridge::handler(QtMsgType type, const QMessageLogContext& context,
                          const QString& message)
{
  const unsigned short severity = severity_of(type);

  // The gate of the build - the very MAX_LOG_LEVEL the application own
  // messages obey. It stands in front of the message building work as well, so
  // a build which does not keep the debug level does not even assemble a
  // toolkit debug message.
  //
  // The gate of the toolkit itself needs no line of code here: unlike the GLib
  // one, Qt asks it's logging categories before it calls a message handler at
  // all, so a message this build of the toolkit does not report never arrives.
  if (!build_keeps(severity)) {
    return;
  }

  std::string text = source_of(context);

  text += message.toStdString();

  // A Qt message carries no line ending of it's own, but a text handed to the
  // qDebug and it's neighbours by hand may well carry one, and the logger
  // appends an own one to every message it receives.
  while (!text.empty() && (text.back() == '\n' || text.back() == '\r')) {
    text.pop_back();
  }

  log_message(severity, text);
}

void QtLogBridge::log_message(const unsigned short severity,
                              const std::string& message)
{
  // The logging macroses and not the logger itself, so the bridge keeps
  // working on the branches which replace the whole logging implementation,
  // and so that the MAX_LOG_LEVEL of the build compiles the calls it does not
  // keep away. The price of it is the source coordinates of the log line: they
  // name this very file, while the toolkit ones stand inside the message text.
  switch (severity) {
    case MACRO_LVL_ERROR:
      LOGE(message);
      break;
    case MACRO_LVL_WARNING:
      LOGW(message);
      break;
    case MACRO_LVL_DEBUG:
      LOGD(message);
      break;
    default:
      LOGI(message);
      break;
  }
}

unsigned short QtLogBridge::severity_of(const QtMsgType type)
{
  // A switch and not a comparison, because the numeric order of the QtMsgType
  // values is a Qt internal business: the QtInfoMsg one stands behind the
  // QtFatalMsg in the Qt6 declaration of that enumeration and in front of the
  // QtWarningMsg in the Qt7 one.
  switch (type) {
    // The QtSystemMsg is not named here, being the very QtCriticalMsg value
    // under an older name of it.
    case QtFatalMsg:
    case QtCriticalMsg:
      return MACRO_LVL_ERROR;
    case QtWarningMsg:
      return MACRO_LVL_WARNING;
    case QtDebugMsg:
      return MACRO_LVL_DEBUG;
    case QtInfoMsg:
    default:
      return MACRO_LVL_INFO;
  }
}

std::string QtLogBridge::source_of(const QMessageLogContext& context)
{
  std::string front;

  // The uncategorized messages of the qDebug and of it's neighbours carry the
  // default category, which is left out of the log line - the very way the Qt
  // own default message pattern leaves it out. The named categories of the
  // toolkit modules (qt.qml.import, qt.quick.mouse and the rest of them) and
  // the QML one stand at the front of the message instead.
  if (context.category != nullptr && context.category[0] != '\0' &&
      std::strcmp(context.category, default_category) != 0) {
    front += context.category;
    front += ": ";
  }

  // Only the file name of the toolkit path is kept, the very way the logger
  // shortens the application own __FILE__ values, so both kinds of a log line
  // name their source alike. The QML files name themselves with an URL, and
  // it's last element is the file name as well.
  if (context.file != nullptr && context.file[0] != '\0') {
    front += std::filesystem::path{context.file}.filename().string();

    // A context which carries a file but no line at all names the zero line,
    // which is worth no place in the log message.
    if (context.line > 0) {
      front += ":" + std::to_string(context.line);
    }

    front += ": ";
  }

  if (context.function != nullptr && context.function[0] != '\0') {
    front += context.function;
    front += ": ";
  }

  return front;
}

}  // namespace Qt6i::qtlog
