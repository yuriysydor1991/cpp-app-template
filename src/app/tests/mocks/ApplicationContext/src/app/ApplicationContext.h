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

  const std::string& get_db_dbname() const { return mdb_dbname; }
  void set_db_dbname(const std::string& newValue) { mdb_dbname = newValue; }

  const std::shared_ptr<IDBConnection>& get_dbconn() const { return mdbconn; }
  void set_dbconn(const std::shared_ptr<IDBConnection>& newValue)
  {
    mdbconn = newValue;
  }

  MOCK_METHOD(void, push_error, (const std::string& errorDescription));

  static const std::string default_db_name;

 private:
  int& margc;
  char**& margv;
  bool mprint_help_and_exit{false};
  bool mprint_version_and_exit{false};
  std::vector<std::string> merrors;
  std::atomic_bool mstop{false};
  std::string mdb_dbname;
  std::shared_ptr<IDBConnection> mdbconn;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
