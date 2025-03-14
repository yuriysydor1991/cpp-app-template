#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "src/lib/libmain/LibFactory.h"
#include "LibraryFacade.h"

using namespace templatelib0;
using namespace testing;

class UTEST_LibraryFacade : public Test
{
 public:
  
  using LibFactory = lib0impl::LibFactory;

  UTEST_LibraryFacade()
    : facade{std::make_shared<LibraryFacade>()}
  {}

  LibFactory* get_libfactory_mock()
  {
    return *(LibFactory::available_instances.begin());
  }

  std::shared_ptr<LibraryFacade> facade;
};

TEST_F(UTEST_LibraryFacade, libcall_no_context_failure)
{
  LibFactory& libfactory = *get_libfactory_mock();

  EXPECT_CALL(libfactory, create_appropriate_lib(_)).Times(0);
  EXPECT_CALL(libfactory, create_default_context()).Times(0);

  EXPECT_FALSE(facade->libcall({}));
}
