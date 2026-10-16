#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DISABLEDFBCLIENT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DISABLEDFBCLIENT_CLASS_H

#include <string>

#include "src/Firebird/IFbClient.h"

namespace firebirdi::driver
{

/**
 * @brief The IFbClient stand-in of a build configured with the
 * ENABLE_FIREBIRD option OFF, which links no native Firebird client library.
 *
 * Every attachment fails with an error message that names the option.
 */
class DisabledFbClient : public IFbClient
{
 public:
  ~DisabledFbClient() override = default;
  DisabledFbClient() = default;

  bool attach(const std::string& database, const std::string& user,
              const std::string& password) override;
  void detach() override;
  bool attached() const override;
  std::string query_scalar(const std::string& query) override;
};

}  // namespace firebirdi::driver

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DISABLEDFBCLIENT_CLASS_H
