#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_BOOSTLOGCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_BOOSTLOGCONTROLLER_CLASS_H

#include <atomic>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <string>

#include "project-global-decls.h"

namespace boost_log
{

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

/**
 * @brief Boost log controller class. Inits the boost logging system.
 */
class BoostLogController
{
 public:
  inline static constexpr const char* const defaultLogDateFormat =
      "%Y-%m-%d %H:%M:%S.%f";

  inline static const std::string default_log_name =
      project_decls::PROJECT_NAME + "-" + project_decls::PROJECT_BUILD_VERSION +
      ".log";

  virtual ~BoostLogController() = default;
  BoostLogController() = default;

  static void init(
      const std::string& filepath = default_log_name,
      const logging::trivial::severity_level& nlvl = logging::trivial::info,
      const bool toPrintValue = true);

  static src::severity_logger<logging::trivial::severity_level>& get_lg();

  static std::string get_filename(const std::string& filepath);

 private:
  static void init_stdout();
  static void init_file();

  inline static std::atomic_bool toPrintMsgs{true};
  inline static std::string lfilepath;
  inline static logging::trivial::severity_level lvl = logging::trivial::info;
  inline static src::severity_logger<logging::trivial::severity_level> lg;
};

}  // namespace boost_log

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_BOOSTLOGCONTROLLER_CLASS_H
