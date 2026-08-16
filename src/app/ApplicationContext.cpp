#include "src/app/ApplicationContext.h"

#include <memory>
#include <string>
#include <vector>

#include "project-global-decls.h"

namespace app
{

const std::string ApplicationContext::default_db_name =
    project_decls::PROJECT_NAME + project_decls::PROJECT_BUILD_VERSION +
    std::string{".db"};

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : margc{gargc}, margv{gargv}, mdb_dbname{default_db_name}
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

const std::string& ApplicationContext::get_db_dbname() const
{
  return mdb_dbname;
}

void ApplicationContext::set_db_dbname(const std::string& newValue)
{
  mdb_dbname = newValue;
}

const std::shared_ptr<IDBConnection>& ApplicationContext::get_dbconn() const
{
  return mdbconn;
}

void ApplicationContext::set_dbconn(
    const std::shared_ptr<IDBConnection>& newValue)
{
  mdbconn = newValue;
}

}  // namespace app
