#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_RECORDINGLOGGER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_RECORDINGLOGGER_CLASS_H

#include <string>

#include "src/log/ILogger.h"

/**
 * @brief The logger::ILogger implementation which is not a RealDefaultLogger
 * descendant at all. It records the very last call of every interface method
 * instead of the actual logging, the very same way a log4cpp or a boost::log
 * wrapper would forward those calls into it's own logging library.
 */
class RecordingLogger : public logger::ILogger
{
 public:
  inline static const std::string lvlRepr{"REC"};

  void log(const unsigned short& loglvl, const std::string& msg) override;

  void log(const unsigned short& loglvl, const char* const filePath,
           const int& fileLine, const std::string& msg) override;

  bool logfile(const std::string& filepath) override;

  void print(const bool toPrintValue) override;

  void level(const unsigned short& nlvl) override;

  const std::string& lvl_repr(const unsigned short& glvl) override;

  bool init(const std::string& filepath, const unsigned short& nlvl,
            const bool toPrintValue) override;

  unsigned short lastLvl{0U};
  std::string lastMsg;
  std::string lastFilePath;
  int lastFileLine{0};
  std::string lastLogfile;
  bool lastPrint{false};
  unsigned short lastLevel{0U};
  unsigned short lastReprLvl{0U};
};

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_RECORDINGLOGGER_CLASS_H
