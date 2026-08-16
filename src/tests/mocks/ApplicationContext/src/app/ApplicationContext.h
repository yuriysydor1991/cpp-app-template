#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H

#include <gmock/gmock.h>

#include <atomic>
#include <string>
#include <vector>

#include "project-global-decls.h"

namespace app
{

class ApplicationContext
{
 public:
  ApplicationContext(int& gargc, char**& gargv);

  int& get_argc() const { return margc; }
  char**& get_argv() const { return margv; }

  bool get_print_help_and_exit() const { return mprint_help_and_exit; }
  void set_print_help_and_exit(const bool newValue)
  {
    mprint_help_and_exit = newValue;
  }

  bool get_print_version_and_exit() const { return mprint_version_and_exit; }
  void set_print_version_and_exit(const bool newValue)
  {
    mprint_version_and_exit = newValue;
  }

  const std::vector<std::string>& get_errors() const { return merrors; }

  bool get_stop() const { return mstop.load(); }
  void set_stop(const bool newValue) { mstop.store(newValue); }

  const std::string& get_http_address() const { return mhttp_address; }
  void set_http_address(const std::string& newValue)
  {
    mhttp_address = newValue;
  }

  unsigned short get_http_port() const { return mhttp_port; }
  void set_http_port(const unsigned short newValue) { mhttp_port = newValue; }

  MOCK_METHOD(void, push_error, (const std::string& errorDescription));

  inline static const std::string& default_http_address =
      project_decls::PROJECT_HTTP_LISTEN_ADDRESS;
  inline static constexpr const unsigned short default_http_port =
      project_decls::PROJECT_HTTP_LISTEN_PORT;

 private:
  int& margc;
  char**& margv;
  bool mprint_help_and_exit{false};
  bool mprint_version_and_exit{false};
  std::vector<std::string> merrors;
  std::atomic_bool mstop{false};
  std::string mhttp_address;
  unsigned short mhttp_port;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
