#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WT4CONTEXT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WT4CONTEXT_CLASS_H

#include <memory>

#include "src/app/ApplicationContext.h"

namespace wt4server
{

struct Wt4Context
{
  virtual ~Wt4Context() = default;
  explicit Wt4Context(std::shared_ptr<app::ApplicationContext> nAppCtx);

  std::shared_ptr<app::ApplicationContext> appctx;
};

}  // namespace wt4server

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WT4CONTEXT_CLASS_H
