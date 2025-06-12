#include "src/log/boost-log/BoostLogController.h"

#include <filesystem>
#include <iostream>

namespace boost_log
{

void BoostLogController::init(const std::string& filepath,
                              const logging::trivial::severity_level& nlvl,
                              const bool toPrintValue)
{
  lfilepath = filepath;
  lvl = nlvl;
  toPrintMsgs = toPrintValue;

  init_stdout();

  init_file();

  logging::core::get()->set_filter(logging::trivial::severity >= lvl);

  logging::add_common_attributes();
}

void BoostLogController::init_stdout()
{
  if (!toPrintMsgs) {
    return;
  }

  logging::add_console_log(
      std::cout,
      keywords::format =
          (expr::stream << expr::format_date_time<boost::posix_time::ptime>(
                               "TimeStamp", defaultLogDateFormat)
                        << " " << logging::trivial::severity << " "
                        << expr::smessage));
}

void BoostLogController::init_file()
{
  logging::add_file_log(
      keywords::file_name = default_log_name,
      keywords::open_mode = std::ios_base::app,
      keywords::format =
          (expr::stream << expr::format_date_time<boost::posix_time::ptime>(
                               "TimeStamp", defaultLogDateFormat)
                        << " " << logging::trivial::severity << " "
                        << expr::smessage));
}

src::severity_logger<logging::trivial::severity_level>&
BoostLogController::get_lg()
{
  return lg;
}

std::string BoostLogController::get_filename(const std::string& filepath)
{
  std::filesystem::path fullPath{filepath};

  return fullPath.filename().string();
}

}  // namespace boost_log
