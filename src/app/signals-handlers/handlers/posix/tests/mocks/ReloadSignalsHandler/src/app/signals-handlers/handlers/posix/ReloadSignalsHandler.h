#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_RELOADSIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_RELOADSIGNALSHANDLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/ISignalsHandler.h"

namespace app
{

class ReloadSignalsHandler : public ISignalsHandler
{
 public:
  ~ReloadSignalsHandler() override = default;

  ReloadSignalsHandler()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(ReloadSignalsHandler&)> onMockCreate;

  MOCK_METHOD(bool, install, (std::shared_ptr<ApplicationContext> ctx),
              (override));
  MOCK_METHOD(void, uninstall, (), (override));
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_RELOADSIGNALSHANDLER_CLASS_H
