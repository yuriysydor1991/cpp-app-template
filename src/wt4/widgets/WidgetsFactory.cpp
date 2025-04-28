#include "src/wt4/widgets/WidgetsFactory.h"

#include <memory>

#include "src/wt4/Wt4Context.h"
#include "src/wt4/widgets/guest/Root.h"

namespace wt4server::widgets
{

WidgetsFactory::WidgetsFactory(std::shared_ptr<Wt4Context> nwt4ctx)
    : wt4ctx{nwt4ctx}
{
  assert(wt4ctx != nullptr);
}

std::unique_ptr<guest::Root> WidgetsFactory::create_guest_root()
{
  auto widget = std::make_unique<guest::Root>();

  widget->init(wt4ctx);

  return widget;
}

}  // namespace wt4server::widgets
