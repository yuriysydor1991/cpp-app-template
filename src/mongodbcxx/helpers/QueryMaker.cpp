#include "src/mongodbcxx/helpers/QueryMaker.h"

#include <memory>

#include "src/mongodbcxx/mongocxx-includes.h"

namespace mongodbcxxi::helpers
{

QueryMaker::QueryMaker(std::shared_ptr<app::ApplicationContext> ctx) : actx{ctx}
{
}

QueryMaker::JsonDoc QueryMaker::create_date_query()
{
  static const JsonDoc dateDoc = JsonDocBuilder{} << "hello" << 1
                                                  << stream::finalize;

  return dateDoc;
}

QueryMaker::JsonDoc QueryMaker::create_ping_query()
{
  static const JsonDoc pingDoc = JsonDocBuilder{} << "ping" << 1
                                                  << stream::finalize;

  return pingDoc;
}

}  // namespace mongodbcxxi::helpers
