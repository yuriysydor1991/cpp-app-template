#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "src/Firebird/Firebird.h"
#include "src/Firebird/driver/FbClient.h"
#include "src/Firebird/tests/mocks/IFbClientMock.h"
#include "src/app/ApplicationContext.h"

using namespace firebirdi;
using namespace app;
using namespace testing;

// Link-time seam: the orchestration is exercised against the injected mock, so
// the real fbclient backed driver factory is never needed here.
namespace firebirdi::driver
{
std::shared_ptr<IFbClient> create_fb_client() { return nullptr; }
}  // namespace firebirdi::driver

namespace
{

/// @brief Test double exposing the injected IFbClient to the Firebird class.
class TestFirebird : public Firebird
{
 public:
  explicit TestFirebird(std::shared_ptr<IFbClient> nclient)
      : injected{nclient}
  {
  }

 protected:
  std::shared_ptr<IFbClient> create_client() override { return injected; }

 private:
  std::shared_ptr<IFbClient> injected;
};

}  // namespace

class UTEST_Firebird : public Test
{
 public:
  UTEST_Firebird()
      : client{std::make_shared<IFbClientMock>()},
        fb{std::make_shared<TestFirebird>(client)},
        ctx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<IFbClientMock> client;
  std::shared_ptr<TestFirebird> fb;
  std::shared_ptr<ApplicationContext> ctx;
};

TEST_F(UTEST_Firebird, connect_no_context_fails)
{
  EXPECT_CALL(*client, attach(_, _, _)).Times(0);

  EXPECT_FALSE(fb->connect(nullptr));
}

TEST_F(UTEST_Firebird, connect_passes_credentials_and_succeeds)
{
  ctx->fb_user = "SYSDBA";
  ctx->fb_password = "masterkey";

  EXPECT_CALL(*client, attach(_, "SYSDBA", "masterkey"))
      .Times(1)
      .WillOnce(Return(true));

  EXPECT_TRUE(fb->connect(ctx));
}

TEST_F(UTEST_Firebird, connect_failure_is_propagated)
{
  EXPECT_CALL(*client, attach(_, _, _)).Times(1).WillOnce(Return(false));

  EXPECT_FALSE(fb->connect(ctx));
}

TEST_F(UTEST_Firebird, connected_reflects_the_client_state)
{
  EXPECT_CALL(*client, attach(_, _, _)).WillOnce(Return(true));
  EXPECT_CALL(*client, attached()).WillRepeatedly(Return(true));

  EXPECT_TRUE(fb->connect(ctx));
  EXPECT_TRUE(fb->connected());
}

TEST_F(UTEST_Firebird, get_current_date_returns_fetched_value)
{
  static const std::string fetched_date{"2026-05-20"};

  EXPECT_CALL(*client, attach(_, _, _)).WillOnce(Return(true));
  EXPECT_CALL(*client, attached()).WillRepeatedly(Return(true));
  EXPECT_CALL(*client, query_scalar(_)).Times(1).WillOnce(Return(fetched_date));

  EXPECT_TRUE(fb->connect(ctx));
  EXPECT_EQ(fb->get_current_date(), fetched_date);
}

TEST_F(UTEST_Firebird, get_current_date_without_connection_is_empty)
{
  EXPECT_CALL(*client, query_scalar(_)).Times(0);

  EXPECT_TRUE(fb->get_current_date().empty());
}
