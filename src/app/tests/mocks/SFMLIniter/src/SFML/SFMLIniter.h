#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLINITER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace templateSFML
{

class SFMLIniter
{
 public:
  virtual ~SFMLIniter() = default;
  SFMLIniter()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(SFMLIniter& instance)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext> ctx));
};

}  // namespace templateSFML

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SFMLINITER_CLASS_H
