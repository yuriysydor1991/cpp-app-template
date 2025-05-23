#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <memory>

namespace beasthttp
{

class HttpController
{
 public:
  virtual ~HttpController() = default;
  HttpController() = default;

  MOCK_METHOD(bool, serve, (std::shared_ptr<app::ApplicationContext> actx));
};

}  // namespace beasthttp

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_HTTPCONTROLLER_CLASS_H
