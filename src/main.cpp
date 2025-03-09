#include "src/app/ApplicationFactory.h"

/**
 * @brief The application main routine, obviously.
 *
 * @param argc Count of given command line arguments.
 * @param argv The command line parameters array by itself.
 *
 * @return Returns a zero value in case of success and other value
 * in case of any error.
 */
int main(int argc, char** argv)
{
  return app::ApplicationFactory::execute(argc, argv);
}
