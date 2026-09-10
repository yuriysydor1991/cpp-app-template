#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_STOPSIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_STOPSIGNALSHANDLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/ISignalsHandler.h"

namespace app
{

class StopSignalsHandler : public ISignalsHandler
{
 public:
  ~StopSignalsHandler() override = default;

  StopSignalsHandler()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(StopSignalsHandler&)> onMockCreate;

  MOCK_METHOD(bool, install, (std::shared_ptr<ApplicationContext> ctx),
              (override));
  MOCK_METHOD(void, uninstall, (), (override));
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_STOPSIGNALSHANDLER_CLASS_H
