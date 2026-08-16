#include "src/app/ApplicationContext.h"

#include <string>
#include <vector>

namespace app
{

const std::string ApplicationContext::default_mysql_name = "";

const std::string ApplicationContext::default_mysql_user = "template_test_user";

const std::string ApplicationContext::default_mysql_password =
    "template_test_password";

const std::string ApplicationContext::default_mysql_host = "tcp://127.0.0.1";

const std::string ApplicationContext::default_mysql_port = "3306";

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : margc{gargc},
      margv{gargv},
      mmysql_dbname{default_mysql_name},
      mmysql_user{default_mysql_user},
      mmysql_password{default_mysql_password},
      mmysql_host{default_mysql_host},
      mmysql_port{default_mysql_port}
{
}

int& ApplicationContext::get_argc() const { return margc; }

char**& ApplicationContext::get_argv() const { return margv; }

bool ApplicationContext::get_print_help_and_exit() const
{
  return mprint_help_and_exit;
}

void ApplicationContext::set_print_help_and_exit(const bool newValue)
{
  mprint_help_and_exit = newValue;
}

bool ApplicationContext::get_print_version_and_exit() const
{
  return mprint_version_and_exit;
}

void ApplicationContext::set_print_version_and_exit(const bool newValue)
{
  mprint_version_and_exit = newValue;
}

const std::vector<std::string>& ApplicationContext::get_errors() const
{
  return merrors;
}

void ApplicationContext::push_error(const std::string& errorDescription)
{
  merrors.emplace_back(errorDescription);
}

bool ApplicationContext::get_stop() const { return mstop.load(); }

void ApplicationContext::set_stop(const bool newValue)
{
  mstop.store(newValue);
}

const std::string& ApplicationContext::get_mysql_dbname() const
{
  return mmysql_dbname;
}

void ApplicationContext::set_mysql_dbname(const std::string& newValue)
{
  mmysql_dbname = newValue;
}

const std::string& ApplicationContext::get_mysql_user() const
{
  return mmysql_user;
}

void ApplicationContext::set_mysql_user(const std::string& newValue)
{
  mmysql_user = newValue;
}

const std::string& ApplicationContext::get_mysql_password() const
{
  return mmysql_password;
}

void ApplicationContext::set_mysql_password(const std::string& newValue)
{
  mmysql_password = newValue;
}

const std::string& ApplicationContext::get_mysql_host() const
{
  return mmysql_host;
}

void ApplicationContext::set_mysql_host(const std::string& newValue)
{
  mmysql_host = newValue;
}

const std::string& ApplicationContext::get_mysql_port() const
{
  return mmysql_port;
}

void ApplicationContext::set_mysql_port(const std::string& newValue)
{
  mmysql_port = newValue;
}

const std::shared_ptr<IDBConnection>& ApplicationContext::get_mysqlconn() const
{
  return mmysqlconn;
}

void ApplicationContext::set_mysqlconn(
    const std::shared_ptr<IDBConnection>& newValue)
{
  mmysqlconn = newValue;
}

}  // namespace app
