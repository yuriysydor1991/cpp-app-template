#include "src/log/default-logger/real-default-logger/RealDefaultLogger.h"

#include <array>
#include <chrono>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

namespace default_logger
{

void RealDefaultLogger::log(const unsigned short& loglvl,
                            const std::string& msg)
{
  if (loglvl > lvl) {
    return;
  }

  std::lock_guard<std::mutex> alogfile_m_guard{alogfile_m};

  std::ostringstream finalLog;

  // A freshly constructed stream adopts the global locale, which the
  // application is free to replace with one that groups the digits - that is
  // what std::locale::global(std::locale("")) does on most of the hosts. Such
  // a locale splits the logger own numeric fields with the group separators,
  // turning a thread id into 135,429,793,650,560, and it even eats the
  // microseconds zero padding, because the separators count towards the field
  // width. The log line layout is the logger own business and must not depend
  // on the application locale, so the message stream is pinned to the classic
  // one. The application message itself is formatted by the LOG_BODY macro
  // stream and keeps honouring the application locale.
  finalLog.imbue(std::locale::classic());

  insert_current_timestamp(finalLog);

  finalLog << " " << lvl_repr(loglvl) << " " << std::this_thread::get_id()
           << " " << msg << std::endl;

  const std::string finalLogStr = finalLog.str();

  if (alogfile.is_open()) {
    alogfile << finalLogStr;

    if (loglvl <= LVL_WARNING) {
      alogfile.flush();
    }
  }

  if (!toPrintMsgs.load()) {
    return;
  }

  if (loglvl <= LVL_WARNING) {
    std::cerr << finalLogStr;
  } else {
    std::cout << finalLogStr;
  }
}

void RealDefaultLogger::log(const unsigned short& loglvl,
                            const char* const filePath, const int& fileLine,
                            const std::string& msg)
{
  std::filesystem::path fullPath{filePath};

  std::string filename = fullPath.filename().string();

  log(loglvl, filename + ":" + std::to_string(fileLine) + " : " + msg);
}

void RealDefaultLogger::logfile(const std::string& filepath)
{
  if (filepath.empty()) {
    return;
  }

  if (alogfile.is_open()) {
    alogfile.close();
  }

  alogfile.open(filepath.c_str(), std::fstream::app);

  if (!alogfile.is_open()) {
    throw std::runtime_error{"Fail to open the log file at " + filepath};
  }
}

void RealDefaultLogger::print(const bool toPrintValue)
{
  toPrintMsgs.store(toPrintValue);
}

void RealDefaultLogger::level(const unsigned short& nlvl) { lvl = nlvl; }

void RealDefaultLogger::init(const std::string& filepath,
                             const unsigned short& nlvl,
                             const bool toPrintValue)
{
  logfile(filepath);
  level(nlvl);
  print(toPrintValue);
}

inline void RealDefaultLogger::insert_current_timestamp(std::ostringstream& oss)
{
  using namespace std::chrono;

  const auto now = system_clock::now();

  const time_t now_time_t = system_clock::to_time_t(now);
  std::tm timeHolder = *std::localtime(&now_time_t);

  oss << std::put_time(&timeHolder, defaultLogDateFormat);

#ifdef ENABLE_LOGS_MICROSECONDS_TIME
  static constexpr const char microsecFiller = '0';
  static constexpr const unsigned int microsecWidth = 6U;

  const auto timeSinceEpoch = now.time_since_epoch();
  auto seconds = duration_cast<std::chrono::seconds>(timeSinceEpoch);
  auto microseconds =
      duration_cast<std::chrono::microseconds>(timeSinceEpoch - seconds);

  // The fill character is sticky, unlike the width, so it is restored right
  // after the padded field. Otherwise it stays behind and pads whatever field
  // is appended to the very same message later on.
  const char previousFill = oss.fill();

  oss << '.' << std::setfill(microsecFiller) << std::setw(microsecWidth)
      << microseconds.count() << std::setfill(previousFill);
#endif  // ENABLE_LOGS_MICROSECONDS_TIME
}

const std::string& RealDefaultLogger::lvl_repr(const unsigned short& glvl)
{
  static constexpr const unsigned short maxLvls = 6U;
  static const std::array<const std::string, maxLvls> reprs{
      std::string{"UNK"}, std::string{"ERR"}, std::string{"WRN"},
      std::string{"INF"}, std::string{"DBG"}, std::string{"TRA"},
  };

  if (glvl >= maxLvls) {
    return reprs[0U];
  }

  return reprs[glvl];
}

std::string RealDefaultLogger::get_full_log_path(const std::string& logname)
{
  namespace fs = std::filesystem;

  static const fs::path default_log_path = DEFAULT_LOG_FILE_PATH;

  const fs::path logpath = default_log_path / logname;

  return logpath.string();
}

std::string RealDefaultLogger::get_default_full_log_path()
{
  return get_full_log_path(default_log_name);
}

}  // namespace default_logger
