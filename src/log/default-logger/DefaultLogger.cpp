#include "src/log/default-logger/DefaultLogger.h"

#include <memory>
#include <string>

namespace default_logger
{

void DefaultLogger::log(const unsigned short& loglvl, const std::string& msg)
{
  real_logger()->log(loglvl, msg);
}

void DefaultLogger::log(const unsigned short& loglvl,
                        const char* const filePath, const int& fileLine,
                        const std::string& msg)
{
  real_logger()->log(loglvl, filePath, fileLine, msg);
}

void DefaultLogger::logfile(const std::string& filepath)
{
  real_logger()->logfile(filepath);
}

void DefaultLogger::print(const bool toPrintValue)
{
  real_logger()->print(toPrintValue);
}

void DefaultLogger::level(const unsigned short& nlvl)
{
  real_logger()->level(nlvl);
}

const std::string& DefaultLogger::lvl_repr(const unsigned short& glvl)
{
  return real_logger()->lvl_repr(glvl);
}

void DefaultLogger::init(const std::string& filepath,
                         const unsigned short& nlvl, const bool toPrintValue)
{
  real_logger()->init(filepath, nlvl, toPrintValue);
}

DefaultLogger::RealLoggerPtr DefaultLogger::real_logger()
{
  return real_logger_holder();
}

void DefaultLogger::real_logger(const RealLoggerPtr& newRealLogger)
{
  if (!newRealLogger) {
    return;
  }

  real_logger_holder() = newRealLogger;
  adopted = true;
}

bool DefaultLogger::real_logger_adopted() { return adopted; }

DefaultLogger::RealLoggerPtr& DefaultLogger::real_logger_holder()
{
  static RealLoggerPtr realLogger{std::make_shared<RealDefaultLogger>()};

  return realLogger;
}

}  // namespace default_logger
