#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H

#include <gmock/gmock.h>

#include <string>
#include <vector>

namespace app
{

struct ApplicationContext
{
 public:
  int& argc;
  char**& argv;

  ApplicationContext(int& gargc, char**& gargv);

  bool print_help_and_exit{false};
  bool print_version_and_exit{false};
  std::vector<std::string> errors;
  std::string image_path;
  std::string cascade_path;

  MOCK_METHOD(void, push_error, (const std::string& errorDescription));
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H