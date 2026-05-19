#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "LibraryFacade.h"
#include "src/app/Application.h"
#include "src/lib/libmain/LibMain.h"

using namespace app;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  using LibraryFacade = templatelib0::LibraryFacade;
  using LibraryContext = templatelib0::LibraryContext;
  using ApplicationContext2LibraryContext =
      converters::ApplicationContext2LibraryContext;

  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
    templatelib0::LibraryFacade::resetMocks();
  }

  ~UTEST_Application()
  {
    templatelib0::LibraryFacade::resetMocks();
    ApplicationContext2LibraryContext::onMockCreate = nullptr;
  }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  MockFunction<void(ApplicationContext2LibraryContext&)> converterEnsurer;

  auto ctxInstance = std::make_shared<LibraryContext>();
  auto libmain = std::make_shared<lib0impl::LibMain>();

  EXPECT_CALL(*templatelib0::LibraryFacade::create_library_context_mock, Call())
      .Times(1)
      .WillOnce(Return(ctxInstance));

  EXPECT_CALL(*templatelib0::LibraryFacade::create_library_mock, Call(_))
      .Times(1)
      .WillOnce(Return(libmain));

  EXPECT_CALL(*libmain, libcall(_)).Times(1).WillOnce(Return(true));

  EXPECT_CALL(converterEnsurer, Call(_))
      .Times(1)
      .WillOnce([&](ApplicationContext2LibraryContext& instance) {
        EXPECT_CALL(instance, convert(_, _)).Times(1).WillOnce(Return(true));
      });

  ApplicationContext2LibraryContext::onMockCreate =
      converterEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, failure_exit_no_lib_context)
{
  MockFunction<void(ApplicationContext2LibraryContext&)> converterEnsurer;

  EXPECT_CALL(*templatelib0::LibraryFacade::create_library_context_mock, Call())
      .Times(1)
      .WillOnce(Return(nullptr));

  EXPECT_CALL(converterEnsurer, Call(_)).Times(0);

  ApplicationContext2LibraryContext::onMockCreate =
      converterEnsurer.AsStdFunction();

  EXPECT_CALL(
      *appCtx,
      push_error(std::string{"No library context instance was created"}))
      .Times(1);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, failure_exit_invalid_context_conversion_result)
{
  MockFunction<void(ApplicationContext2LibraryContext&)> converterEnsurer;

  auto ctxInstance = std::make_shared<LibraryContext>();

  EXPECT_CALL(*templatelib0::LibraryFacade::create_library_context_mock, Call())
      .Times(1)
      .WillOnce(Return(ctxInstance));

  EXPECT_CALL(converterEnsurer, Call(_))
      .Times(1)
      .WillOnce([&](ApplicationContext2LibraryContext& instance) {
        EXPECT_CALL(instance, convert(_, _)).Times(1).WillOnce(Return(false));
      });

  ApplicationContext2LibraryContext::onMockCreate =
      converterEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx,
              push_error(std::string{"Failure during context conversion"}))
      .Times(1);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, failure_exit_invalid_lib_result)
{
  MockFunction<void(ApplicationContext2LibraryContext&)> converterEnsurer;

  auto ctxInstance = std::make_shared<LibraryContext>();
  auto libmain = std::make_shared<lib0impl::LibMain>();

  EXPECT_CALL(*templatelib0::LibraryFacade::create_library_context_mock, Call())
      .Times(1)
      .WillOnce(Return(ctxInstance));

  EXPECT_CALL(*templatelib0::LibraryFacade::create_library_mock, Call(_))
      .Times(1)
      .WillOnce(Return(libmain));

  EXPECT_CALL(*libmain, libcall(_)).Times(1).WillOnce(Return(false));

  EXPECT_CALL(converterEnsurer, Call(_))
      .Times(1)
      .WillOnce([&](ApplicationContext2LibraryContext& instance) {
        EXPECT_CALL(instance, convert(_, _)).Times(1).WillOnce(Return(true));
      });

  ApplicationContext2LibraryContext::onMockCreate =
      converterEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx,
              push_error(std::string{"Invalid library execution status"}))
      .Times(1);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}
