#include "ApplicationContext.h"

namespace app
{

ApplicationContext::ApplicationContext(int& gargc, char**& gargv)
    : margc{gargc}, margv{gargv}
{
  // The pushed errors are kept like the real context keeps them, so the test
  // cases see them through the get_errors accessor too.
  ON_CALL(*this, push_error(testing::_))
      .WillByDefault([this](const std::string& errorDescription) {
        merrors.push_back(errorDescription);
      });
}

}  // namespace app
