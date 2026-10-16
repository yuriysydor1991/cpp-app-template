#include "RecordingRealLogger.h"

#include <string>

void RecordingRealLogger::log(const unsigned short& loglvl,
                              const std::string& msg)
{
  lastLvl = loglvl;
  lastMsg = msg;
}
