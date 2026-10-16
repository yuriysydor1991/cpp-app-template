#include "src/wt4/Wt4Server.h"

#include <cassert>
#include <exception>
#include <memory>
#include <string>
#include <thread>

#include "src/log/log.h"
#include "src/wt4/Wt4ArgsFilter.h"

namespace wt4server
{

Wt4Server::Wt4Server(const Wt::WEnvironment& env,
                     std::shared_ptr<Wt4Context> nwt4ctx)
    : Wt::WApplication(env),
      wt4ctx{nwt4ctx},
      wfactory{std::make_unique<widgets::WidgetsFactory>(wt4ctx)}
{
  assert(nwt4ctx != nullptr);
  assert(wfactory != nullptr);

  root()->addWidget(wfactory->create_guest_root());
}

int Wt4Server::run(std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr || ctx->get_argc() < 1 || ctx->get_argv() == nullptr) {
    LOGE("No valid application context provided");
    return app::IApplication::INVALID;
  }

  try {
    return serve(ctx);
  }
  catch (const std::exception& e) {
    LOGE("Wt server failure: " << e.what());
  }

  return app::IApplication::INVALID;
}

int Wt4Server::serve(std::shared_ptr<app::ApplicationContext> ctx)
{
  const std::string appPath{ctx->get_argv()[0]};

  Wt4ArgsFilter argsFilter;

  Wt::WServer server{appPath};

  server.setServerConfiguration(
      appPath, argsFilter.filter(ctx->get_argc(), ctx->get_argv()),
      WTHTTP_CONFIGURATION);

  server.addEntryPoint(
      Wt::EntryPointType::Application,
      [ctx](const Wt::WEnvironment& env) { return build_server(env, ctx); });

  if (!server.start()) {
    LOGE("Failure to start the Wt server");
    return app::IApplication::INVALID;
  }

  wait_for_stop(ctx);

  LOGI("Stopping the Wt server");

  server.stop();

  return 0;
}

void Wt4Server::wait_for_stop(std::shared_ptr<app::ApplicationContext> ctx)
{
  while (!ctx->get_stop()) {
    std::this_thread::sleep_for(stopCheckPeriod);
  }
}

std::unique_ptr<Wt4Server> Wt4Server::build_server(
    const Wt::WEnvironment& env, std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  auto wt4ctx = create_context(ctx);

  assert(wt4ctx != nullptr);

  auto wt4s = std::make_unique<Wt4Server>(env, wt4ctx);

  return wt4s;
}

std::shared_ptr<Wt4Context> Wt4Server::create_context(
    std::shared_ptr<app::ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  return std::make_shared<Wt4Context>(ctx);
}

}  // namespace wt4server
