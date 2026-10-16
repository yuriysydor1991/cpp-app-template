#include "src/wt4/Wt4ArgsFilter.h"

#include <set>
#include <string>
#include <vector>

#include "src/app/CMDParamNames.h"

namespace wt4server
{

std::vector<std::string> Wt4ArgsFilter::filter(const int argc, char** argv)
{
  std::vector<std::string> wtArgs;

  for (int iter = 1; argv != nullptr && iter < argc; ++iter) {
    const std::string arg{argv[iter]};

    if (is_app_param_with_data(arg)) {
      // skipping the parameter data as well
      ++iter;
    } else if (!is_app_flag(arg)) {
      wtArgs.push_back(arg);
    }
  }

  return wtArgs;
}

bool Wt4ArgsFilter::is_app_flag(const std::string& arg)
{
  using app::CMDParamNames;

  static const std::set<std::string> flags{
      CMDParamNames::HELPW, CMDParamNames::HELP, CMDParamNames::VERSIONW,
      CMDParamNames::VERSION};

  return flags.count(arg) > 0U;
}

bool Wt4ArgsFilter::is_app_param_with_data(const std::string& arg)
{
  using app::CMDParamNames;

  static const std::set<std::string> params{CMDParamNames::LOGPATHW,
                                            CMDParamNames::LOGPATH};

  return params.count(arg) > 0U;
}

}  // namespace wt4server
