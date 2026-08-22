#include "src/app/applications/ApplicationHelpPrinter.h"

#include <cassert>
#include <iostream>
#include <memory>

#include "project-global-decls.h"
#include "src/app/CMDParamNames.h"
#include "src/claude/ClaudeController.h"
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
            << " <path> - write the log messages into the given file"
            << std::endl
            << "\t" << CMDParamNames::TOKENW << " or " << CMDParamNames::TOKEN
            << " <token> - the Anthropic API token to authorize the Claude "
               "call with. Taken from the "
            << claudei::ClaudeController::TOKEN_ENV_VAR
            << " environment variable when omitted" << std::endl
            << "\t" << CMDParamNames::QUESTIONW << " or "
            << CMDParamNames::QUESTION
            << " <question> - the question to ask the Claude model about"
            << std::endl
            << "\t" << CMDParamNames::MODELW << " or " << CMDParamNames::MODEL
            << " <model> - the model to ask. The "
            << claudei::ClaudeController::DEFAULT_MODEL
            << " one is asked when omitted" << std::endl;

  return 0;
}

}  // namespace app
