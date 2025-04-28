#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CUSTOM_WIDGET_ROOTGUEST_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CUSTOM_WIDGET_ROOTGUEST_CLASS_H

#include <Wt/WContainerWidget.h>

#include <memory>

#include "src/wt4/Wt4Context.h"
#include "src/wt4/widgets/ICustomWidget.h"

/**
 * @brief The template project custom widgets namespace.
 */
namespace wt4server::widgets::guest
{

/**
 * @brief The Wt instance initer and runner class.
 */
class Root : public Wt::WContainerWidget, public ICustomWidget
{
 public:
  virtual ~Root() = default;
  Root() = default;

  virtual bool init(std::shared_ptr<Wt4Context> wt4ctx) override;
};

}  // namespace wt4server::widgets::guest

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CUSTOM_WIDGET_ROOTGUEST_CLASS_H
