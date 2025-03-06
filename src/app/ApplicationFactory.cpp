#include <memory>
#include <cassert>

#include "src/app/ApplicationContext.h"
#include "src/app/IApplication.h"
#include "src/app/Application.h"
#include "src/app/ApplicationHelpPrinter.h"
#include "src/app/ApplicationFactory.h"
#include "src/app/CommandLineParser.h"
#include "src/app/ApplicationVersionPrinter.h"

namespace app {

std::shared_ptr<ApplicationContext> ApplicationFactory::create_default_context (int& gargc, char** &gargv)
{
  return std::make_shared<ApplicationContext> (gargc, gargv) ;
}

std::shared_ptr<CommandLineParser> ApplicationFactory::create_default_arg_parser ()
{
  return std::make_shared<CommandLineParser> () ;
}

std::shared_ptr<ApplicationContext> ApplicationFactory::create_context (int& gargc, char** &gargv)
{
  std::shared_ptr<ApplicationContext> ctx = create_default_context (gargc, gargv) ;
  std::shared_ptr<CommandLineParser> argParser = create_default_arg_parser () ;

  assert(ctx != nullptr);
  assert(argParser != nullptr);

  if (ctx == nullptr)
  { return {} ; }

  if (argParser == nullptr)
  { return {} ; }

  argParser->parse_args(ctx);

  return ctx ;
}

std::shared_ptr<IApplication> ApplicationFactory::create_default_application ()
{
  return std::make_shared<Application> () ;
}

std::shared_ptr<IApplication> ApplicationFactory::create_help_printer ()
{
  return std::make_shared<ApplicationHelpPrinter> () ;
}

std::shared_ptr<IApplication> ApplicationFactory::create_version_printer ()
{
  return std::make_shared<ApplicationVersionPrinter> () ;
}

std::shared_ptr<IApplication> ApplicationFactory::create_application(std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) 
  { return {}; }

  if (ctx->print_help_and_exit)
  { return create_help_printer () ; }

  if (ctx->print_version_and_exit)
  { return create_version_printer () ; }

  return create_default_application () ;
}

int ApplicationFactory::run(int& gargc, char** &gargv)
{
  std::shared_ptr<ApplicationContext> ctx = create_context (gargc, gargv) ;

  assert(ctx != nullptr);

  if (ctx == nullptr) {
    return IApplication::INVALID;
  }

  std::shared_ptr<IApplication> app = create_application (ctx) ;

  assert(app != nullptr);

  if (app == nullptr) {
    return IApplication::INVALID;
  }

  return app->run(ctx);
}

int ApplicationFactory::execute(int& gargc, char** &gargv)
{
  std::shared_ptr<ApplicationFactory> factory = std::make_shared<ApplicationFactory> () ;

  return factory->run (gargc, gargv) ;
}

} //namespace app
