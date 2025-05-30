#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_NOSQL_MONGODB_QUERYMAKER_HELPER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_NOSQL_MONGODB_QUERYMAKER_HELPER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/mongodbcxx/mongocxx-includes.h"

namespace mongodbcxxi::helpers
{

using namespace bsoncxx::builder;

/**
 * @brief The class to encapsulate the DBMS MongoDB query creation.
 */
class QueryMaker
{
 public:
  using JsonDocBuilder = stream::document;
  using JsonDoc = bsoncxx::document::value;

  virtual ~QueryMaker() = default;
  explicit QueryMaker(std::shared_ptr<app::ApplicationContext> ctx);

  /**
   * @brief Creates the simple current date query JSON document.
   *
   * @returns Filled bsoncxx date query instance.
   */
  static JsonDoc create_date_query();

  /**
   * @brief Create the ping query to check if database connector
   * objects are connected to the MongoDB.
   *
   * @return Returns filled ping bsoncxx document query.
   */
  static JsonDoc create_ping_query();

 private:
  std::shared_ptr<app::ApplicationContext> actx;
};

}  // namespace mongodbcxxi::helpers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_NOSQL_MONGODB_QUERYMAKER_HELPER_CLASS_H
