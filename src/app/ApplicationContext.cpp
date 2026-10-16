#include "src/app/ApplicationContext.h"

#include <cstdlib>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "project-global-decls.h"

namespace
{

/// @brief Returns the environment variable value or the fallback if the
/// variable is unset or empty.
std::string env_or(const char* name, const std::string& fallback)
{
  const char* value = std::getenv(name);

  return value != nullptr && *value != '\0' ? std::string{value} : fallback;
}

/// @brief Returns the SQLITE_DB_PATH value if set, otherwise the database file
/// inside the user data directory of the XDG Base Directory specification.
std::string default_db_path(const std::string& fileName)
{
  const std::string home = env_or("HOME", {});
  const std::filesystem::path dataDir = env_or(
      "XDG_DATA_HOME", home.empty() ? std::string{} : home + "/.local/share");

  return env_or("SQLITE_DB_PATH",
                (dataDir / project_decls::PROJECT_NAME / fileName).string());
}

}  // namespace

namespace app
{

const std::string ApplicationContext::default_db_name =
    project_decls::PROJECT_NAME + project_decls::PROJECT_BUILD_VERSION +
    std::string{".db"};

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : margc{gargc}, margv{gargv}, mdb_dbname{default_db_path(default_db_name)}
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
