#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H

#include <gmock/gmock.h>

#include <string>
#include <vector>

#include "project-global-decls.h"

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

  /// @brief For security listen for a loopback only by default.
  inline static const std::string& default_http_address =
      project_decls::PROJECT_HTTP_LISTEN_ADDRESS;
  inline static constexpr const unsigned short default_http_port =
      project_decls::PROJECT_HTTP_LISTEN_PORT;

  std::string http_address;
  unsigned short http_port;

  MOCK_METHOD(bool, stop, ());
  MOCK_METHOD(void, stop, (bool nstop));
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H