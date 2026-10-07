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
  inline static const std::string CFGW{"--cfg"};
  inline static const std::string CFG{"-c"};
  inline static const std::string WEIGHTSW{"--weights"};
  inline static const std::string WEIGHTS{"-w"};
  inline static const std::string DXXWJZ1W{"--dxxwjz1"};
  inline static const std::string DXXWJZ2W{"--dxxwjz2"};
  inline static const std::string NAMESW{"--names"};
  inline static const std::string NAMES{"-n"};
  inline static const std::string IMAGEW{"--image"};
  inline static const std::string IMAGE{"-i"};
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_COMMANDLINEPARAMETERNAMES_CLASS_H
