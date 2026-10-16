#include "src/log/log4cpp5-init/Log4Cpp5Init.h"

#include <fcntl.h>

#include <array>
#include <filesystem>
#include <iostream>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>

namespace log4cpp5i
{

bool Log4Cpp5Init::init(const std::string& filepath, const unsigned short& nlvl,
                        const bool toPrintValue)
{
  log4cpp::Category& root = log4cpp::Category::getRoot();

  root.removeAllAppenders();
  root.setPriority(get_log4cpp_priority(nlvl));

  const bool fileOpened = add_file_appender(root, filepath);

  if (!fileOpened || toPrintValue) {
    add_console_appender(root);
  }

  return fileOpened;
}

void Log4Cpp5Init::init_defaults()
{
  const std::string filepath = get_default_full_log_path();

  if (!init(filepath)) {
    std::cerr << "Fail to open the log file at " << filepath
              << ", logging into the console only" << std::endl;
  }
}

bool Log4Cpp5Init::add_file_appender(log4cpp::Category& root,
                                     const std::string& filepath)
{
  static constexpr mode_t file_mode = 00644;

  const int fd =
      ::open(filepath.c_str(), O_CREAT | O_APPEND | O_WRONLY, file_mode);

  if (fd < 0) {
    return false;
  }

  // the appender takes over the descriptor and closes it on its own
  auto* fileAppender = new log4cpp::FileAppender("file", fd);
  auto* layout = new log4cpp::PatternLayout();
  layout->setConversionPattern(default_conversation_pattern);
  fileAppender->setLayout(layout);

  root.addAppender(fileAppender);

  return true;
}

void Log4Cpp5Init::add_console_appender(log4cpp::Category& root)
{
  auto* consoleAppender = new log4cpp::OstreamAppender("console", &std::cout);
  auto* layout = new log4cpp::PatternLayout();
  layout->setConversionPattern(default_conversation_pattern);
  consoleAppender->setLayout(layout);

  root.addAppender(consoleAppender);
}

std::string Log4Cpp5Init::get_filename_only(const char* const filePath)
{
  std::filesystem::path fullPath{filePath};

  return fullPath.filename().string();
}

log4cpp::Priority::Value Log4Cpp5Init::get_log4cpp_priority(
    const unsigned short& prjsev)
{
  static const std::array<log4cpp::Priority::Value, MACRO_LVL_TRACE>
      log4cpp_prio{log4cpp::Priority::ERROR, log4cpp::Priority::WARN,
                   log4cpp::Priority::INFO, log4cpp::Priority::DEBUG,
                   trace_priority};

  if (prjsev <= MACRO_LVL_ERROR) {
    return log4cpp_prio.front();
  }

  if (prjsev >= MACRO_LVL_TRACE) {
    return log4cpp_prio.back();
  }

  return log4cpp_prio[prjsev - 1U];
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
