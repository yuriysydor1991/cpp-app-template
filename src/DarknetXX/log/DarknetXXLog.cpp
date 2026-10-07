#include "src/DarknetXX/log/DarknetXXLog.h"

#include <algorithm>
#include <string>

#include "src/log/log.h"

namespace darknetxxi
{

void DarknetXXLog::log(const unsigned short& loglvl, const char* const filePath,
                       const int& fileLine, const std::string& msg)
{
  using default_logger::DefaultLogger;

  // A network load alone writes dozens of the info messages (the layers
  // table and the like), so the darknetxx info and debug messages go a level
  // down, while the warnings and the errors keep theirs.
  const auto level = loglvl < DefaultLogger::LVL_INFO
                         ? loglvl
                         : std::min(static_cast<unsigned short>(loglvl + 1U),
                                    DefaultLogger::LVL_TRACE);

  DefaultLogger::log(level, filePath, fileLine, msg);
}

}  // namespace darknetxxi
