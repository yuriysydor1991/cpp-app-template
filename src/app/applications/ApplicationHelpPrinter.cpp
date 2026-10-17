#include "src/app/applications/ApplicationHelpPrinter.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <string>

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

  // The command line errors of the CommandLineParser come first, since a bad
  // usage is the reason of the help message then.
  for (const std::string& error : ctx->get_errors()) {
    std::cerr << error << std::endl;
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
            << std::endl
            << "\t" << CMDParamNames::LOGPATHW << " " << tr("or") << " "
            << CMDParamNames::LOGPATH << " " << tr("<path>") << " - "
            << tr("append the log messages to the given file instead of the "
                  "default one")
            << std::endl;

  // A help message printed because of a bad usage is a failure.
  return ctx->get_errors().empty() ? 0 : INVALID;
}

}  // namespace app
