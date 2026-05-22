#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/sdbuscxx/server-objects/CurrentDateServerObject.h"
#include "src/sdbuscxx/server-objects/DBusServerObjectFactory.h"
#include "src/sdbuscxx/server-objects/IDBusServerObject.h"

using namespace testing;
using namespace sdbuscxxi;

class UTEST_DBusServerObjectFactory : public Test
{
 public:
  UTEST_DBusServerObjectFactory()
      : factory{std::make_shared<DBusServerObjectFactory>()}
  {
  }

  std::shared_ptr<DBusServerObjectFactory> factory;
};

TEST_F(UTEST_DBusServerObjectFactory, create_current_date_object_not_null)
{
  IDBusServerObjectPtr object = factory->create_current_date_object();

  EXPECT_NE(object, nullptr);
}

TEST_F(UTEST_DBusServerObjectFactory, create_current_date_object_is_current_date)
{
  IDBusServerObjectPtr object = factory->create_current_date_object();

  EXPECT_NE(std::dynamic_pointer_cast<CurrentDateServerObject>(object), nullptr);
}

TEST_F(UTEST_DBusServerObjectFactory, create_default_object_not_null)
{
  IDBusServerObjectPtr object = factory->create_default_object();

  EXPECT_NE(object, nullptr);
}

TEST_F(UTEST_DBusServerObjectFactory, create_default_object_is_current_date)
{
  IDBusServerObjectPtr object = factory->create_default_object();

  // For now the default object must be the current date server object.
  EXPECT_NE(std::dynamic_pointer_cast<CurrentDateServerObject>(object), nullptr);
}
