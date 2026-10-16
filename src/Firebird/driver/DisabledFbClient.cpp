#include "src/Firebird/driver/DisabledFbClient.h"

#include <memory>
#include <string>

#include "src/Firebird/driver/FbClient.h"
#include "src/log/log.h"

namespace firebirdi::driver
{

std::shared_ptr<IFbClient> create_fb_client()
{
  return std::make_shared<DisabledFbClient>();
}

bool DisabledFbClient::attach(const std::string& database,
                              [[maybe_unused]] const std::string& user,
                              [[maybe_unused]] const std::string& password)
{
  LOGE(
      "The Firebird client support is disabled by the ENABLE_FIREBIRD=OFF "
      "configure, so the "
      << database << " database can not be attached");

  return false;
}

void DisabledFbClient::detach() {}

bool DisabledFbClient::attached() const { return false; }

std::string DisabledFbClient::query_scalar(
    [[maybe_unused]] const std::string& query)
{
  return {};
}

}  // namespace firebirdi::driver
