#include "src/wt4/Wt4Server.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

#include <cassert>
#include <memory>

namespace wt4server
{

Wt4Server::Wt4Server(const Wt::WEnvironment& env, std::shared_ptr<Wt4Context> nwt4ctx) 
  : Wt::WApplication(env), wt4ctx{nwt4ctx}
{
  assert(nwt4ctx != nullptr);

  root()->addWidget(std::make_unique<Wt::WText>("Hello, Wt!"));
}

int Wt4Server::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  return Wt::WRun(ctx->argc, ctx->argv, [ctx](const Wt::WEnvironment& env) {
    return build_server(env, ctx);
  });
}

std::unique_ptr<Wt4Server> Wt4Server::build_server(const Wt::WEnvironment& env, std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  auto wt4ctx = create_context(ctx);

  assert(wt4ctx != nullptr);
  
  auto wt4s = std::make_unique<Wt4Server>(env, wt4ctx);

  return wt4s;
}

std::shared_ptr<Wt4Context> Wt4Server::create_context(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  return std::make_shared<Wt4Context>(ctx);
}

}  // namespace wt4server
