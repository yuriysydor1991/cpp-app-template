#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITECONTROLLERMOCK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITECONTROLLERMOCK_CLASS_H

#include <gmock/gmock.h>

#include <memory>

#include "src/sqlite3cpp/SQLiteController.h"
#include "src/sqlite3cpp/sqlmaker/QueryMaker.h"

namespace sqlite3i
{

/// @brief The real SQLiteController with the query maker factory mocked.
class SQLiteControllerMock : public SQLiteController
{
 public:
  MOCK_METHOD(std::shared_ptr<sqlmaker::QueryMaker>, create_query_maker, (),
              (override));
};

}  // namespace sqlite3i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITECONTROLLERMOCK_CLASS_H
