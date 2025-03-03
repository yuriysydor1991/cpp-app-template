#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H

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
};

} // namespace app

#endif // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
