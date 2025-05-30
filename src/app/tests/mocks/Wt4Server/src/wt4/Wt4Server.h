#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WT4SERVER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WT4SERVER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"
#include "src/app/IApplication.h"

namespace wt4server
{

class Wt4Server
{
 public:
  virtual ~Wt4Server() = default;
  Wt4Server() = default;
  using runMockType =
      std::function<int(std::shared_ptr<app::ApplicationContext>)>;

  inline static runMockType run_mock;

  inline static int run(std::shared_ptr<app::ApplicationContext> ctx)
  {
    if (run_mock != nullptr) {
      return run_mock(ctx);
    }

    return 1;
  }
};

}  // namespace wt4server

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WT4SERVER_CLASS_H
