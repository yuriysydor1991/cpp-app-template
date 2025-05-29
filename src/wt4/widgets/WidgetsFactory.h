#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CUSTOM_WIDGETSFACTORY_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CUSTOM_WIDGETSFACTORY_CLASS_H

#include <memory>

#include "src/wt4/Wt4Context.h"
#include "src/wt4/widgets/ICustomWidget.h"
#include "src/wt4/widgets/guest/Root.h"

namespace wt4server::widgets
{

/**
 * @brief The template project custom widgets factory.
 */
class WidgetsFactory
{
 public:
  virtual ~WidgetsFactory() = default;
  explicit WidgetsFactory(std::shared_ptr<Wt4Context> nwt4ctx);

  virtual std::unique_ptr<guest::Root> create_guest_root();

 private:
  std::shared_ptr<Wt4Context> wt4ctx;
};

}  // namespace wt4server::widgets

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CUSTOM_WIDGETSFACTORY_CLASS_H
