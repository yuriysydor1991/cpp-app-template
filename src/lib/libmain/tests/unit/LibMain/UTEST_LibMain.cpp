#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "LibraryContext.h"
#include "src/lib/libmain/LibMain.h"

using namespace templatelib0;
using namespace lib0impl;
using namespace testing;

class UTEST_LibMain : public Test
{
 public:
  UTEST_LibMain() : libmain{std::make_shared<LibMain>()} {}

  std::shared_ptr<LibMain> libmain;
};

TEST_F(UTEST_LibMain, libcall_no_context_failure)
{
  EXPECT_FALSE(libmain->libcall({}));
}

TEST_F(UTEST_LibMain, libcall_success)
{
  EXPECT_TRUE(libmain->libcall(std::make_shared<LibraryContext>()));
}
