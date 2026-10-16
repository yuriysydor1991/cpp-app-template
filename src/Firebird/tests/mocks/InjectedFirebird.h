#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_INJECTEDFIREBIRD_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_INJECTEDFIREBIRD_CLASS_H

#include <memory>

#include "src/Firebird/Firebird.h"
#include "src/Firebird/IFbClient.h"

namespace firebirdi
{

/**
 * @brief The real Firebird orchestration wired to an injected IFbClient
 * (a mock or a fake) instead of the native driver.
 */
class InjectedFirebird : public Firebird
{
 public:
  explicit InjectedFirebird(std::shared_ptr<IFbClient> nclient)
      : injected{nclient}
  {
  }

 protected:
  std::shared_ptr<IFbClient> create_client() override { return injected; }

 private:
  std::shared_ptr<IFbClient> injected;
};

}  // namespace firebirdi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_INJECTEDFIREBIRD_CLASS_H
