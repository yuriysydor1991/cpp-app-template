#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "LibraryFacade.h"
#include "src/app/Application.h"

using namespace app;
using namespace testing;

class UTEST_Application : public Test
{
 public:
  using LibraryFacade = templatelib0::LibraryFacade;
  using LibraryContext = templatelib0::LibraryContext;

  UTEST_Application()
      : app{std::make_shared<Application>()},
        appCtx{std::make_shared<ApplicationContext>(argc, argv)}
  {
  }

  ~UTEST_Application() { LibraryFacade::onMockCreate = nullptr; }

  int argc{0};
  char** argv{nullptr};

  std::shared_ptr<Application> app;
  std::shared_ptr<ApplicationContext> appCtx;
};

TEST_F(UTEST_Application, no_context_error) { EXPECT_NE(app->run({}), 0); }

TEST_F(UTEST_Application, normal_exit)
{
  MockFunction<void(LibraryFacade&)> libFacadeEnsurer;

  EXPECT_CALL(libFacadeEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](LibraryFacade& instance) {
        auto ctxInstance = std::make_shared<LibraryContext>();

        EXPECT_CALL(instance, create_library_context)
            .Times(1)
            .WillOnce(Return(ctxInstance));

        EXPECT_CALL(instance, libcall(_))
            .Times(1)
            .WillOnce(Invoke([=](std::shared_ptr<LibraryContext> ctx) {
              EXPECT_EQ(ctx, ctxInstance);
              return true;
            }));
      }));

  LibraryFacade::onMockCreate = libFacadeEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_EQ(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, failure_exit_no_lib_context)
{
  MockFunction<void(LibraryFacade&)> libFacadeEnsurer;

  EXPECT_CALL(libFacadeEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](LibraryFacade& instance) {
        EXPECT_CALL(instance, create_library_context)
            .Times(1)
            .WillOnce(Return(nullptr));

        EXPECT_CALL(instance, libcall(_)).Times(0);
      }));

  LibraryFacade::onMockCreate = libFacadeEnsurer.AsStdFunction();

  EXPECT_CALL(
      *appCtx,
      push_error(std::string{"No library context instance was created"}))
      .Times(1);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}

TEST_F(UTEST_Application, failure_exit_invalid_lib_result)
{
  MockFunction<void(LibraryFacade&)> libFacadeEnsurer;

  EXPECT_CALL(libFacadeEnsurer, Call(_))
      .Times(1)
      .WillOnce(Invoke([&](LibraryFacade& instance) {
        auto ctxInstance = std::make_shared<LibraryContext>();

        EXPECT_CALL(instance, create_library_context)
            .Times(1)
            .WillOnce(Return(ctxInstance));

        EXPECT_CALL(instance, libcall(_))
            .Times(1)
            .WillOnce(Invoke([=](std::shared_ptr<LibraryContext> ctx) {
              EXPECT_EQ(ctx, ctxInstance);
              return false;
            }));
      }));

  LibraryFacade::onMockCreate = libFacadeEnsurer.AsStdFunction();

  EXPECT_CALL(*appCtx, push_error(_)).Times(0);

  EXPECT_NE(app->run(appCtx), 0);

  EXPECT_TRUE(appCtx->errors.empty());

  EXPECT_FALSE(appCtx->print_help_and_exit);
  EXPECT_FALSE(appCtx->print_version_and_exit);
}
