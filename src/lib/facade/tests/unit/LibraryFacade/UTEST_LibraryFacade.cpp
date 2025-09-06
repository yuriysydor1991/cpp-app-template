#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "LibraryFacade.h"
#include "src/lib/libmain/LibFactory.h"
#include "src/lib/libmain/LibMain.h"

using namespace templatelib0;
using namespace lib0impl;
using namespace testing;

class UTEST_LibraryFacade : public Test
{
 public:
  using LibFactory = lib0impl::LibFactory;

  UTEST_LibraryFacade() = default;
  ~UTEST_LibraryFacade() = default;
};

TEST_F(UTEST_LibraryFacade, create_default_lib_success)
{
  MockFunction<void(LibFactory&)> mockEnsurer;

  EXPECT_CALL(mockEnsurer, Call)
      .Times(1)
      .WillOnce(Invoke([](LibFactory& instance) {
        EXPECT_CALL(instance, create_appropriate_lib(_)).Times(1);
      }));

  LibFactory::onMockCreate = mockEnsurer.AsStdFunction();

  auto res = LibraryFacade::create_library({});
}

TEST_F(UTEST_LibraryFacade, create_default_lib_direct_success)
{
  MockFunction<void(LibFactory&)> mockEnsurer;

  EXPECT_CALL(mockEnsurer, Call)
      .Times(1)
      .WillOnce(Invoke([](LibFactory& instance) {
        EXPECT_CALL(instance, create_default_lib()).Times(1);
      }));

  LibFactory::onMockCreate = mockEnsurer.AsStdFunction();

  auto res = LibraryFacade::create_default_lib();
}

TEST_F(UTEST_LibraryFacade, create_library_context_success)
{
  MockFunction<void(LibFactory&)> mockEnsurer;

  EXPECT_CALL(mockEnsurer, Call)
      .Times(1)
      .WillOnce(Invoke([](LibFactory& instance) {
        EXPECT_CALL(instance, create_default_context()).Times(1);
      }));

  LibFactory::onMockCreate = mockEnsurer.AsStdFunction();

  auto res = LibraryFacade::create_library_context();
}
