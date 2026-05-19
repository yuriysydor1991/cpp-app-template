#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "LibraryContext.h"
#include "src/app/ApplicationContext.h"
#include "src/converters/ApplicationContext2LibraryContext.h"

using namespace app;
using namespace converters;
using namespace templatelib0;
using namespace testing;

class UTEST_ApplicationContext2LibraryContext : public Test
{
 public:
  UTEST_ApplicationContext2LibraryContext()
      : converter{std::make_shared<ApplicationContext2LibraryContext>()}
  {
  }

  std::shared_ptr<ApplicationContext> create_app_context(int& gargc,
                                                         char**& gargv)
  {
    return std::make_shared<ApplicationContext>(gargc, gargv);
  }

  std::shared_ptr<ApplicationContext> default_app_context()
  {
    return create_app_context(argc, argv);
  }

  std::shared_ptr<ApplicationContext2LibraryContext> converter;

  int argc{0};
  char** argv{nullptr};
};

TEST_F(UTEST_ApplicationContext2LibraryContext, no_contexts_failure)
{
  EXPECT_FALSE(converter->convert({}, {}));
}

TEST_F(UTEST_ApplicationContext2LibraryContext, no_app_context_failure)
{
  EXPECT_FALSE(converter->convert({}, std::make_shared<LibraryContext>()));
}

TEST_F(UTEST_ApplicationContext2LibraryContext, no_lib_context_failure)
{
  EXPECT_FALSE(converter->convert(default_app_context(), {}));
}

TEST_F(UTEST_ApplicationContext2LibraryContext, all_empty_context_success)
{
  EXPECT_TRUE(converter->convert(default_app_context(),
                                 std::make_shared<LibraryContext>()));
}
