#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H

#include <gmock/gmock.h>

#include <string>
#include <vector>

#include "src/app/IDBConnection.h"

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

  MOCK_METHOD(void, push_error, (const std::string& errorDescription));

  std::string db_dbname;

  static const std::string default_db_name;

  std::shared_ptr<IDBConnection> dbconn;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H