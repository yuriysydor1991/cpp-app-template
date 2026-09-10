#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CONTINUESIGNALSHANDLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CONTINUESIGNALSHANDLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/app/signals-handlers/ISignalsHandler.h"

namespace app
{

class ContinueSignalsHandler : public ISignalsHandler
{
 public:
  ~ContinueSignalsHandler() override = default;

  ContinueSignalsHandler()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(ContinueSignalsHandler&)> onMockCreate;

  MOCK_METHOD(bool, install, (std::shared_ptr<ApplicationContext> ctx),
              (override));
  MOCK_METHOD(void, uninstall, (), (override));
};

}  // namespace app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CONTINUESIGNALSHANDLER_CLASS_H
