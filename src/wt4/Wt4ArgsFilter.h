#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WT4ARGSFILTER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WT4ARGSFILTER_CLASS_H

#include <string>
#include <vector>

namespace wt4server
{

/**
 * @brief Picks the Wt server arguments out of the executable command line.
 *
 * The executable command line carries the application own parameters (see
 * the app::CMDParamNames class) next to the Wt ones, while the Wt server
 * configuration rejects every parameter it does not know.
 */
class Wt4ArgsFilter
{
 public:
  virtual ~Wt4ArgsFilter() = default;
  Wt4ArgsFilter() = default;

  /**
   * @brief Returns the command line arguments without the program name and
   * without the application own parameters together with their data.
   *
   * @param argc The command line arguments count.
   * @param argv The command line arguments.
   *
   * @return Returns the arguments to pass to the Wt server configuration.
   */
  virtual std::vector<std::string> filter(int argc, char** argv);

 protected:
  static bool is_app_flag(const std::string& arg);
  static bool is_app_param_with_data(const std::string& arg);
};

}  // namespace wt4server

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WT4ARGSFILTER_CLASS_H
