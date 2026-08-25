#include "src/gtkmm3/log/GtkLogBridge.h"

#include <cstring>
#include <filesystem>
#include <string>

#include "src/log/log.h"

namespace Gtkmm3i::gtklog
{

void GtkLogBridge::install()
{
  // The GLib accepts a writer only once in the life of a process and kills the
  // process on a second attempt, so a repeated install is ignored instead.
  if (installed) {
    return;
  }

  installed = true;

  g_log_set_writer_func(&GtkLogBridge::writer, nullptr, nullptr);

  g_set_print_handler(&GtkLogBridge::print_handler);
  g_set_printerr_handler(&GtkLogBridge::printerr_handler);

  LOGD("The toolkit messages are routed into the application log");
}

GLogWriterOutput GtkLogBridge::writer(GLogLevelFlags logLevel,
                                      const GLogField* fields,
                                      gsize fieldsCount, gpointer userData)
{
  static_cast<void>(userData);

  std::string domain;

  const bool hasDomain =
      field_value(fields, fieldsCount, "GLIB_DOMAIN", domain);

  // The first gate is the toolkit own one: the info and the debug messages are
  // reported only while their domain is switched on through the
  // G_MESSAGES_DEBUG environment variable. That is the behaviour every GTK
  // application has and replacing the writer must not change it.
  if (toolkit_would_drop(logLevel, hasDomain ? domain.c_str() : nullptr)) {
    return G_LOG_WRITER_HANDLED;
  }

  const unsigned short severity = severity_of(logLevel);

  // The second gate is the MAX_LOG_LEVEL of the build - the very one the
  // application own messages obey. It stands in front of the message building
  // work as well, so a build which does not keep the debug level does not even
  // assemble a toolkit debug message.
  if (!build_keeps(severity)) {
    return G_LOG_WRITER_HANDLED;
  }

  std::string message;

  if (!field_value(fields, fieldsCount, "MESSAGE", message)) {
    return G_LOG_WRITER_HANDLED;
  }

  std::string file;
  std::string line;
  std::string function;

  const bool hasFile = field_value(fields, fieldsCount, "CODE_FILE", file);
  const bool hasLine = field_value(fields, fieldsCount, "CODE_LINE", line);
  const bool hasFunction =
      field_value(fields, fieldsCount, "CODE_FUNC", function);

  std::string text;

  if (hasDomain) {
    text += domain + ": ";
  }

  // The GTK is built with the structured logging, so it's messages name the
  // toolkit source file, line and function they came from. The GLib itself
  // reports most of it's own troubles through the older path, which carries
  // none of those fields, and then the domain alone stands at the front.
  //
  // Only the file name of the toolkit path is kept, the very way the logger
  // shortens the application own __FILE__ values, so both kinds of a log line
  // name their source alike.
  if (hasFile) {
    text += std::filesystem::path{file}.filename().string();

    if (hasLine) {
      text += ":" + line;
    }

    text += ": ";
  }

  if (hasFunction) {
    text += function + ": ";
  }

  text += message;

  log_message(severity, text);

  return G_LOG_WRITER_HANDLED;
}

void GtkLogBridge::print_handler(const gchar* text)
{
  log_unstructured(MACRO_LVL_INFO, text);
}

void GtkLogBridge::printerr_handler(const gchar* text)
{
  log_unstructured(MACRO_LVL_WARNING, text);
}

void GtkLogBridge::log_unstructured(const unsigned short severity,
                                    const gchar* const text)
{
  if (text == nullptr || !build_keeps(severity)) {
    return;
  }

  std::string message{print_domain};

  message += ": ";
  message += text;

  // Both of those streams carry the line ending of a terminal, and the logger
  // appends an own one to every message it receives.
  while (!message.empty() &&
         (message.back() == '\n' || message.back() == '\r')) {
    message.pop_back();
  }

  log_message(severity, message);
}

void GtkLogBridge::log_message(const unsigned short severity,
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

unsigned short GtkLogBridge::severity_of(const GLogLevelFlags logLevel)
{
  if ((logLevel & (G_LOG_LEVEL_ERROR | G_LOG_LEVEL_CRITICAL)) != 0) {
    return MACRO_LVL_ERROR;
  }

  if ((logLevel & G_LOG_LEVEL_WARNING) != 0) {
    return MACRO_LVL_WARNING;
  }

  if ((logLevel & G_LOG_LEVEL_DEBUG) != 0) {
    return MACRO_LVL_DEBUG;
  }

  // The G_LOG_LEVEL_MESSAGE, the G_LOG_LEVEL_INFO and every level a library
  // declares above the GLib ones.
  return MACRO_LVL_INFO;
}

bool GtkLogBridge::toolkit_would_drop(const GLogLevelFlags logLevel,
                                      const gchar* const domain)
{
#if GLIB_CHECK_VERSION(2, 68, 0)
  return g_log_writer_default_would_drop(logLevel, domain) != FALSE;
#else
  // The GLib of this build carries no g_log_writer_default_would_drop, which
  // arrived with the 2.68 one, so the rule of it's default writer is applied
  // by hand: an info or a debug message of a domain the G_MESSAGES_DEBUG
  // variable does not name is dropped and every other level is kept.
  if ((logLevel & (G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG)) == 0) {
    return false;
  }

  const gchar* const switchedOn = g_getenv("G_MESSAGES_DEBUG");

  if (switchedOn == nullptr) {
    return true;
  }

  if (g_strcmp0(switchedOn, "all") == 0) {
    return false;
  }

  return domain == nullptr || std::strstr(switchedOn, domain) == nullptr;
#endif  // GLIB_CHECK_VERSION
}

bool GtkLogBridge::field_value(const GLogField* const fields,
                               const gsize fieldsCount, const gchar* const key,
                               std::string& value)
{
  if (fields == nullptr) {
    return false;
  }

  for (gsize iter = 0U; iter < fieldsCount; ++iter) {
    const GLogField& field = fields[iter];

    if (field.value == nullptr || g_strcmp0(field.key, key) != 0) {
      continue;
    }

    const gchar* const text = static_cast<const gchar*>(field.value);

    // A negative length marks a null terminated value, which is what every
    // field of the whole toolkit diagnostics is. Any other one is counted and
    // carries no null terminator to rely on.
    value = (field.length < 0)
                ? std::string{text}
                : std::string{
                      text, static_cast<std::string::size_type>(field.length)};

    return true;
  }

  return false;
}

}  // namespace Gtkmm3i::gtklog
