#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_COMMANDLINEPARSER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_COMMANDLINEPARSER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace app {

/**
 * @brief The default application implementation should be placed
 * into current class.
 */
class CommandLineParser
{
public:
  virtual ~CommandLineParser() = default;
  CommandLineParser() = default;

  /**
   * @brief Parses given argc and argv fields of a given application context.
   * In case of any error tries to store it's description into the ctx context
   * and sets value of the print_help_and_exit field of the ctx into true.
   * 
   * @param ctx The application context that needs to be parsed.
   * 
   * @return Returns true on success and false in case of any error.
   */
  virtual bool parse_args(std::shared_ptr<ApplicationContext> ctx) ;

protected:

  /**
   * @brief Parse single argument with optional data provided next to it.
   * 
   * @param ctx The parsed application context.
   * @param param Command line argument (usually starts with - or --, for example, --help)
   * @param hasNext Flag that marks if there is any next value placed after
   * the current command line flag.
   * @param nextParam The value that stands after current command line flag, or empty
   * string if insufficient data.
   * @param paramIndex Int iterator that indicates current item in the argv array ( passed
   * mostly by the OS).
   * 
   * @return Returns true on the success and false in case of any error.
   */
  virtual bool parse_arg(
    std::shared_ptr<ApplicationContext> ctx,
    const std::string& param, 
    const int& hasNext, 
    const std::string& nextParam,
    int& paramIndex
  );

  /**
   * @brief Check if given parameter param must have some data value placed after it
   * in the command line parameters.
   * 
   * @param ctx The parsed application context.
   * @param param Command line argument (usually starts with - or --, for example, --help)
   * @param hasNext Flag that marks if there is any next value placed after
   * the current command line flag.
   * 
   * @return Returns true if given parameter param should have any value and nextParam
   * contains it or command line flag param does not require any data next to it.
   * And a false values otherwise.
   */
  virtual bool check_4_data(
    std::shared_ptr<ApplicationContext> ctx,
    const std::string& param, 
    const int& hasNext,
    const std::string& nextParam
  );
};

} // namespace app

#endif // YOUR_CPP_APP_TEMPLATE_PROJECT_COMMANDLINEPARSER_CLASS_H
