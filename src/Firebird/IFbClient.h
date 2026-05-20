#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ABSTRACT_IFBCLIENT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ABSTRACT_IFBCLIENT_CLASS_H

#include <string>

/**
 * @brief The namespace to encapsulate all the guts of the Firebird database
 * handling.
 */
namespace firebirdi
{

/**
 * @brief Thin abstraction over the Firebird client library (fbclient).
 *
 * All the raw `fbclient` (ibase.h) calls live behind this interface in the
 * firebirdi::driver::FbClient implementation. Keeping the native library out
 * of the rest of the component allows the Firebird orchestration and its tests
 * to be built and run without the Firebird development headers or a running
 * Firebird server.
 */
class IFbClient
{
 public:
  virtual ~IFbClient() = default;
  IFbClient() = default;

  /**
   * @brief Attaches to the given Firebird database.
   *
   * @param database The Firebird database connection string in the
   * `host/port:database` (or just `database`) form.
   * @param user The Firebird user name placed into the database parameter
   * buffer.
   * @param password The Firebird user password placed into the database
   * parameter buffer.
   *
   * @return Returns a true boolean value on the success or false otherwise.
   */
  virtual bool attach(const std::string& database, const std::string& user,
                      const std::string& password) = 0;

  /**
   * @brief Detaches from the database if currently attached.
   */
  virtual void detach() = 0;

  /**
   * @brief Returns a true boolean value in case of a present database
   * attachment.
   */
  virtual bool attached() const = 0;

  /**
   * @brief Executes the given query and returns the first column of the first
   * fetched row as a string.
   *
   * @param query The SQL query that selects a single scalar value.
   *
   * @return Returns the fetched value, or an empty string in case of any error.
   */
  virtual std::string query_scalar(const std::string& query) = 0;
};

}  // namespace firebirdi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ABSTRACT_IFBCLIENT_CLASS_H
