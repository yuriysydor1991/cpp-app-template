#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H

#include <gmock/gmock.h>

#include <atomic>
#include <memory>
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

  const std::string& get_db_name() const { return mdb_name; }
  void set_db_name(const std::string& newValue) { mdb_name = newValue; }

  const std::string& get_db_username() const { return mdb_username; }
  void set_db_username(const std::string& newValue) { mdb_username = newValue; }

  const std::string& get_db_password() const { return mdb_password; }
  void set_db_password(const std::string& newValue) { mdb_password = newValue; }

  const std::string& get_db_host() const { return mdb_host; }
  void set_db_host(const std::string& newValue) { mdb_host = newValue; }

  const std::string& get_db_port() const { return mdb_port; }
  void set_db_port(const std::string& newValue) { mdb_port = newValue; }

  const std::shared_ptr<IDBConnection>& get_db_connection() const
  {
    return mdb_connection;
  }
  void set_db_connection(const std::shared_ptr<IDBConnection>& newValue)
  {
    mdb_connection = newValue;
  }

  MOCK_METHOD(void, push_error, (const std::string& errorDescription));

 private:
  int& margc;
  char**& margv;
  bool mprint_help_and_exit{false};
  bool mprint_version_and_exit{false};
  std::vector<std::string> merrors;
  std::atomic_bool mstop{false};
  std::string mdb_name;
  std::string mdb_username;
  std::string mdb_password;
  std::string mdb_host;
  std::string mdb_port;
  std::shared_ptr<IDBConnection> mdb_connection;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
