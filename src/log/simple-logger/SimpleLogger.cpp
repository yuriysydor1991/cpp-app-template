#include "src/log/simple-logger/SimpleLogger.h"

#include <array>
#include <chrono>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

namespace simple_logger
{

void SimpleLogger::log(const unsigned short& loglvl, const std::string& msg)
{
  if (loglvl > lvl) {
    return;
  }

  const std::string ctimestamp = current_timestamp();
  const std::string& lvlrepr = lvl_repr(loglvl);

  std::ostringstream finalLog;

  finalLog << ctimestamp << " " << lvlrepr << " " << msg << std::endl;

  std::lock_guard<std::mutex> alogfile_m_guard{alogfile_m};

  if (alogfile.is_open()) {
    alogfile << finalLog.str();
  }

  if (!toPrintMsgs.load()) {
    return;
  }

  if (loglvl <= LVL_WARNING) {
    std::cerr << finalLog.str();
  } else {
    std::cout << finalLog.str();
  }
}

void SimpleLogger::log(const unsigned short& loglvl, const char* const filePath,
                       const int& fileLine, const std::string& msg)
{
  std::filesystem::path fullPath{filePath};

  std::string filename = fullPath.filename().string();

  log(loglvl, filename + ":" + std::to_string(fileLine) + " : " + msg);
}

void SimpleLogger::logfile(const std::string& filepath)
{
  if (filepath.empty()) {
    return;
  }

  alogfile.open(filepath.c_str(), std::fstream::app);

  if (!alogfile.is_open()) {
    throw std::runtime_error{"Fail to open the log file at " + filepath};
  }
}

void SimpleLogger::print(const bool toPrintValue)
{
  toPrintMsgs.store(toPrintValue);
}

void SimpleLogger::level(const unsigned short& nlvl) { lvl = nlvl; }

void SimpleLogger::init(const std::string& filepath, const unsigned short& nlvl,
                        const bool toPrintValue)
{
  logfile(filepath);
  level(nlvl);
  print(toPrintValue);
}

std::string SimpleLogger::current_timestamp()
{
  static constexpr const char nanosecFiller = '0';
  static constexpr const unsigned int nanosecWidth = 9U;

  using namespace std::chrono;

  auto now = system_clock::now();
  auto now_ns = time_point_cast<nanoseconds>(now);

  auto now_time_t = system_clock::to_time_t(now);
  std::tm timeHolder = *std::localtime(&now_time_t);

  auto duration_since_epoch = now_ns.time_since_epoch();
  auto nanosec = duration_cast<nanoseconds>(duration_since_epoch) % seconds(1);

  std::ostringstream oss;

  oss << std::put_time(&timeHolder, defaultLogDateFormat);
  oss << '.' << std::setfill(nanosecFiller) << std::setw(nanosecWidth)
      << nanosec.count();

  return oss.str();
}

const std::string& SimpleLogger::lvl_repr(const unsigned short& glvl)
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

}  // namespace simple_logger
