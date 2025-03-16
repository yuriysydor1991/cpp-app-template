#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>

namespace templateGtkmm3
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

  MOCK_METHOD(int, run, (int& argc, char**& argv));
};

}  // namespace templateGtkmm3

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GTKMMINITER_CLASS_H
