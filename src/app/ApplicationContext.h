#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H

#include <vector>
#include <string>

namespace app {

/**
 * @brief The class that holds necessary information for the application
 * to run properly. May hold parsed parameters, configuration values
 * and error messages with application status code.
 */
struct ApplicationContext
{
  int& argc ;
  char** &argv ;

  ApplicationContext(int& gargc, char** &gargv);

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
   * @brief Pushes a new error description into the errors field;
   * 
   * @param errorDescription The application error description.
   */
  void push_error(const std::string& errorDescription);
};

} // namespace app

#endif // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
