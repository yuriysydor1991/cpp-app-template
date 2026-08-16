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

  const std::string& get_mysql_dbname() const { return mmysql_dbname; }
  void set_mysql_dbname(const std::string& newValue)
  {
    mmysql_dbname = newValue;
  }

  const std::string& get_mysql_user() const { return mmysql_user; }
  void set_mysql_user(const std::string& newValue) { mmysql_user = newValue; }

  const std::string& get_mysql_password() const { return mmysql_password; }
  void set_mysql_password(const std::string& newValue)
  {
    mmysql_password = newValue;
  }

  const std::string& get_mysql_host() const { return mmysql_host; }
  void set_mysql_host(const std::string& newValue) { mmysql_host = newValue; }

  const std::string& get_mysql_port() const { return mmysql_port; }
  void set_mysql_port(const std::string& newValue) { mmysql_port = newValue; }

  const std::shared_ptr<IDBConnection>& get_mysqlconn() const
  {
    return mmysqlconn;
  }
  void set_mysqlconn(const std::shared_ptr<IDBConnection>& newValue)
  {
    mmysqlconn = newValue;
  }

  MOCK_METHOD(void, push_error, (const std::string& errorDescription));

  static const std::string default_mysql_name;
  static const std::string default_mysql_user;
  static const std::string default_mysql_password;
  static const std::string default_mysql_host;
  static const std::string default_mysql_port;

 private:
  int& margc;
  char**& margv;
  bool mprint_help_and_exit{false};
  bool mprint_version_and_exit{false};
  std::vector<std::string> merrors;
  std::atomic_bool mstop{false};
  std::string mmysql_dbname;
  std::string mmysql_user;
  std::string mmysql_password;
  std::string mmysql_host;
  std::string mmysql_port;
  std::shared_ptr<IDBConnection> mmysqlconn;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
