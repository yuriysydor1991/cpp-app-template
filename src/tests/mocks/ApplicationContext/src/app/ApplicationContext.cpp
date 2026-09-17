#include "ApplicationContext.h"

namespace app
{

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : margc{gargc}, margv{gargv}, mhttp_port{0}
{
  // The stop flag keeps its value unless a test case expects otherwise.
  ON_CALL(*this, get_stop()).WillByDefault([this]() { return mstop.load(); });
  ON_CALL(*this, set_stop(testing::_))
      .WillByDefault([this](const bool newValue) { mstop.store(newValue); });
}

}  // namespace app
