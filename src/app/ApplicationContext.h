#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H

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
 */
struct ApplicationContext
{
  /// @brief Command line arguments count passed by the OS through the main
  /// executable function.
  int& argc;

  /// @brief The command line arguments array passed by the OS through
  /// the main executable function.
  char**& argv;

  /**
   * @brief An ApplicationContext constructor.
   *
   * @param gargc Command line arguments count passed by the OS through the main
   * executable function that will be referenced in the argc member field.
   * @param gargv  The command line arguments array passed by the OS through
   * the main executable function that will be referenced in the argv member
   * field.
   */
  ApplicationContext(int& gargc, char**& gargv);

  /**
   * @brief Set up this flag to true so the ApplicationFactory will create
   * a ApplicationHelpPrinter instance during the application execution.
   * All other classes are ignoring this flag.
   */
  bool print_help_and_exit{false};

  /**
   * @brief Set up this flag value to a true in order to ApplicationFactory
   * to create ApplicationVersionPrinter and execute it.
   */
  bool print_version_and_exit{false};

  /**
   * @brief Errors description.
   */
  std::vector<std::string> errors;

  /**
   * @brief The Anthropic API token to authorize the Claude calls with. When
   * empty the ClaudeController takes the token from the environment variable
   * named in it's TOKEN_ENV_VAR field.
   */
  std::string claude_token;

  /**
   * @brief The question to ask the Claude model about. When empty the
   * Application::run only prints the hint on how to provide one.
   */
  std::string claude_question;

  /**
   * @brief An optional model override. When empty the ClaudeController asks
   * it's DEFAULT_MODEL one.
   */
  std::string claude_model;

  /**
   * @brief Pushes a new error description into the errors field;
   *
   * @param errorDescription The application error description.
   */
  void push_error(const std::string& errorDescription);
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
