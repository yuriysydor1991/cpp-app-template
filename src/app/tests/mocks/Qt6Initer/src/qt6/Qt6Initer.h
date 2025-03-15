#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H

#include <memory>

#include <gmock/gmock.h>

namespace templateQt6app
{

class Qt6Initer
{
 public:
  virtual ~Qt6Initer() = default;
  Qt6Initer()
  {
    if (onMockCreate) { onMockCreate(*this); }
  }

  inline static std::function<void(Qt6Initer& instance)> onMockCreate;

  MOCK_METHOD(int, run, (int& argc, char**& argv));

 protected:
  inline static const char* const main_qml_path = "qrc:/ui/qml/main.qml";
};

}  // namespace templateQt6app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H
