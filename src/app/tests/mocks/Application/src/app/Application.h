#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATION_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATION_CLASS_H

#include <memory>
#include <functional>

#include <gmock/gmock.h>

#include "src/app/IApplication.h"
#include "src/app/ApplicationContext.h"

namespace app {

class Application:
  public IApplication
{
public:
  virtual ~Application() = default;

  Application() 
  {
    if (onMockCreate) { onMockCreate(*this); }
  }

  inline static std::function<void(Application&)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<ApplicationContext> ctx), (override)) ;
};

} // namespace app

#endif // YOUR_CPP_APP_TEMPLATE_PROJECT_APPLICATION_CLASS_H
