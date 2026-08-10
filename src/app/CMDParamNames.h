#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_COMMANDLINEPARAMETERNAMES_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_COMMANDLINEPARAMETERNAMES_CLASS_H

#include <memory>
#include <set>

#include "src/app/ApplicationContext.h"

namespace app
{

/**
 * @brief Class for encapsulating the command line parameters.
 */
class CMDParamNames
{
 public:
  virtual ~CMDParamNames() = default;
  CMDParamNames() = default;

  inline static const std::string HELPW{"--help"};
  inline static const std::string HELP{"-h"};
  inline static const std::string VERSIONW{"--version"};
  inline static const std::string VERSION{"-v"};
  inline static const std::string LOGPATHW{"--log-file"};
  inline static const std::string LOGPATH{"-l"};
  inline static const std::string TOKENW{"--token"};
  inline static const std::string TOKEN{"-t"};
  inline static const std::string QUESTIONW{"--question"};
  inline static const std::string QUESTION{"-q"};
  inline static const std::string MODELW{"--model"};
  inline static const std::string MODEL{"-m"};
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_COMMANDLINEPARAMETERNAMES_CLASS_H
