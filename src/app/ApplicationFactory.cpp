#include <memory>
#include <cassert>

#include "src/app/ApplicationContext.h"
#include "src/app/IApplication.h"
#include "src/app/Application.h"
#include "src/app/ApplicationFactory.h"

namespace app {

std::shared_ptr<ApplicationContext> ApplicationFactory::create_default_context (int& gargc, char** &gargv)
{
  return std::make_shared<ApplicationContext> (gargc, gargv) ;
}

std::shared_ptr<IApplication> ApplicationFactory::create_default_application()
{
  return std::make_shared<Application> () ;
}

std::shared_ptr<IApplication> ApplicationFactory::create_application([[maybe_unused]] std::shared_ptr<ApplicationContext> ctx)
{
  return create_default_application () ;
}

int ApplicationFactory::run(int& gargc, char** &gargv)
{
  std::shared_ptr<ApplicationContext> ctx = create_default_context (gargc, gargv) ;

  assert(ctx != nullptr);

  std::shared_ptr<IApplication> app = create_application (ctx) ;

  assert(app != nullptr);

  return app->run(ctx);
}

int ApplicationFactory::execute(int& gargc, char** &gargv)
{
  std::shared_ptr<ApplicationFactory> factory = std::make_shared<ApplicationFactory> () ;

  return factory->run (gargc, gargv) ;
}

} //namespace app
