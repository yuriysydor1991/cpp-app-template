#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DARKNETXXLOG_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DARKNETXXLOG_CLASS_H

#include <string>

namespace darknetxxi
{

/**
 * @brief The sink of the darknetxx log messages, which forwards them into the
 * project log. The darknetxx logger implementation of the project (see the
 * DefaultLogger.cpp next to this file) hands them over here.
 *
 * Unlike the rest of the adaptor, it compiles with the project include
 * directories alone, so it's the project logger it reaches.
 */
class DarknetXXLog
{
 public:
  virtual ~DarknetXXLog() = default;
  DarknetXXLog() = default;

  static void log(const unsigned short& loglvl, const char* filePath,
                  const int& fileLine, const std::string& msg);
};

}  // namespace darknetxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DARKNETXXLOG_CLASS_H
