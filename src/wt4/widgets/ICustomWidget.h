#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ICUSTOMWIDGET_ABSTRACT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ICUSTOMWIDGET_ABSTRACT_CLASS_H

#include <memory>

#include "src/wt4/Wt4Context.h"

/**
 * @brief The template project custom widgets namespace.
 */
namespace wt4server::widgets
{

/**
 * @brief The Wt instance initer and runner class.
 */
class ICustomWidget
{
 public:
  virtual ~ICustomWidget() = default;
  ICustomWidget() = default;

  virtual bool init(std::shared_ptr<Wt4Context> wt4ctx) = 0;
};

}  // namespace wt4server::widgets

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ICUSTOMWIDGET_ABSTRACT_CLASS_H
