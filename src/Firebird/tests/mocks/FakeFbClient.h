#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FAKEFBCLIENT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FAKEFBCLIENT_CLASS_H

#include <string>

#include "src/Firebird/IFbClient.h"

namespace firebirdi
{

/**
 * @brief Records what the Firebird orchestration hands to the native driver
 * and returns canned responses, so the whole component pipeline (connection
 * string maker + query maker + orchestration) can be verified end to end
 * without a running Firebird server.
 */
class FakeFbClient : public IFbClient
{
 public:
  bool attach(const std::string& database, const std::string& user,
              const std::string& password) override
  {
    last_database = database;
    last_user = user;
    last_password = password;
    is_attached = attach_result;
    return attach_result;
  }

  void detach() override { is_attached = false; }
  bool attached() const override { return is_attached; }

  std::string query_scalar(const std::string& query) override
  {
    last_query = query;
    return scalar_result;
  }

  bool attach_result{true};
  std::string scalar_result;
  bool is_attached{false};

  std::string last_database;
  std::string last_user;
  std::string last_password;
  std::string last_query;
};

}  // namespace firebirdi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FAKEFBCLIENT_CLASS_H
