#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

#include "src/app/ApplicationContext.h"

namespace Gtkmm3i
{

class GtkmmIniter
{
 public:
  virtual ~GtkmmIniter() = default;
  GtkmmIniter()
  {
    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(GtkmmIniter&)> onMockCreate;

  MOCK_METHOD(int, run, (std::shared_ptr<app::ApplicationContext>));
};

}  // namespace Gtkmm3i

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H
