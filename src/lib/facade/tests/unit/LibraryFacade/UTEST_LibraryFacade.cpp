#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "LibraryFacade.h"
#include "src/lib/libmain/LibFactory.h"
#include "src/lib/libmain/LibMain.h"

using namespace CppAppTemplate012;
using namespace lib0impl;
using namespace testing;

class UTEST_LibraryFacade : public Test
{
 public:
  using LibFactory = lib0impl::LibFactory;

  UTEST_LibraryFacade() = default;
  ~UTEST_LibraryFacade() override { LibFactory::onMockCreate = nullptr; }

  ILibPtr lib{std::make_shared<LibMain>()};
  LibraryContextPtr libctx{std::make_shared<LibraryContext>()};
};

TEST_F(UTEST_LibraryFacade, create_library_success)
{
  MockFunction<void(LibFactory&)> mockEnsurer;

  EXPECT_CALL(mockEnsurer, Call)
      .Times(1)
      .WillOnce(Invoke([this](LibFactory& instance) {
        EXPECT_CALL(instance, create_appropriate_lib(libctx))
            .Times(1)
            .WillOnce(Return(lib));
      }));

  LibFactory::onMockCreate = mockEnsurer.AsStdFunction();

  EXPECT_EQ(LibraryFacade::create_library(libctx), lib);
}

TEST_F(UTEST_LibraryFacade, create_default_lib_success)
{
  MockFunction<void(LibFactory&)> mockEnsurer;

  EXPECT_CALL(mockEnsurer, Call)
      .Times(1)
      .WillOnce(Invoke([this](LibFactory& instance) {
        EXPECT_CALL(instance, create_default_lib())
            .Times(1)
            .WillOnce(Return(lib));
      }));

  LibFactory::onMockCreate = mockEnsurer.AsStdFunction();

  EXPECT_EQ(LibraryFacade::create_default_lib(), lib);
}

TEST_F(UTEST_LibraryFacade, create_library_context_success)
{
  MockFunction<void(LibFactory&)> mockEnsurer;

  EXPECT_CALL(mockEnsurer, Call)
      .Times(1)
      .WillOnce(Invoke([this](LibFactory& instance) {
        EXPECT_CALL(instance, create_default_context())
            .Times(1)
            .WillOnce(Return(libctx));
      }));

  LibFactory::onMockCreate = mockEnsurer.AsStdFunction();

  EXPECT_EQ(LibraryFacade::create_library_context(), libctx);
}
