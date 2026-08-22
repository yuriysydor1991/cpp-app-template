#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "LibraryFacade.h"
#include "src/app/ApplicationFactory.h"
#include "src/app/applications/Application.h"
#include "src/app/applications/ApplicationHelpPrinter.h"
#include "src/app/applications/ApplicationVersionPrinter.h"
#include "src/log/ILogger.h"
#include "src/log/log.h"

using namespace app;
using namespace testing;

namespace
{

/**
 * @brief The application owned logger stand-in which is handed over to the
 * library part. It performs no logging, the test checks the instance identity
 * only.
 */
class StubLogger : public logger::ILogger
{
 public:
  inline static const std::string lvlRepr{"STB"};

  void log([[maybe_unused]] const unsigned short& loglvl,
           [[maybe_unused]] const std::string& msg) override
  {
  }

  void log([[maybe_unused]] const unsigned short& loglvl,
           [[maybe_unused]] const char* const filePath,
           [[maybe_unused]] const int& fileLine,
           [[maybe_unused]] const std::string& msg) override
  {
  }

  void logfile([[maybe_unused]] const std::string& filepath) override {}

  void print([[maybe_unused]] const bool toPrintValue) override {}

  void level([[maybe_unused]] const unsigned short& nlvl) override {}

  const std::string& lvl_repr(
      [[maybe_unused]] const unsigned short& glvl) override
  {
    return lvlRepr;
  }

  void init([[maybe_unused]] const std::string& filepath,
            [[maybe_unused]] const unsigned short& nlvl,
            [[maybe_unused]] const bool toPrintValue) override
  {
  }
};

}  // namespace

class UTEST_ApplicationFactory : public Test
{
 public:
  UTEST_ApplicationFactory() : factory{std::make_shared<ApplicationFactory>()}
  {
  }

  ~UTEST_ApplicationFactory()
  {
    CommandLineParser::onMockCreate = nullptr;
    Application::onMockCreate = nullptr;
    ApplicationHelpPrinter::onMockCreate = nullptr;
    ApplicationVersionPrinter::onMockCreate = nullptr;
    templatelib0::LibraryFacade::init_logger_mock.reset();
    logMock::realLogger.reset();
  }

  inline std::shared_ptr<ApplicationContext> create_context(int& gargc,
                                                            char**& gargv)
  {
    return std::make_shared<ApplicationContext>(gargc, gargv);
  }

  std::shared_ptr<ApplicationFactory> factory;

  int customArgc{0};
  char** customArgv{nullptr};
};

TEST_F(UTEST_ApplicationFactory, create_default_context)
{
  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<ApplicationContext> ctx =
      factory->create_default_context(argc, argv);

  EXPECT_NE(ctx, nullptr);
}

TEST_F(UTEST_ApplicationFactory, create_default_arg_parser)
{
  std::shared_ptr<CommandLineParser> parser =
      factory->create_default_arg_parser();

  EXPECT_NE(parser, nullptr);
}

TEST_F(UTEST_ApplicationFactory, create_default_application)
{
  std::shared_ptr<IApplication> app = factory->create_default_application();

  EXPECT_NE(app, nullptr);
  EXPECT_NE(std::dynamic_pointer_cast<Application>(app), nullptr);
}

TEST_F(UTEST_ApplicationFactory, create_help_printer)
{
  std::shared_ptr<IApplication> app = factory->create_help_printer();

  EXPECT_NE(app, nullptr);
  EXPECT_NE(std::dynamic_pointer_cast<ApplicationHelpPrinter>(app), nullptr);
}

TEST_F(UTEST_ApplicationFactory, create_version_printer)
{
  std::shared_ptr<IApplication> app = factory->create_version_printer();

  EXPECT_NE(app, nullptr);
  EXPECT_NE(std::dynamic_pointer_cast<ApplicationVersionPrinter>(app), nullptr);
}

TEST_F(UTEST_ApplicationFactory, create_context)
{
  MockFunction<void(CommandLineParser & instance)> onMockCreateEnsurer;

  EXPECT_CALL(onMockCreateEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](CommandLineParser& instance) {
        EXPECT_CALL(instance, parse_args(_))
            .Times(1)
            .WillOnce(Invoke([&](std::shared_ptr<ApplicationContext> ctx) {
              EXPECT_EQ(&ctx->get_argc(), &customArgc);
              EXPECT_EQ(&ctx->get_argv(), &customArgv);
              return true;
            }));
      }));

  CommandLineParser::onMockCreate = onMockCreateEnsurer.AsStdFunction();

  std::shared_ptr<ApplicationContext> ctx =
      factory->create_context(customArgc, customArgv);

  EXPECT_NE(ctx, nullptr);
}

TEST_F(UTEST_ApplicationFactory, create_application_invalid_context_error)
{
  std::shared_ptr<IApplication> app = factory->create_application({});

  EXPECT_EQ(app, nullptr);
}

TEST_F(UTEST_ApplicationFactory, create_application_default)
{
  std::shared_ptr<ApplicationContext> ctx =
      create_context(customArgc, customArgv);

  std::shared_ptr<IApplication> app = factory->create_application(ctx);

  EXPECT_NE(app, nullptr);
  EXPECT_NE(std::dynamic_pointer_cast<Application>(app), nullptr);
}

TEST_F(UTEST_ApplicationFactory, create_application_help_printer)
{
  std::shared_ptr<ApplicationContext> ctx =
      create_context(customArgc, customArgv);

  ctx->set_print_help_and_exit(true);

  std::shared_ptr<IApplication> app = factory->create_application(ctx);

  EXPECT_NE(app, nullptr);
  EXPECT_NE(std::dynamic_pointer_cast<ApplicationHelpPrinter>(app), nullptr);
}

TEST_F(UTEST_ApplicationFactory, create_application_version_printer)
{
  std::shared_ptr<ApplicationContext> ctx =
      create_context(customArgc, customArgv);

  ctx->set_print_version_and_exit(true);

  std::shared_ptr<IApplication> app = factory->create_application(ctx);

  EXPECT_NE(app, nullptr);
  EXPECT_NE(std::dynamic_pointer_cast<ApplicationVersionPrinter>(app), nullptr);
}

TEST_F(UTEST_ApplicationFactory, factory_run_default_app)
{
  MockFunction<void(CommandLineParser & instance)> onMockCreateParserEnsurer;
  MockFunction<void(Application & instance)> onMockCreateAppEnsurer;

  EXPECT_CALL(onMockCreateParserEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](CommandLineParser& instance) {
        EXPECT_CALL(instance, parse_args(_))
            .Times(1)
            .WillOnce(Invoke([&](std::shared_ptr<ApplicationContext> ctx) {
              EXPECT_EQ(&ctx->get_argc(), &customArgc);
              EXPECT_EQ(&ctx->get_argv(), &customArgv);
              return true;
            }));
      }));

  EXPECT_CALL(onMockCreateAppEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](Application& instance) {
        EXPECT_CALL(instance, run(_)).Times(1).WillOnce(Return(0));
      }));

  CommandLineParser::onMockCreate = onMockCreateParserEnsurer.AsStdFunction();
  Application::onMockCreate = onMockCreateAppEnsurer.AsStdFunction();

  EXPECT_EQ(factory->run(customArgc, customArgv), 0);
}

TEST_F(UTEST_ApplicationFactory, factory_run_help_app)
{
  MockFunction<void(CommandLineParser & instance)> onMockCreateParserEnsurer;
  MockFunction<void(ApplicationHelpPrinter & instance)> onMockCreateAppEnsurer;

  EXPECT_CALL(onMockCreateParserEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](CommandLineParser& instance) {
        EXPECT_CALL(instance, parse_args(_))
            .Times(1)
            .WillOnce(Invoke([&](std::shared_ptr<ApplicationContext> ctx) {
              EXPECT_EQ(&ctx->get_argc(), &customArgc);
              EXPECT_EQ(&ctx->get_argv(), &customArgv);
              ctx->set_print_help_and_exit(true);
              return true;
            }));
      }));

  EXPECT_CALL(onMockCreateAppEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](ApplicationHelpPrinter& instance) {
        EXPECT_CALL(instance, run(_)).Times(1).WillOnce(Return(0));
      }));

  CommandLineParser::onMockCreate = onMockCreateParserEnsurer.AsStdFunction();
  ApplicationHelpPrinter::onMockCreate = onMockCreateAppEnsurer.AsStdFunction();

  EXPECT_EQ(factory->run(customArgc, customArgv), 0);
}

TEST_F(UTEST_ApplicationFactory, factory_run_version_app)
{
  MockFunction<void(CommandLineParser & instance)> onMockCreateParserEnsurer;
  MockFunction<void(ApplicationVersionPrinter & instance)>
      onMockCreateAppEnsurer;

  EXPECT_CALL(onMockCreateParserEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](CommandLineParser& instance) {
        EXPECT_CALL(instance, parse_args(_))
            .Times(1)
            .WillOnce(Invoke([&](std::shared_ptr<ApplicationContext> ctx) {
              EXPECT_EQ(&ctx->get_argc(), &customArgc);
              EXPECT_EQ(&ctx->get_argv(), &customArgv);
              ctx->set_print_version_and_exit(true);
              return true;
            }));
      }));

  EXPECT_CALL(onMockCreateAppEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](ApplicationVersionPrinter& instance) {
        EXPECT_CALL(instance, run(_)).Times(1).WillOnce(Return(0));
      }));

  CommandLineParser::onMockCreate = onMockCreateParserEnsurer.AsStdFunction();
  ApplicationVersionPrinter::onMockCreate =
      onMockCreateAppEnsurer.AsStdFunction();

  EXPECT_EQ(factory->run(customArgc, customArgv), 0);
}

TEST_F(UTEST_ApplicationFactory, factory_run_inits_the_library_logger)
{
  const logger::ILoggerPtr appLogger{std::make_shared<StubLogger>()};

  MockFunction<void(CommandLineParser & instance)> onMockCreateParserEnsurer;
  MockFunction<void(Application & instance)> onMockCreateAppEnsurer;

  auto init_logger_mock =
      std::make_unique<MockFunction<void(const logger::ILoggerPtr&)>>();

  logMock::realLogger = appLogger;

  // The application hands its own just initialized logger instance over to the
  // library part, so the whole project logs into a single target log file.
  EXPECT_CALL(*init_logger_mock, Call(appLogger)).Times(1);

  EXPECT_CALL(onMockCreateParserEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](CommandLineParser& instance) {
        EXPECT_CALL(instance, parse_args(_)).Times(1).WillOnce(Return(true));
      }));

  EXPECT_CALL(onMockCreateAppEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](Application& instance) {
        EXPECT_CALL(instance, run(_)).Times(1).WillOnce(Return(0));
      }));

  CommandLineParser::onMockCreate = onMockCreateParserEnsurer.AsStdFunction();
  Application::onMockCreate = onMockCreateAppEnsurer.AsStdFunction();
  templatelib0::LibraryFacade::init_logger_mock = std::move(init_logger_mock);

  EXPECT_EQ(factory->run(customArgc, customArgv), 0);
}

TEST_F(UTEST_ApplicationFactory, factory_execute_default_app)
{
  MockFunction<void(CommandLineParser & instance)> onMockCreateParserEnsurer;
  MockFunction<void(Application & instance)> onMockCreateAppEnsurer;

  EXPECT_CALL(onMockCreateParserEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](CommandLineParser& instance) {
        EXPECT_CALL(instance, parse_args(_))
            .Times(1)
            .WillOnce(Invoke([&](std::shared_ptr<ApplicationContext> ctx) {
              EXPECT_EQ(&ctx->get_argc(), &customArgc);
              EXPECT_EQ(&ctx->get_argv(), &customArgv);
              return true;
            }));
      }));

  EXPECT_CALL(onMockCreateAppEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](Application& instance) {
        EXPECT_CALL(instance, run(_)).Times(1).WillOnce(Return(0));
      }));

  CommandLineParser::onMockCreate = onMockCreateParserEnsurer.AsStdFunction();
  Application::onMockCreate = onMockCreateAppEnsurer.AsStdFunction();

  EXPECT_EQ(ApplicationFactory::execute(customArgc, customArgv), 0);
}
