#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/Firebird/driver/DisabledFbClient.h"
#include "src/Firebird/driver/FbClient.h"

using namespace firebirdi;
using namespace firebirdi::driver;
using namespace testing;

class UTEST_DisabledFbClient : public Test
{
 public:
  UTEST_DisabledFbClient() : client{create_fb_client()} {}

  std::shared_ptr<IFbClient> client;
};

TEST_F(UTEST_DisabledFbClient, factory_creates_the_disabled_client)
{
  EXPECT_NE(std::dynamic_pointer_cast<DisabledFbClient>(client), nullptr);
}

TEST_F(UTEST_DisabledFbClient, attach_fails)
{
  EXPECT_FALSE(client->attach("employee", "SYSDBA", "masterkey"));
  EXPECT_FALSE(client->attached());
}

TEST_F(UTEST_DisabledFbClient, query_yields_nothing)
{
  client->detach();

  EXPECT_TRUE(client->query_scalar("SELECT 1 FROM RDB$DATABASE").empty());
}
