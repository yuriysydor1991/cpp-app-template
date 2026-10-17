#include "src/log/boost-log/BoostLogController.h"

#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace boost_log
{

bool BoostLogController::init(const std::string& filepath,
                              const unsigned int& nlvl, const bool toPrintValue)
{
  lfilepath = filepath;
  lvl = get_boost_lvl(nlvl);
  toPrintMsgs = toPrintValue;

  const auto core = logging::core::get();

  // A repeated init replaces the sinks of the previous one instead of adding
  // a second copy of them, and a sink failing later on (a full disk, a
  // removed log directory) drops its records instead of the process.
  core->remove_all_sinks();
  core->set_exception_handler(logging::make_exception_suppressor());

  init_stdout();

  const bool fileOpened = init_file();

  core->set_filter(logging::trivial::severity >= lvl);

  logging::add_common_attributes();

  return fileOpened;
}

bool BoostLogController::init_defaults()
{
  if (init()) {
    return true;
  }

  std::cerr << "Fail to open the log file at " << default_log_name
            << ", logging into the console only" << std::endl;

  return false;
}

void BoostLogController::init_stdout()
{
  if (!toPrintMsgs) {
    return;
  }

  logging::add_console_log(
      std::cout,
      keywords::format =
          (expr::stream
           << expr::format_date_time<boost::posix_time::ptime>(
                  "TimeStamp", defaultLogDateFormat)
           << " " << logging::trivial::severity << " "
           << expr::attr<boost::log::attributes::current_thread_id::value_type>(
                  "ThreadID")
           << " " << expr::smessage));
}

bool BoostLogController::init_file()
{
  // The text file backend opens the file with the first record alone, which
  // throws then, so the file gets opened here once to tell a failure first.
  if (!std::ofstream{lfilepath, std::ios_base::app}) {
    return false;
  }

  logging::add_file_log(
      keywords::file_name = lfilepath, keywords::open_mode = std::ios_base::app,
      keywords::auto_flush = true,
      keywords::format =
          (expr::stream
           << expr::format_date_time<boost::posix_time::ptime>(
                  "TimeStamp", defaultLogDateFormat)
           << " " << logging::trivial::severity << " "
           << expr::attr<boost::log::attributes::current_thread_id::value_type>(
                  "ThreadID")
           << " " << expr::smessage));

  return true;
}

src::severity_logger_mt<logging::trivial::severity_level>&
BoostLogController::get_lg()
{
  return logger;
}

std::string BoostLogController::get_filename(const std::string& filepath)
{
  std::filesystem::path fullPath{filepath};

  return fullPath.filename().string();
}

logging::trivial::severity_level BoostLogController::get_boost_lvl(
    const unsigned int& prjlvl)
{
  static const unsigned int max_sev = 5U;

  static const std::array<logging::trivial::severity_level, max_sev> boost_sevs{
      logging::trivial::error, logging::trivial::warning,
      logging::trivial::info,  logging::trivial::debug,
      logging::trivial::trace,
  };

  if (prjlvl <= 1U) {
    return boost_sevs.front();
  }

  if (prjlvl >= max_sev) {
    return boost_sevs.back();
  }

  return boost_sevs[prjlvl - 1U];
}

}  // namespace boost_log
