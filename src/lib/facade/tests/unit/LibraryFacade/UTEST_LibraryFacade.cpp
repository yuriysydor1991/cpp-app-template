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

  UTEST_LibraryFacade() : facade{std::make_shared<LibraryFacade>()}
  {
    get_libfactory_mock_wrapper()->recreate_real();
  }

  ~UTEST_LibraryFacade() { get_libfactory_mock_wrapper()->real.reset(); }

  LibFactory* get_libfactory_mock_wrapper()
  {
    EXPECT_FALSE(LibFactory::available_instances.empty());

    if (LibFactory::available_instances.empty()) {
      static LibFactory static_instance;

      return &static_instance;
    }

    return *(LibFactory::available_instances.begin());
  }

  std::shared_ptr<LibraryFacade> facade;
};

TEST_F(UTEST_LibraryFacade, libcall_no_context_failure)
{
  LibFactory& libfactory = *get_libfactory_mock_wrapper();

  EXPECT_CALL(libfactory.get_real(), create_appropriate_lib(_)).Times(0);
  EXPECT_CALL(libfactory.get_real(), create_default_context()).Times(0);

  EXPECT_FALSE(facade->libcall({}));
}

TEST_F(UTEST_LibraryFacade, create_library_context_success)
{
  LibFactory& libfactory = *get_libfactory_mock_wrapper();

  EXPECT_CALL(libfactory.get_real(), create_appropriate_lib(_)).Times(0);
  EXPECT_CALL(libfactory.get_real(), create_default_context())
      .Times(1)
      .WillOnce(Return(std::make_shared<LibraryContext>()));

  EXPECT_NE(facade->create_library_context(), nullptr);
}

TEST_F(UTEST_LibraryFacade, create_library_success)
{
  LibFactory& libfactory = *get_libfactory_mock_wrapper();

  EXPECT_CALL(libfactory.get_real(), create_appropriate_lib(_))
      .Times(1)
      .WillOnce(Return(std::make_shared<LibMain>()));
  EXPECT_CALL(libfactory.get_real(), create_default_context()).Times(0);

  EXPECT_NE(facade->create_library(std::make_shared<LibraryContext>()),
            nullptr);
}

TEST_F(UTEST_LibraryFacade, libcall_success)
{
  LibFactory& libfactory = *get_libfactory_mock_wrapper();

  auto libctx = std::make_shared<LibraryContext>();
  auto libinstance = std::make_shared<LibMain>();

  EXPECT_CALL(libfactory.get_real(), create_appropriate_lib(libctx))
      .Times(1)
      .WillOnce(Return(libinstance));
  EXPECT_CALL(libfactory.get_real(), create_default_context()).Times(0);
  EXPECT_CALL(*libinstance, libcall(libctx)).Times(1).WillOnce(Return(true));

  EXPECT_TRUE(facade->libcall(libctx));
}
