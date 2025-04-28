#include "src/wt4/widgets/guest/Root.h"

#include <Wt/WText.h>

#include <memory>

#include "src/wt4/Wt4Context.h"

namespace wt4server::widgets::guest
{

bool Root::init([[maybe_unused]] std::shared_ptr<Wt4Context> wt4ctx)
{
  addWidget(std::make_unique<Wt::WText>("Hello from guest::Root!"));

  return true;
}

}  // namespace wt4server::widgets::guest
