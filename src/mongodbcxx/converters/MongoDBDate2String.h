#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_NOSQL_MONGODBDATE2STRING_CONVERTER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_NOSQL_MONGODBDATE2STRING_CONVERTER_CLASS_H

#include <string>

#include "src/mongodbcxx/mongocxx-includes.h"

/**
 * @brief The converters for the MongoDB results types values
 * into nice std formats.
 */
namespace mongodbcxxi::converters
{

/**
 * @brief The DBMS MongoDB date time converter to std::string.
 */
class MongoDBDate2String
{
 public:
  virtual ~MongoDBDate2String() = default;
  MongoDBDate2String() = default;

  /**
   * @brief Converts given bsoncxx date type instance into
   * human readable date string. Date string format stored
   * in the MongoDBDate2String::dateFormat constant.
   *
   * @param bdate The date to convert into a std::string.
   *
   * @return Returns converted date in the format
   * MongoDBDate2String::dateFormat.
   */
  static std::string convert(const bsoncxx::types::b_date& bdate);

 private:
  inline static constexpr const char* const dateFormat = "%Y-%m-%d";
};

}  // namespace mongodbcxxi::converters

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_NOSQL_MONGODBDATE2STRING_CONVERTER_CLASS_H
