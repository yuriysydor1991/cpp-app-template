#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "LibraryContext.h"
#include "LibraryFacade.h"
#include "src/app/ApplicationFactory.h"
#include "src/converters/ApplicationContext2LibraryContext.h"
#include "src/lib/libmain/LibMain.h"

using namespace app;
using namespace testing;
using namespace templatelib0;
using namespace lib0impl;
using namespace converters;

class CTEST_app : public Test
{
 public:
  CTEST_app() = default;

  ~CTEST_app()
  {
    ApplicationContext2LibraryContext::onMockCreate = nullptr;
    LibraryFacade::resetMocks();
  }

  int argc{0};
  char** argv{nullptr};

  ApplicationFactory facade;
};

TEST_F(CTEST_app, create_default_context_success)
{
  auto actx = facade.create_default_context(argc, argv);

  EXPECT_NE(actx, nullptr);
}

TEST_F(CTEST_app, create_default_arg_parser_success)
{
  auto argp = facade.create_default_arg_parser();

  EXPECT_NE(argp, nullptr);
}

TEST_F(CTEST_app, create_default_application_success)
{
  auto dapp = facade.create_default_application();

  EXPECT_NE(dapp, nullptr);
}

TEST_F(CTEST_app, create_help_printer_success)
{
  auto hpapp = facade.create_help_printer();

  EXPECT_NE(hpapp, nullptr);
}

TEST_F(CTEST_app, create_context_success)
{
  auto ctx = facade.create_context(argc, argv);

  EXPECT_NE(ctx, nullptr);
}

TEST_F(CTEST_app, create_application_success)
{
  auto actx = facade.create_default_context(argc, argv);

  EXPECT_NE(actx, nullptr);

  auto app = facade.create_application(actx);

  EXPECT_NE(app, nullptr);
}

TEST_F(CTEST_app, execute_success)
{
  auto libctx = std::make_shared<LibraryContext>();
  auto libmain = std::make_shared<LibMain>();

  auto create_library_mock =
      std::make_unique<testing::MockFunction<ILibPtr(LibraryContextPtr ctx)>>();
  auto create_library_context_mock =
      std::make_unique<testing::MockFunction<LibraryContextPtr()>>();
  auto create_default_lib_mock =
      std::make_unique<testing::MockFunction<ILibPtr()>>();
  testing::MockFunction<void(ApplicationContext2LibraryContext&)>
      converterEnsurer;

  EXPECT_CALL(*create_library_context_mock, Call)
      .Times(1)
      .WillOnce(testing::Return(libctx));
  EXPECT_CALL(*create_library_mock, Call)
      .Times(1)
      .WillOnce(testing::Return(libmain));

  EXPECT_CALL(*libmain, libcall(libctx))
      .Times(1)
      .WillOnce(testing::Return(true));

  EXPECT_CALL(converterEnsurer, Call)
      .Times(1)
      .WillOnce(testing::Invoke([](ApplicationContext2LibraryContext& i) {
        EXPECT_CALL(i, convert(_, _)).Times(1).WillOnce(testing::Return(true));
      }));

  LibraryFacade::create_library_mock = std::move(create_library_mock);
  LibraryFacade::create_library_context_mock =
      std::move(create_library_context_mock);
  LibraryFacade::create_default_lib_mock = std::move(create_default_lib_mock);
  ApplicationContext2LibraryContext::onMockCreate =
      converterEnsurer.AsStdFunction();

  int status = ApplicationFactory::execute(argc, argv);

  EXPECT_EQ(status, 0);
}
