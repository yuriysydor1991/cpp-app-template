// The darknetxx DefaultLogger implementation of the project, which takes the
// place of the darknetxx own one (the darknetxx enabler leaves it out): the
// darknetxx core messages go into the project log through the DarknetXXLog
// sink. The DARKNETXX_COMPILE_DEFINITIONS rename the default_logger namespace
// of the darknetxx, so the class is not the project DefaultLogger one.
#include <src/log/default-logger/DefaultLogger.h>

#include <cstdarg>
#include <cstdio>
#include <string>

#include "src/DarknetXX/log/DarknetXXLog.h"

namespace default_logger
{

void DefaultLogger::log(const unsigned short& loglvl,
                        const char* const filePath, const int& fileLine,
                        const std::string& msg)
{
  darknetxxi::DarknetXXLog::log(loglvl, filePath, fileLine, msg);
}

bool DefaultLogger::enabled([[maybe_unused]] const unsigned short& loglvl)
{
  // the project logger drops the messages above it's level by itself
  return true;
}

std::string DefaultLogger::prepare_buff(const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);

  // the first pass measures the message on a copy of the arguments
  va_list sizing;
  va_copy(sizing, args);
  const int size = std::vsnprintf(nullptr, 0, fmt, sizing);
  va_end(sizing);

  std::string message(size > 0 ? static_cast<std::size_t>(size) + 1U : 1U,
                      '\0');

  std::vsnprintf(message.data(), message.size(), fmt, args);
  va_end(args);

  message.pop_back();

  return message;
}

}  // namespace default_logger
