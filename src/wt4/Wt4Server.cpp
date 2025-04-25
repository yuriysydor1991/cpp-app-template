#include "src/wt4/Wt4Server.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

#include <cassert>
#include <memory>

namespace wt4server
{

Wt4Server::Wt4Server(const Wt::WEnvironment& env) : Wt::WApplication(env)
{
  root()->addWidget(std::make_unique<Wt::WText>("Hello, Wt!"));
}

int Wt4Server::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  return Wt::WRun(ctx->argc, ctx->argv, [](const Wt::WEnvironment& env) {
    return std::make_unique<Wt4Server>(env);
  });
}

}  // namespace wt4server
