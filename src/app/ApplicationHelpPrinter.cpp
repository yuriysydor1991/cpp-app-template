#include <memory>
#include <iostream>
#include <cassert>

#include "src/app/ApplicationHelpPrinter.h"
#include "project-global-decls.h"

namespace app {

int ApplicationHelpPrinter::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr)
  { return INVALID ; }

  // Register and implement here command line parameters from the CommandLineParser class.
  std::cout
    << "Usage:" << std::endl << std::endl
    << "\t" << project_decls::PROJECT_NAME << " [OPTIONS]" 
    << std::endl << std::endl
    << "Introduce a new command line flags by registering them in" << std::endl
    << "the ApplicationHelpPrinter and the CommandLineParser classes."
    << std::endl << std::endl
    << "Where OPTIONS may be next:" << std::endl
    << "\t--help or -h - print current help message"
    << std::endl
    << "\t--version or -v - print application version, build git commit and configure date"
    << std::endl;

  return 0 ;
}

} // namespace app
