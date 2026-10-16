#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_RECORDINGREALLOGGER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_RECORDINGREALLOGGER_CLASS_H

#include <string>

#include "src/log/default-logger/real-default-logger/RealDefaultLogger.h"

/**
 * @brief The real logger substitution which records the very last log call
 * instead of the actual logging.
 */
class RecordingRealLogger : public default_logger::RealDefaultLogger
{
 public:
  using RealDefaultLogger::log;

  void log(const unsigned short& loglvl, const std::string& msg) override;

  unsigned short lastLvl{0U};
  std::string lastMsg;
};

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_RECORDINGREALLOGGER_CLASS_H
