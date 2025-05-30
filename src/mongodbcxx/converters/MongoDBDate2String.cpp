#include "src/mongodbcxx/converters/MongoDBDate2String.h"

#include <chrono>
#include <iomanip>
#include <memory>
#include <sstream>

#include "src/mongodbcxx/mongocxx-includes.h"

namespace mongodbcxxi::converters
{

std::string MongoDBDate2String::convert(const bsoncxx::types::b_date& bdate)
{
  std::time_t time = std::chrono::system_clock::to_time_t(bdate);

  std::tm converterTime = *std::localtime(&time);

  std::ostringstream oss;

  oss << std::put_time(&converterTime, dateFormat);

  return oss.str();
}

}  // namespace mongodbcxxi::converters
