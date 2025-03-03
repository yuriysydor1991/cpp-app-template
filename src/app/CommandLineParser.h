#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_COMMANDLINEPARSER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_COMMANDLINEPARSER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace app {

/**
 * @brief The default application implementation should be placed into
 * into current class.
 */
class CommandLineParser
{
public:
  virtual ~CommandLineParser() = default;
  CommandLineParser() = default;

  /**
   * @brief Parses given argc and argv fields of a given application context.
   * 
   * @return Returns true on success and false in case of any error.
   */
  virtual bool parse_args(std::shared_ptr<ApplicationContext> ctx) ;

protected:
  virtual bool parse_arg(
    std::shared_ptr<ApplicationContext> ctx,
    const std::string& param, 
    const int& hasNext, 
    const std::string& nextParam,
    int& paramIndex
  );

  virtual bool check_4_data(
    std::shared_ptr<ApplicationContext> ctx,
    const std::string& param, 
    const int& hasNext
  );
};

} // namespace app

#endif // YOUR_CPP_APP_TEMPLATE_PROJECT_COMMANDLINEPARSER_CLASS_H
