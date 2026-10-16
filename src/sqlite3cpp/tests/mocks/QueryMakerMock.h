#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITE_QUERYMAKERMOCK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITE_QUERYMAKERMOCK_CLASS_H

#include <gmock/gmock.h>

#include <string>

#include "src/sqlite3cpp/sqlmaker/QueryMaker.h"

namespace sqlite3i::sqlmaker
{

/// @brief The QueryMaker mock to feed the controller with arbitrary queries.
class QueryMakerMock : public QueryMaker
{
 public:
  MOCK_METHOD(const std::string&, make_date_query, (), (override));
};

}  // namespace sqlite3i::sqlmaker

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SQLITE_QUERYMAKERMOCK_CLASS_H
