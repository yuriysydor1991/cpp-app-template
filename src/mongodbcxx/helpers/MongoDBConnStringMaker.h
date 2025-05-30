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
   * If no data provided - returns the default connection string
   * to a localhost and standard port of 27017.
   *
   * @param actx the app::ApplicationContext instance with
   * appropriate data.
   *
   * @return Returns valid MongoDB server connection string.
   */
  static std::string make_conn_string(
      std::shared_ptr<app::ApplicationContext> actx);

 protected:
  /**
   * @brief Checks whenever given app::ApplicationContext class instance
   * contains enough data to assemble the new MongoDB connection string.
   *
   * @return Returns a true boolean value if context contains enough of data
   * to assemble a new MongoDB connection string.
   */
  static bool filledConns(std::shared_ptr<app::ApplicationContext> actx);
};

}  // namespace mongodbcxxi::helpers

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_NOSQL_MONGODBCONNSTRINGMAKER_HELPER_CLASS_H
