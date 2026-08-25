#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM3_GTKLOGBRIDGE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM3_GTKLOGBRIDGE_CLASS_H

#include <string>

#include "src/gtkmm3/gtkmm_includes.h"
#include "src/log/severity-macro-consts.h"

/**
 * @brief The toolkit messages routing encapsulation namespace.
 */
namespace Gtkmm3i::gtklog
{

/**
 * @brief Puts every message the toolkit reports into the application log.
 *
 * GTK, GDK, GIO, Pango, gtkmm and GLib itself report through the GLib
 * logging, which writes into the standard output and the standard error
 * streams of the process by it's own default writer. So without this class a
 * toolkit complaint is seen by whoever watches the terminal and by nobody
 * else: it never reaches the log file, it carries no timestamp of the
 * application format, no thread id and it obeys no level setting of the
 * application.
 *
 * The GtkLogBridge::install call replaces that default writer with an own one
 * and takes the two unstructured streams, the g_print and the g_printerr, over
 * as well, so a single log file carries the whole story of a run - the
 * application messages and the toolkit ones together.
 *
 * The writer is a process wide one, so it catches the GLib messages of every
 * library of the binary, not only the ones of the toolkit itself.
 */
class GtkLogBridge
{
 public:
  virtual ~GtkLogBridge() = default;
  GtkLogBridge() = default;

  /**
   * @brief Takes the GLib logging of the whole process over.
   *
   * Call it before anything of the toolkit is touched, so the complaints of
   * the toolkit start up itself are caught as well. The GLib accepts a writer
   * only once in the life of a process and kills the process on a second
   * attempt, so every call after the first one is silently ignored.
   */
  static void install();

 private:
  /**
   * @brief The GLib writer function which stands in the place of the default
   * one and receives every structured message of the process.
   *
   * @param logLevel The GLib level of the message with it's flags.
   * @param fields The message fields set - the MESSAGE, the GLIB_DOMAIN, the
   * CODE_FILE, the CODE_LINE and the CODE_FUNC ones.
   * @param fieldsCount The count of the fields in that set.
   * @param userData The unused pointer given to the g_log_set_writer_func.
   *
   * @return Always returns the G_LOG_WRITER_HANDLED value, which keeps the
   * GLib own behaviour of a fatal message: the g_error level and every level
   * the G_DEBUG variable makes fatal still abort the process afterwards.
   */
  static GLogWriterOutput writer(GLogLevelFlags logLevel,
                                 const GLogField* fields, gsize fieldsCount,
                                 gpointer userData);

  /**
   * @brief The g_print handler which logs the printed text with the info
   * level.
   *
   * @param text The text of the g_print call.
   */
  static void print_handler(const gchar* text);

  /**
   * @brief The g_printerr handler which logs the printed text with the
   * warning level.
   *
   * @param text The text of the g_printerr call.
   */
  static void printerr_handler(const gchar* text);

  /**
   * @brief Logs a text of the g_print or of the g_printerr stream, which
   * carries no level, no domain and no source coordinates of it's own.
   *
   * @param severity The application severity to log the text with.
   * @param text The text to log. A null pointer is ignored.
   */
  static void log_unstructured(const unsigned short severity,
                               const gchar* const text);

  /**
   * @brief Hands a ready toolkit message over to the logging macroses.
   *
   * @param severity The application severity to log the message with.
   * @param message The message text to log.
   */
  static void log_message(const unsigned short severity,
                          const std::string& message);

  /**
   * @brief Converts a GLib level into the application severity.
   *
   * The GLib error and the critical levels both stand for a broken invariant,
   * which is why both of them become the error severity. A library is free to
   * declare levels of it's own above the GLib ones, and those carry no
   * severity this application knows about, so they become the info one.
   *
   * @param logLevel The GLib level of a message with it's flags.
   *
   * @return Returns the MACRO_LVL_* severity of the given GLib level.
   */
  static unsigned short severity_of(const GLogLevelFlags logLevel);

  /**
   * @brief Tells whether the toolkit own gate drops the message, the very way
   * the default GLib writer decides it.
   *
   * @param logLevel The GLib level of the message with it's flags.
   * @param domain The GLIB_DOMAIN of the message or a null pointer while it
   * carries none.
   *
   * @return Returns true while the message is not to be reported at all.
   */
  static bool toolkit_would_drop(const GLogLevelFlags logLevel,
                                 const gchar* const domain);

  /**
   * @brief Searches for the value of a single GLib structured log field.
   *
   * @param fields The fields set the writer received.
   * @param fieldsCount The count of the fields in that set.
   * @param key The name of the field to search for.
   * @param value Receives the value of the found field. Stays untouched while
   * the field is absent.
   *
   * @return Returns true while the field was found and it's value was placed
   * into the value argument.
   */
  static bool field_value(const GLogField* const fields,
                          const gsize fieldsCount, const gchar* const key,
                          std::string& value);

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
   * here by hand because the toolkit level is known at a run time only.
   */
  inline static constexpr const unsigned short compiled_max_level =
      static_cast<unsigned short>(MAX_LOG_LEVEL);

  /**
   * @brief The domain the g_print and the g_printerr texts are logged under.
   * Those two streams carry no domain of their own.
   */
  inline static constexpr const char* const print_domain = "GLib print";

  /**
   * @brief Whether the GLib logging is taken over already.
   */
  inline static bool installed{false};
};

}  // namespace Gtkmm3i::gtklog

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMM3_GTKLOGBRIDGE_CLASS_H
