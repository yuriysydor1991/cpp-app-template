#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MONGODBCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MONGODBCONTROLLER_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/app/IDBConnection.h"
#include "src/mongodbcxx/helpers/QueryMaker.h"
#include "src/mongodbcxx/mongocxx-includes.h"

/**
 * @brief The MongoDB abstraction layer encapsulation namespace.
 */
namespace mongodbcxxi
{

/**
 * @brief The DBMS MongoDB interface controller class.
 */
class MongoDBController : public app::IDBConnection
{
 public:
  using JsonDoc = helpers::QueryMaker::JsonDoc;
  using DBJsonRes = bsoncxx::document::value;

  virtual ~MongoDBController() = default;
  MongoDBController();

  /**
   * @brief Tries to connect to the specified database server.
   * The credentials are taken from the ApplicationContext instance.
   *
   * @param nctx The ApplicationContext for connection credentials etc.
   *
   * @returns Returns a true boolean value on the success or false otherwise.
   */
  virtual bool connect(std::shared_ptr<app::ApplicationContext> nctx) override;

  /**
   * @brief Returns a true boolean value in case of a present
   * connection.
   *
   * @returns Returns a true boolean value in case of a present
   * connection or false otherwise.
   */
  virtual bool connected() override;

  /**
   * @brief The demonstration method which fetches current date as a string from
   * the available server connection if any.
   *
   * @returns Returns retrieved date from the database if any, or empty string
   * in case of any error.
   */
  virtual std::string get_current_date() override;

 protected:
  /**
   * @brief Executes given bsoncxx::document::value document query.
   * Moves it contents.
   *
   * @param queryDoc The document query to be executed. It's value is moved.
   *
   * @return Returns the query result if any or a std::shared_ptr with a nullptr
   * value.
   */
  virtual std::shared_ptr<DBJsonRes> execute_query(JsonDoc queryDoc);

  inline static constexpr const char* const localTime = "localTime";

  std::shared_ptr<app::ApplicationContext> actx;

  mongocxx::client dbclient;
  mongocxx::database dbconnection;

  std::shared_ptr<helpers::QueryMaker> qmaker;
};

}  // namespace mongodbcxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MONGODBCONTROLLER_CLASS_H
