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

  const std::string& get_fb_dbname() const { return mfb_dbname; }
  void set_fb_dbname(const std::string& newValue) { mfb_dbname = newValue; }

  const std::string& get_fb_user() const { return mfb_user; }
  void set_fb_user(const std::string& newValue) { mfb_user = newValue; }

  const std::string& get_fb_password() const { return mfb_password; }
  void set_fb_password(const std::string& newValue) { mfb_password = newValue; }

  const std::string& get_fb_host() const { return mfb_host; }
  void set_fb_host(const std::string& newValue) { mfb_host = newValue; }

  const std::string& get_fb_port() const { return mfb_port; }
  void set_fb_port(const std::string& newValue) { mfb_port = newValue; }

  const std::shared_ptr<IDBConnection>& get_db_connection() const
  {
    return mdb_connection;
  }
  void set_db_connection(const std::shared_ptr<IDBConnection>& newValue)
  {
    mdb_connection = newValue;
  }

  MOCK_METHOD(void, push_error, (const std::string& errorDescription));

  static const std::string default_fb_name;
  static const std::string default_fb_user;
  static const std::string default_fb_password;

 private:
  int& margc;
  char**& margv;
  bool mprint_help_and_exit{false};
  bool mprint_version_and_exit{false};
  std::vector<std::string> merrors;
  std::atomic_bool mstop{false};
  std::string mfb_dbname;
  std::string mfb_user;
  std::string mfb_password;
  std::string mfb_host;
  std::string mfb_port;
  std::shared_ptr<IDBConnection> mdb_connection;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATIONCONTEXT_CLASS_H
