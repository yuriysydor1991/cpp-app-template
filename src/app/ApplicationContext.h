#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H

#include <atomic>
#include <string>
#include <vector>

#include "src/app/IDBConnection.h"

namespace app
{

class IDBConnection;

/**
 * @brief The class that holds necessary information for the application
 * to run properly.
 *
 * May hold parsed parameters, configuration values and error messages
 * with application status code. The command line parameters are parsed by
 * the CommandLineParser class instance inside the ApplicationFactory class.
 * The ApplicationHelpPrinter class instance is printing command line help
 * for available command line parameters that may be stored in
 * the current class instance (if registered properly).
 *
 * All the data members are private ones, so the held data is reachable through
 * the appropriate access methods only.
 */
class ApplicationContext
{
 public:
  /**
   * @brief An ApplicationContext constructor.
   *
   * @param gargc Command line arguments count passed by the OS through the main
   * executable function that will be referenced in the margc member field.
   * @param gargv  The command line arguments array passed by the OS through
   * the main executable function that will be referenced in the margv member
   * field.
   */
  ApplicationContext(int& gargc, char**& gargv);

  /// @brief Provides the referenced command line arguments count. The
  /// reference is modifiable, since toolkits like Gtk::Application::create and
  /// glutInit consume argc/argv through a non constant one.
  int& get_argc() const;

  /// @brief Provides the referenced command line arguments array. Modifiable
  /// for the same reason as ApplicationContext::get_argc.
  char**& get_argv() const;

  /// @brief Tells if the ApplicationFactory should create and run an
  /// ApplicationHelpPrinter instance.
  bool get_print_help_and_exit() const;

  /// @brief Sets the help printing flag. Only the ApplicationFactory reads it.
  void set_print_help_and_exit(const bool newValue);

  /// @brief Tells if the ApplicationFactory should create and run an
  /// ApplicationVersionPrinter instance.
  bool get_print_version_and_exit() const;

  /// @brief Sets the version printing flag. Only the ApplicationFactory reads
  /// it.
  void set_print_version_and_exit(const bool newValue);

  /// @brief Provides the accumulated errors descriptions.
  const std::vector<std::string>& get_errors() const;

  /// @brief Pushes a new error description into the merrors field.
  void push_error(const std::string& errorDescription);

  /// @brief Tells if the application was asked to stop. Atomic, so it is safe
  /// to poll it from any thread.
  bool get_stop() const;

  /// @brief Sets the application stop flag. Raise it to ask the running
  /// routines to return from IApplication::run.
  void set_stop(const bool newValue);

  /// @brief Firebird database name, path or alias.
  const std::string& get_fb_dbname() const;

  /// @brief Sets the firebird database name, path or alias.
  void set_fb_dbname(const std::string& newValue);

  /// @brief Firebird user name.
  const std::string& get_fb_user() const;

  /// @brief Sets the firebird user name.
  void set_fb_user(const std::string& newValue);

  /// @brief Firebird user password.
  const std::string& get_fb_password() const;

  /// @brief Sets the firebird user password.
  void set_fb_password(const std::string& newValue);

  /// @brief Firebird hostname.
  const std::string& get_fb_host() const;

  /// @brief Sets the firebird hostname.
  void set_fb_host(const std::string& newValue);

  /// @brief Firebird port.
  const std::string& get_fb_port() const;

  /// @brief Sets the firebird port.
  void set_fb_port(const std::string& newValue);

  /// @brief The Firebird connection interface object. Connected in default
  /// Application class implementation.
  const std::shared_ptr<IDBConnection>& get_db_connection() const;

  /// @brief Sets the the Firebird connection interface object. Connected in
  /// default Application class implementation.
  void set_db_connection(const std::shared_ptr<IDBConnection>& newValue);

  static const std::string default_fb_name;

  /// @brief Remember to change this publicly visible credentials!!!
  static const std::string default_fb_user;

  /// @brief Remember to change this publicly visible credentials!!!
  static const std::string default_fb_password;

 private:
  /// @brief Command line arguments count passed by the OS through the main
  /// executable function.
  int& margc;

  /// @brief The command line arguments array passed by the OS through
  /// the main executable function.
  char**& margv;

  /// @brief The help printing flag. See the
  /// ApplicationContext::set_print_help_and_exit setter.
  bool mprint_help_and_exit{false};

  /// @brief The version printing flag. See the
  /// ApplicationContext::set_print_version_and_exit setter.
  bool mprint_version_and_exit{false};

  /// @brief Errors description.
  std::vector<std::string> merrors;

  /// @brief The thread safe application stop flag. See the
  /// ApplicationContext::set_stop setter.
  std::atomic_bool mstop{false};

  /// @brief Firebird database name, path or alias
  std::string mfb_dbname;

  /// @brief Firebird user name
  std::string mfb_user;

  /// @brief Firebird user password
  std::string mfb_password;

  /// @brief Firebird hostname
  std::string mfb_host;

  /// @brief Firebird port
  std::string mfb_port;

  /// @brief The Firebird connection interface object. Connected in default
  /// Application class implementation.
  std::shared_ptr<IDBConnection> mdb_connection;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
