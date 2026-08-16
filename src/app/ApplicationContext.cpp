#include "src/app/ApplicationContext.h"

#include <string>
#include <vector>

namespace app
{

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : margc{gargc}, margv{gargv}
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

const std::string& ApplicationContext::get_db_name() const { return mdb_name; }

void ApplicationContext::set_db_name(const std::string& newValue)
{
  mdb_name = newValue;
}

const std::string& ApplicationContext::get_db_username() const
{
  return mdb_username;
}

void ApplicationContext::set_db_username(const std::string& newValue)
{
  mdb_username = newValue;
}

const std::string& ApplicationContext::get_db_password() const
{
  return mdb_password;
}

void ApplicationContext::set_db_password(const std::string& newValue)
{
  mdb_password = newValue;
}

const std::string& ApplicationContext::get_db_host() const { return mdb_host; }

void ApplicationContext::set_db_host(const std::string& newValue)
{
  mdb_host = newValue;
}

const std::string& ApplicationContext::get_db_port() const { return mdb_port; }

void ApplicationContext::set_db_port(const std::string& newValue)
{
  mdb_port = newValue;
}

const std::shared_ptr<IDBConnection>& ApplicationContext::get_db_connection()
    const
{
  return mdb_connection;
}

void ApplicationContext::set_db_connection(
    const std::shared_ptr<IDBConnection>& newValue)
{
  mdb_connection = newValue;
}

}  // namespace app
