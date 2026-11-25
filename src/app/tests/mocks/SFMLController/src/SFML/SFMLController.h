#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace templateSFML
{

class SFMLController
{
 public:
  virtual ~SFMLController() = default;
  SFMLController()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(SFMLController& instance)> onMockCreate;

  MOCK_METHOD(int, run, (app::ApplicationContextPtr ctx));
};

}  // namespace templateSFML

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLCONTROLLER_CLASS_H
