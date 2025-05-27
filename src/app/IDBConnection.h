#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ABSTRACT_IDBCONNECTION_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ABSTRACT_IDBCONNECTION_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace app
{

struct ApplicationContext;

/**
 * @brief Class interface to interface the db connection methods.
 */
class IDBConnection
{
 public:
  virtual ~IDBConnection() = default;
  IDBConnection() = default;

  /**
   * @brief Tries to connect to the specified database server.
   * The credentials are taken from the ApplicationContext instance.
   *
   * @param nctx The ApplicationContext for connection credentials etc.
   *
   * @returns Returns a true boolean value on the success or false otherwise.
   */
  virtual bool connect(std::shared_ptr<app::ApplicationContext> nctx) = 0;

  /**
   * @brief Returns a true boolean value in case of a present
   * connection.
   *
   * @returns Returns a true boolean value in case of a present
   * connection or false otherwise.
   */
  virtual bool connected() = 0;

  /**
   * @brief The demonstration method which fetches current date as a string from
   * the available server connection if any.
   *
   * @returns Returns retrieved date from the database if any, or empty string
   * in case of any error.
   */
  virtual std::string get_current_date() = 0;
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ABSTRACT_IDBCONNECTION_CLASS_H
