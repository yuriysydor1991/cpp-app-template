#include "src/log/log4cpp5-init/Log4Cpp5Init.h"

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
                           const log4cpp::Priority::PriorityLevel& nlvl,
                           const bool toPrintValue)
    : print{toPrintValue}, log_name{filepath}, log_lvl{nlvl}
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

}  // namespace log4cpp5i
