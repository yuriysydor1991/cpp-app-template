#include "src/app/ApplicationFactory.h"

#include <cassert>
#include <memory>

#include "LibraryFacade.h"
#include "src/app/ApplicationContext.h"
#include "src/app/CMDParamNames.h"
#include "src/app/CommandLineParser.h"
#include "src/app/applications/Application.h"
#include "src/app/applications/ApplicationHelpPrinter.h"
#include "src/app/applications/ApplicationVersionPrinter.h"
#include "src/app/applications/IApplication.h"
#include "src/log/log.h"

namespace app
{

std::shared_ptr<ApplicationContext> ApplicationFactory::create_default_context(
    int& gargc, char**& gargv)
{
  return std::make_shared<ApplicationContext>(gargc, gargv);
}

std::shared_ptr<CommandLineParser>
ApplicationFactory::create_default_arg_parser()
{
  return std::make_shared<CommandLineParser>();
}

std::shared_ptr<ApplicationContext> ApplicationFactory::create_context(
    int& gargc, char**& gargv)
{
  std::shared_ptr<ApplicationContext> ctx =
      create_default_context(gargc, gargv);
  std::shared_ptr<CommandLineParser> argParser = create_default_arg_parser();

  assert(ctx != nullptr);
  assert(argParser != nullptr);

  if (ctx == nullptr) {
    LOGE("Fail to create the application context");
    return {};
  }

  if (argParser == nullptr) {
    LOGE("Fail to create the argument parser");
    return {};
  }

  argParser->parse_args(ctx);

  return ctx;
}

std::shared_ptr<IApplication> ApplicationFactory::create_default_application()
{
  return std::make_shared<Application>();
}

std::shared_ptr<IApplication> ApplicationFactory::create_help_printer()
{
  return std::make_shared<ApplicationHelpPrinter>();
}

std::shared_ptr<IApplication> ApplicationFactory::create_version_printer()
{
  return std::make_shared<ApplicationVersionPrinter>();
}

std::shared_ptr<IApplication> ApplicationFactory::create_application(
    std::shared_ptr<ApplicationContext> ctx)
{
  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context provided");
    return {};
  }

  if (ctx->get_print_help_and_exit()) {
    LOGT("Creating help printer application");
    return create_help_printer();
  }

  if (ctx->get_print_version_and_exit()) {
    LOGT("Creating version printer application");
    return create_version_printer();
  }

  LOGT("Creating the default application object");

  return create_default_application();
}

int ApplicationFactory::run(int& gargc, char**& gargv)
{
  const std::string custom_log =
      CommandLineParser::get_custom_logfile(gargc, gargv);

  if (custom_log.empty()) {
    LOG_INIT_DEFAULTS();
  } else {
    LOG_INIT_PATH(custom_log);
  }

  // The library part carries an own copy of the logging subsystem, so the just
  // initialized application logger instance is handed over to it. Without that
  // call the library would log into an own default log file instead of the one
  // chosen here and the project logs would be split in two.
  templatelib0::LibraryFacade::init_logger(LOG_REAL_LOGGER());

  std::shared_ptr<ApplicationContext> ctx = create_context(gargc, gargv);

  assert(ctx != nullptr);

  if (ctx == nullptr) {
    LOGE("No valid application context object provided");
    return IApplication::INVALID;
  }

  std::shared_ptr<IApplication> app = create_application(ctx);

  assert(app != nullptr);

  if (app == nullptr) {
    LOGE("Fail to create the application object");
    return IApplication::INVALID;
  }

  LOGD("Starting the application");

  return app->run(ctx);
}

int ApplicationFactory::execute(int& gargc, char**& gargv)
{
  std::shared_ptr<ApplicationFactory> factory =
      std::make_shared<ApplicationFactory>();

  return factory->run(gargc, gargv);
}

}  // namespace app
