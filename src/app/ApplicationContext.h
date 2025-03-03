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
