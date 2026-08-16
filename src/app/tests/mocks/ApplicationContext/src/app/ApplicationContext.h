#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H

#include <gmock/gmock.h>

#include <atomic>
#include <string>
#include <vector>

#include "src/app/IDBConnection.h"

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

  const std::string& get_pg_dbname() const { return mpg_dbname; }
  void set_pg_dbname(const std::string& newValue) { mpg_dbname = newValue; }

  const std::string& get_pg_user() const { return mpg_user; }
  void set_pg_user(const std::string& newValue) { mpg_user = newValue; }

  const std::string& get_pg_password() const { return mpg_password; }
  void set_pg_password(const std::string& newValue) { mpg_password = newValue; }

  const std::string& get_pg_host() const { return mpg_host; }
  void set_pg_host(const std::string& newValue) { mpg_host = newValue; }

  const std::string& get_pg_port() const { return mpg_port; }
  void set_pg_port(const std::string& newValue) { mpg_port = newValue; }

  const std::shared_ptr<IDBConnection>& get_pg_connection() const
  {
    return mpg_connection;
  }
  void set_pg_connection(const std::shared_ptr<IDBConnection>& newValue)
  {
    mpg_connection = newValue;
  }

  MOCK_METHOD(void, push_error, (const std::string& errorDescription));

  static const std::string default_pg_name;
  static const std::string default_pg_user;
  static const std::string default_pg_password;

 private:
  int& margc;
  char**& margv;
  bool mprint_help_and_exit{false};
  bool mprint_version_and_exit{false};
  std::vector<std::string> merrors;
  std::atomic_bool mstop{false};
  std::string mpg_dbname;
  std::string mpg_user;
  std::string mpg_password;
  std::string mpg_host;
  std::string mpg_port;
  std::shared_ptr<IDBConnection> mpg_connection;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
