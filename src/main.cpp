#include "project-global-decls.h"
#include "src/log/log.h"

/**
 * @brief The application main routine, obviously.
 *
 * @param argc Count of given command line arguments.
 * @param argv The command line parameters array by itself.
 *
 * @return Returns a zero value in case of success and other value
 * in case of any error.
 */
int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
  LOG_INIT_DEFAULTS();

  LOGI("Your " << project_decls::PROJECT_NAME << " implementation goes here!");

  return 0;
}
