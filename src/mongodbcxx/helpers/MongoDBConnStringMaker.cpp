#include "src/mongodbcxx/helpers/MongoDBConnStringMaker.h"

#include <cassert>
#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace mongodbcxxi::helpers
{

std::string MongoDBConnStringMaker::make_conn_string(
    std::shared_ptr<app::ApplicationContext> actx)
{
  assert(actx != nullptr);

  // "mongodb://dbuser:dbpass@192.168.1.100:27017/databasename?options"

  static const std::string mongodbStarter = "mongodb://";
  static const std::string mongodbDefault = "localhost:27017";

  std::string connUrl{mongodbStarter};

  if (!filledConns(actx)) {
    return mongodbStarter + mongodbDefault;
  }

  connUrl += actx->db_username + ":" + actx->db_password;
  connUrl += "@" + actx->db_host + ":" + actx->db_port;
  connUrl += "/" + actx->db_name;
  connUrl += "?";
  connUrl += "tls=true";

  return connUrl;
}

bool MongoDBConnStringMaker::filledConns(
    std::shared_ptr<app::ApplicationContext> actx)
{
  return actx != nullptr && !actx->db_username.empty() &&
         !actx->db_username.empty() && !actx->db_password.empty() &&
         !actx->db_host.empty() && !actx->db_port.empty() &&
         !actx->db_name.empty();
}

}  // namespace mongodbcxxi::helpers
