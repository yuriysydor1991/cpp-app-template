#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WT4SERVER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WT4SERVER_CLASS_H

#include <memory>

#include <gmock/gmock.h>

#include "src/app/ApplicationContext.h"
#include "src/app/IApplication.h"

namespace wt4server
{

class Wt4Server
{
 public:
  virtual ~Wt4Server() = default;
  Wt4Server() = default;

  using runMockType = testing::MockFunction<int(std::shared_ptr<app::ApplicationContext>)>;

  inline static runMockType run_mock = runMockType{};
  
  inline static int run(std::shared_ptr<app::ApplicationContext> ctx)
  {
    auto run_mock_std = run_mock.AsStdFunction();

    return run_mock_std(ctx);
  }
};

}  // namespace wt4server

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WT4SERVER_CLASS_H
