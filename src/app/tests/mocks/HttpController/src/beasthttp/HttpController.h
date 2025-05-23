#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

namespace beasthttp
{

class HttpController
{
 public:
  virtual ~HttpController() = default;
  HttpController()
  {
    if (onMockCreate != nullptr) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(HttpController&)> onMockCreate;

  MOCK_METHOD(bool, serve, (std::shared_ptr<app::ApplicationContext> actx));
};

}  // namespace beasthttp

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H
