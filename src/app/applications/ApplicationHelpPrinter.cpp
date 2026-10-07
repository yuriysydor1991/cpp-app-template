#include "src/app/applications/ApplicationHelpPrinter.h"

#include <cassert>
#include <iostream>
#include <memory>

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
            << "\t" << CMDParamNames::CFGW << " or " << CMDParamNames::CFG
            << " <path> - load the network of the given cfg file instead of "
               "the "
            << project_decls::PROJECT_DARKNETXX_CFG_PATH << " one" << std::endl
            << "\t" << CMDParamNames::WEIGHTSW << " or "
            << CMDParamNames::WEIGHTS
            << " <path> - load the given original Darknet weights file "
               "(*.weights) instead of the "
            << project_decls::PROJECT_DARKNETXX_WEIGHTS_PATH << " one"
            << std::endl
            << "\t" << CMDParamNames::DXXWJZ1W
            << " <path> - load the given darknetxx dxxwjz1 weights file "
               "(*.dxxwjz1) instead of the original one"
            << std::endl
            << "\t" << CMDParamNames::NAMESW << " or " << CMDParamNames::NAMES
            << " <path> - label the objects with the class names of the given "
               "file instead of the "
            << project_decls::PROJECT_DARKNETXX_NAMES_PATH << " one"
            << std::endl
            << "\t" << CMDParamNames::IMAGEW << " or " << CMDParamNames::IMAGE
            << " <path> - detect the objects in the given image instead of the "
            << project_decls::PROJECT_DARKNETXX_IMAGE_PATH << " one"
            << std::endl;

  return 0;
}

}  // namespace app
