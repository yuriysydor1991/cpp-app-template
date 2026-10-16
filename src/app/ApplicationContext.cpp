#include "src/app/ApplicationContext.h"

#include <cstdlib>
#include <string>
#include <vector>

namespace app
{

namespace
{

/// @brief Returns the given environment variable value if set or the fallback.
std::string env_or(const char* name, const std::string& fallback)
{
  const char* value = std::getenv(name);

  return value != nullptr ? std::string{value} : fallback;
}

}  // namespace

const std::string ApplicationContext::default_pg_name = "postgres";

const std::string ApplicationContext::default_pg_user = "template_test_user";

const std::string ApplicationContext::default_pg_password =
    "template_test_password";

const std::string ApplicationContext::default_pg_host = "localhost";

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : margc{gargc},
      margv{gargv},
      mpg_dbname{env_or("PGDATABASE", default_pg_name)},
      mpg_user{env_or("PGUSER", default_pg_user)},
      mpg_password{env_or("PGPASSWORD", default_pg_password)},
      mpg_host{env_or("PGHOST", default_pg_host)},
      mpg_port{env_or("PGPORT", {})}
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

bool ApplicationContext::get_pause() const { return mpause.load(); }

void ApplicationContext::set_pause(const bool newValue)
{
  mpause.store(newValue);
}

bool ApplicationContext::get_reload() const { return mreload.load(); }

void ApplicationContext::set_reload(const bool newValue)
{
  mreload.store(newValue);
}

bool ApplicationContext::get_first_user_request() const
{
  return mfirst_user_request.load();
}

void ApplicationContext::set_first_user_request(const bool newValue)
{
  mfirst_user_request.store(newValue);
}

bool ApplicationContext::get_second_user_request() const
{
  return msecond_user_request.load();
}

void ApplicationContext::set_second_user_request(const bool newValue)
{
  msecond_user_request.store(newValue);
}

const std::string& ApplicationContext::get_pg_dbname() const
{
  return mpg_dbname;
}

void ApplicationContext::set_pg_dbname(const std::string& newValue)
{
  mpg_dbname = newValue;
}

const std::string& ApplicationContext::get_pg_user() const { return mpg_user; }

void ApplicationContext::set_pg_user(const std::string& newValue)
{
  mpg_user = newValue;
}

const std::string& ApplicationContext::get_pg_password() const
{
  return mpg_password;
}

void ApplicationContext::set_pg_password(const std::string& newValue)
{
  mpg_password = newValue;
}

const std::string& ApplicationContext::get_pg_host() const { return mpg_host; }

void ApplicationContext::set_pg_host(const std::string& newValue)
{
  mpg_host = newValue;
}

const std::string& ApplicationContext::get_pg_port() const { return mpg_port; }

void ApplicationContext::set_pg_port(const std::string& newValue)
{
  mpg_port = newValue;
}

const std::shared_ptr<IDBConnection>& ApplicationContext::get_pg_connection()
    const
{
  return mpg_connection;
}

void ApplicationContext::set_pg_connection(
    const std::shared_ptr<IDBConnection>& newValue)
{
  mpg_connection = newValue;
}

}  // namespace app
