#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_COMMANDLINEPARSER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_COMMANDLINEPARSER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace app
{

class CommandLineParser
{
 public:
  virtual ~CommandLineParser() = default;
  CommandLineParser()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(CommandLineParser& instance)> onMockCreate;

  MOCK_METHOD(bool, parse_args, (std::shared_ptr<ApplicationContext> ctx));
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_COMMANDLINEPARSER_CLASS_H
