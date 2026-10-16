#include "RecordingLogger.h"

#include <string>

void RecordingLogger::log(const unsigned short& loglvl, const std::string& msg)
{
  lastLvl = loglvl;
  lastMsg = msg;
}

void RecordingLogger::log(const unsigned short& loglvl,
                          const char* const filePath, const int& fileLine,
                          const std::string& msg)
{
  lastFilePath = filePath;
  lastFileLine = fileLine;

  log(loglvl, msg);
}

void RecordingLogger::logfile(const std::string& filepath)
{
  lastLogfile = filepath;
}

void RecordingLogger::print(const bool toPrintValue)
{
  lastPrint = toPrintValue;
}

void RecordingLogger::level(const unsigned short& nlvl) { lastLevel = nlvl; }

const std::string& RecordingLogger::lvl_repr(const unsigned short& glvl)
{
  lastReprLvl = glvl;

  return lvlRepr;
}

void RecordingLogger::init(const std::string& filepath,
                           const unsigned short& nlvl, const bool toPrintValue)
{
  logfile(filepath);
  level(nlvl);
  print(toPrintValue);
}
