#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/gdbus/query-handlers/DBusQueryHandlerFactory.h"
#include "src/gdbus/query-handlers/Hostname1QueryHandler.h"
#include "src/gdbus/query-handlers/IDBusQueryHandler.h"

using namespace testing;
using namespace gdbusi;

class UTEST_DBusQueryHandlerFactory : public Test
{
 public:
  UTEST_DBusQueryHandlerFactory()
      : factory{std::make_shared<DBusQueryHandlerFactory>()}
  {
  }

  std::shared_ptr<DBusQueryHandlerFactory> factory;
};

TEST_F(UTEST_DBusQueryHandlerFactory, create_hostname1_handler_not_null)
{
  IDBusQueryHandlerPtr handler = factory->create_hostname1_handler();

  EXPECT_NE(handler, nullptr);
}

TEST_F(UTEST_DBusQueryHandlerFactory, create_hostname1_handler_is_hostname1)
{
  IDBusQueryHandlerPtr handler = factory->create_hostname1_handler();

  EXPECT_NE(std::dynamic_pointer_cast<Hostname1QueryHandler>(handler), nullptr);
}

TEST_F(UTEST_DBusQueryHandlerFactory, create_default_handler_not_null)
{
  IDBusQueryHandlerPtr handler = factory->create_default_handler();

  EXPECT_NE(handler, nullptr);
}

TEST_F(UTEST_DBusQueryHandlerFactory, create_default_handler_is_hostname1)
{
  IDBusQueryHandlerPtr handler = factory->create_default_handler();

  // For now the default handler must be the hostname1 query handler.
  EXPECT_NE(std::dynamic_pointer_cast<Hostname1QueryHandler>(handler), nullptr);
}
