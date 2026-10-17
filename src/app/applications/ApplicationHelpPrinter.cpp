#include "src/app/applications/ApplicationHelpPrinter.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include "project-global-decls.h"
#include "src/app/CMDParamNames.h"
#include "src/log/log.h"

namespace app
{

int ApplicationHelpPrinter::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return INVALID;
  }

  // The command line errors of the CommandLineParser come first, since a bad
  // usage is the reason of the help message then.
  for (const std::string& error : ctx->get_errors()) {
    std::cerr << error << std::endl;
  }

  // Register and implement here command line parameters from the
  // CommandLineParser class.
  std::cout << "Usage:" << std::endl
            << std::endl
            << "\t" << project_decls::PROJECT_NAME << " [OPTIONS]" << std::endl
            << std::endl
            << "Introduce a new command line flags by registering them in"
            << std::endl
            << "the ApplicationHelpPrinter and the CommandLineParser classes."
            << std::endl
            << std::endl
            << "Where OPTIONS may be next:" << std::endl
            << "\t" << CMDParamNames::HELPW << " or " << CMDParamNames::HELP
            << " - print current help message" << std::endl
            << "\t" << CMDParamNames::VERSIONW << " or "
            << CMDParamNames::VERSION
            << " - print application version, build git "
               "commit and configure date"
            << std::endl
            << "\t" << CMDParamNames::LOGPATHW << " or "
            << CMDParamNames::LOGPATH
            << " <path> - append the log messages to the given file instead of "
               "the default one"
            << std::endl
            << "\t" << CMDParamNames::IMAGEW << " or " << CMDParamNames::IMAGE
            << " <path> - read the given FITS image and report about it"
            << std::endl;

  // A help message printed because of a bad usage is a failure.
  return ctx->get_errors().empty() ? 0 : INVALID;
}

}  // namespace app
