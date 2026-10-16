#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_NOSQL_MONGODBCONNSTRINGMAKER_HELPER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_NOSQL_MONGODBCONNSTRINGMAKER_HELPER_CLASS_H

#include <memory>
#include <string>

#include "src/app/ApplicationContext.h"

namespace mongodbcxxi::helpers
{

/**
 * @brief The DBMS MongoDB URL connection string maker.
 */
class MongoDBConnStringMaker
{
 public:
  virtual ~MongoDBConnStringMaker() = default;
  MongoDBConnStringMaker() = default;

  /**
   * @brief Creates the MongoDB connection string URI based on
   * the data provided in the app::ApplicationContext instance.
   * An empty host or port is replaced by the localhost and the standard
   * 27017 port, the credentials part is added for a non-empty username only,
   * and the user name, the password and the database name are percent-encoded.
   *
   * @param actx the app::ApplicationContext instance with
   * appropriate data.
   *
   * @return Returns valid MongoDB server connection string or an empty one
   * for no context given.
   */
  static std::string make_conn_string(
      std::shared_ptr<app::ApplicationContext> actx);

 protected:
  /**
   * @brief Percent-encodes every character of the given value except the
   * RFC 3986 unreserved ones, so the @, :, /, %, ? and # characters of the
   * credentials can't break the connection string.
   *
   * @param value The value to encode.
   *
   * @return Returns the percent-encoded value.
   */
  static std::string percent_encode(const std::string& value);

  /// @brief Returns the value or the fallback one for an empty value.
  static const std::string& value_or(const std::string& value,
                                     const std::string& fallback);

  inline static const std::string defaultHost{"localhost"};
  inline static const std::string defaultPort{"27017"};
};

}  // namespace mongodbcxxi::helpers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_NOSQL_MONGODBCONNSTRINGMAKER_HELPER_CLASS_H
