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
#include <boost/log/utility/exception_handler.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <string>

#include "project-global-decls.h"
#include "src/log/severity-macro-consts.h"

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
  static constexpr const char* const defaultLogDateFormat =
      "%Y-%m-%d %H:%M:%S.%f";

  inline static const std::string default_log_name =
      project_decls::PROJECT_NAME + "-" + project_decls::PROJECT_BUILD_VERSION +
      ".log";

  virtual ~BoostLogController() = default;
  BoostLogController() = default;

  /**
   * @brief Sets the console and the file sinks up, replacing the ones of a
   * previous call.
   *
   * @return Returns false when the log file can't be opened, which leaves the
   * console sink alone.
   */
  static bool init(const std::string& filepath = default_log_name,
                   const unsigned int& nlvl = MAX_LOG_LEVEL,
                   bool toPrintValue = true);

  /**
   * @brief The default init of the LOG_INIT_DEFAULTS macro: a default log
   * file that can't be opened (a read-only current directory, for instance)
   * costs a single standard error warning and the logs go into the console.
   *
   * @return Returns false when the default log file can't be opened.
   */
  static bool init_defaults();

  static src::severity_logger_mt<logging::trivial::severity_level>& get_lg();

  static std::string get_filename(const std::string& filepath);

  static logging::trivial::severity_level get_boost_lvl(
      const unsigned int& prjlvl);

 private:
  static void init_stdout();
  static bool init_file();

  inline static std::atomic_bool toPrintMsgs{true};
  inline static std::string lfilepath;
  inline static logging::trivial::severity_level lvl = logging::trivial::info;
  /// @brief The multithreaded flavour, since every thread logs through it.
  inline static src::severity_logger_mt<logging::trivial::severity_level>
      logger;
};

}  // namespace boost_log

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_BOOSTLOGCONTROLLER_CLASS_H
