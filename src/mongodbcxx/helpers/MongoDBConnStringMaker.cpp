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

  if (actx == nullptr) {
    return {};
  }

  // "mongodb://dbuser:dbpass@192.168.1.100:27017/databasename?options"

  std::string connUrl{"mongodb://"};

  const bool authenticated = !actx->get_db_username().empty();

  if (authenticated) {
    connUrl += percent_encode(actx->get_db_username());

    if (!actx->get_db_password().empty()) {
      connUrl += ":" + percent_encode(actx->get_db_password());
    }

    connUrl += "@";
  }

  connUrl += value_or(actx->get_db_host(), defaultHost) + ":" +
             value_or(actx->get_db_port(), defaultPort);
  connUrl += "/" + percent_encode(actx->get_db_name());

  std::string options;

  if (!actx->get_db_timeout_ms().empty()) {
    options += "&serverSelectionTimeoutMS=" + actx->get_db_timeout_ms() +
               "&connectTimeoutMS=" + actx->get_db_timeout_ms();
  }

  const std::string& tls =
      value_or(actx->get_db_tls(), authenticated ? tlsOn : tlsAuto);

  if (!tls.empty()) {
    options += "&tls=" + tls;
  }

  if (!options.empty()) {
    connUrl += "?" + options.substr(1);
  }

  return connUrl;
}

std::string MongoDBConnStringMaker::percent_encode(const std::string& value)
{
  static const std::string unreserved{
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~"};
  static const std::string hexDigits{"0123456789ABCDEF"};

  std::string encoded;

  for (const char symbol : value) {
    if (unreserved.find(symbol) != std::string::npos) {
      encoded += symbol;
      continue;
    }

    const auto code = static_cast<unsigned char>(symbol);

    encoded += '%';
    encoded += hexDigits[code >> 4U];
    encoded += hexDigits[code & 0x0FU];
  }

  return encoded;
}

const std::string& MongoDBConnStringMaker::value_or(const std::string& value,
                                                    const std::string& fallback)
{
  return value.empty() ? fallback : value;
}

}  // namespace mongodbcxxi::helpers
