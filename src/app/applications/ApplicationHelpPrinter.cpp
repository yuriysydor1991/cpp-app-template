#include "src/app/applications/ApplicationHelpPrinter.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "project-global-decls.h"
#include "src/app/CMDParamNames.h"
#include "src/gettext/tr.h"
#include "src/log/log.h"

namespace app
{

using gettexti::tr;

int ApplicationHelpPrinter::run(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return INVALID;
  }

  // Register and implement here command line parameters from the
  // CommandLineParser class. The gettexti::tr calls translate the messages.
  std::cout << tr("Usage:") << std::endl
            << std::endl
            << "\t" << project_decls::PROJECT_NAME << " " << tr("[OPTIONS]")
            << std::endl
            << std::endl
            << tr("Introduce a new command line flags by registering them in\n"
                  "the ApplicationHelpPrinter and the CommandLineParser "
                  "classes.")
            << std::endl
            << std::endl
            // TRANSLATORS: the OPTIONS of the [OPTIONS] in the usage line.
            << tr("Where OPTIONS may be next:")
            << std::endl
            // TRANSLATORS: joins the long and the short parameter names.
            << "\t" << CMDParamNames::HELPW << " " << tr("or") << " "
            << CMDParamNames::HELP << " - " << tr("print current help message")
            << std::endl
            << "\t" << CMDParamNames::VERSIONW << " " << tr("or") << " "
            << CMDParamNames::VERSION << " - "
            << tr("print application version, build git commit and configure "
                  "date")
            << std::endl;

  return 0;
}

}  // namespace app
