#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H

#include <atomic>
#include <string>
#include <vector>

namespace app
{

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

  /// @brief The Anthropic API token to authorize the Claude calls with. When
  /// empty the ClaudeController takes the token from the environment variable
  /// named in it's TOKEN_ENV_VAR field.
  const std::string& get_claude_token() const;

  /// @brief Sets the the Anthropic API token to authorize the Claude calls
  /// with. When empty the ClaudeController takes the token from the environment
  /// variable named in it's TOKEN_ENV_VAR field.
  void set_claude_token(const std::string& newValue);

  /// @brief The question to ask the Claude model about. When empty the
  /// Application::run only prints the hint on how to provide one.
  const std::string& get_claude_question() const;

  /// @brief Sets the the question to ask the Claude model about. When empty the
  /// Application::run only prints the hint on how to provide one.
  void set_claude_question(const std::string& newValue);

  /// @brief An optional model override. When empty the ClaudeController asks
  /// it's DEFAULT_MODEL one.
  const std::string& get_claude_model() const;

  /// @brief Sets the an optional model override. When empty the
  /// ClaudeController asks it's DEFAULT_MODEL one.
  void set_claude_model(const std::string& newValue);

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

  /**
   * @brief The Anthropic API token to authorize the Claude calls with. When
   * empty the ClaudeController takes the token from the environment variable
   * named in it's TOKEN_ENV_VAR field.
   */
  std::string mclaude_token;

  /**
   * @brief The question to ask the Claude model about. When empty the
   * Application::run only prints the hint on how to provide one.
   */
  std::string mclaude_question;

  /**
   * @brief An optional model override. When empty the ClaudeController asks
   * it's DEFAULT_MODEL one.
   */
  std::string mclaude_model;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
