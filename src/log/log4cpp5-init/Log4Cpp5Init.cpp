#include "src/log/log4cpp5-init/Log4Cpp5Init.h"

#include <array>
#include <filesystem>
#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>

namespace log4cpp5i
{

Log4Cpp5Init::~Log4Cpp5Init() { deinit(); }

Log4Cpp5Init::Log4Cpp5Init(const std::string& filepath,
                           const unsigned short& nlvl, const bool toPrintValue)
    : print{toPrintValue},
      log_name{filepath},
      log_lvl{get_log4cpp_priority(nlvl)}
{
  init();
}

void Log4Cpp5Init::init()
{
  init_file();
  init_console();
}

void Log4Cpp5Init::init_file()
{
  auto* layout = new log4cpp::PatternLayout();
  layout->setConversionPattern(default_conversation_pattern);

  auto* fileAppender = new log4cpp::FileAppender("fileAppender", log_name);
  fileAppender->setLayout(layout);

  log4cpp::Category& root = log4cpp::Category::getRoot();

  root.setPriority(log_lvl);

  root.addAppender(fileAppender);
}

void Log4Cpp5Init::init_console()
{
  if (!print) {
    return;
  }

  auto* consoleLayout = new log4cpp::PatternLayout();
  consoleLayout->setConversionPattern(default_conversation_pattern);

  auto* consoleAppender = new log4cpp::OstreamAppender("console", &std::cout);
  consoleAppender->setLayout(consoleLayout);

  log4cpp::Category& root = log4cpp::Category::getRoot();

  root.setPriority(log_lvl);

  root.addAppender(consoleAppender);
}

std::string Log4Cpp5Init::get_filename_only(const char* const filePath)
{
  std::filesystem::path fullPath{filePath};

  return fullPath.filename().string();
}

void Log4Cpp5Init::deinit() { log4cpp::Category::shutdown(); }

log4cpp::Priority::PriorityLevel Log4Cpp5Init::get_log4cpp_priority(
    const unsigned short& prjsev)
{
  static const unsigned short max_prio = 5U;

  static const std::array<log4cpp::Priority::PriorityLevel, max_prio>
      log4cpp_prio{log4cpp::Priority::ERROR, log4cpp::Priority::WARN,
                   log4cpp::Priority::NOTICE, log4cpp::Priority::INFO,
                   log4cpp::Priority::DEBUG};

  if (prjsev >= max_prio) {
    return log4cpp_prio.back();
  }

  return log4cpp_prio[prjsev];
}

std::string Log4Cpp5Init::get_full_log_path(const std::string& logname)
{
  namespace fs = std::filesystem;

  static const fs::path default_log_path = DEFAULT_LOG_FILE_PATH;

  const fs::path logpath = default_log_path / logname;

  return logpath.string();
}

std::string Log4Cpp5Init::get_default_full_log_path()
{
  return get_full_log_path(default_log_name);
}

}  // namespace log4cpp5i
