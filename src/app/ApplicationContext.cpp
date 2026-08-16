#include "src/app/ApplicationContext.h"

#include <string>
#include <vector>

namespace app
{

const std::string ApplicationContext::default_fb_name = "employee";

const std::string ApplicationContext::default_fb_user = "SYSDBA";

const std::string ApplicationContext::default_fb_password = "masterkey";

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : margc{gargc},
      margv{gargv},
      mfb_dbname{default_fb_name},
      mfb_user{default_fb_user},
      mfb_password{default_fb_password}
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

const std::string& ApplicationContext::get_fb_dbname() const
{
  return mfb_dbname;
}

void ApplicationContext::set_fb_dbname(const std::string& newValue)
{
  mfb_dbname = newValue;
}

const std::string& ApplicationContext::get_fb_user() const { return mfb_user; }

void ApplicationContext::set_fb_user(const std::string& newValue)
{
  mfb_user = newValue;
}

const std::string& ApplicationContext::get_fb_password() const
{
  return mfb_password;
}

void ApplicationContext::set_fb_password(const std::string& newValue)
{
  mfb_password = newValue;
}

const std::string& ApplicationContext::get_fb_host() const { return mfb_host; }

void ApplicationContext::set_fb_host(const std::string& newValue)
{
  mfb_host = newValue;
}

const std::string& ApplicationContext::get_fb_port() const { return mfb_port; }

void ApplicationContext::set_fb_port(const std::string& newValue)
{
  mfb_port = newValue;
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
