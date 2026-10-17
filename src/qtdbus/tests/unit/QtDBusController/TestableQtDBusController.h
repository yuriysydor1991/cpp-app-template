#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_TESTABLEQTDBUSCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_TESTABLEQTDBUSCONTROLLER_CLASS_H

#include <QDBusConnection>

#include "src/qtdbus/QtDBusController.h"

namespace qtdbusi
{

/**
 * @brief Test double exposing the protected seams so run()'s orchestration may
 * be exercised without a live system bus: inited() is forced true and the
 * connection pointer handed to the (mocked) handler is an unused nullptr.
 */
class TestableQtDBusController : public QtDBusController
{
 protected:
  bool init() override { return true; }
  bool inited() const override { return true; }
  QDBusConnection* connection_ptr() override { return nullptr; }
};

}  // namespace qtdbusi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_TESTABLEQTDBUSCONTROLLER_CLASS_H
