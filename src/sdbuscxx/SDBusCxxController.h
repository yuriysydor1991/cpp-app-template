#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUSCXXCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUSCXXCONTROLLER_CLASS_H

#include <memory>

#include <sdbus-c++/sdbus-c++.h>

#include "src/app/ApplicationContext.h"

namespace sdbuscxxi
{

class SDBusCxxController
{
 public:
  using SDBusCxxControllerPtr = std::shared_ptr<SDBusCxxController>;

  virtual ~SDBusCxxController() = default;
  SDBusCxxController() = default;

  virtual bool run(std::shared_ptr<app::ApplicationContext> ctx);

  static SDBusCxxControllerPtr create();

protected:
    virtual bool init();
    virtual bool inited();

    std::shared_ptr<app::ApplicationContext> appctx;

private:
    bool make_example_demo_call();

    std::unique_ptr<sdbus::IConnection> conn;
};

using SDBusCxxControllerPtr = SDBusCxxController::SDBusCxxControllerPtr;

}  // namespace sdbuscxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SDBUSCXXCONTROLLER_CLASS_H
