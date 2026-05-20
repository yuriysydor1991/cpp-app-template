#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_IFBCLIENT_MOCK_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_IFBCLIENT_MOCK_H

#include <gmock/gmock.h>

#include <string>

#include "src/Firebird/IFbClient.h"

namespace firebirdi
{

/**
 * @brief GMock implementation of the IFbClient driver interface.
 */
class IFbClientMock : public IFbClient
{
 public:
  MOCK_METHOD(bool, attach,
              (const std::string& database, const std::string& user,
               const std::string& password),
              (override));
  MOCK_METHOD(void, detach, (), (override));
  MOCK_METHOD(bool, attached, (), (const, override));
  MOCK_METHOD(std::string, query_scalar, (const std::string& query),
              (override));
};

}  // namespace firebirdi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_IFBCLIENT_MOCK_H
