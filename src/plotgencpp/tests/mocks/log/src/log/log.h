#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H

#include <sstream>

#define LOG_INIT(filepath, logLvl, printMessages) \
  do {                                            \
  } while (0)
#define LOG_INIT_DEFAULTS() \
  do {                      \
  } while (0)
#define LOG_INIT_PATH(filepath) \
  do {                          \
  } while (0)

#define LOG_BODY(LOGLVL, msg)              \
  do {                                     \
    std::stringstream logMessageContainer; \
    logMessageContainer << msg;            \
    (void)logMessageContainer.str();       \
  } while (0)

#define LOGE(msg) LOG_BODY("E", msg)
#define LOGI(msg) LOG_BODY("I", msg)
#define LOGW(msg) LOG_BODY("W", msg)
#define LOGD(msg) LOG_BODY("D", msg)
#define LOGT(msg) LOG_BODY("T", msg)

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LOGGER_SUBSYSTEM_DECLARATIONS_H
