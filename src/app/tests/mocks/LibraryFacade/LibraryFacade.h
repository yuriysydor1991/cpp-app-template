#ifndef CPP_APP_TEMPLATE_012_LIBRARYFACADE_CLASS_H
#define CPP_APP_TEMPLATE_012_LIBRARYFACADE_CLASS_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>
#include <memory>

#include "ILib.h"
#include "LibraryContext.h"
#include "src/lib/facade/public/ILogger.h"

namespace CppAppTemplate012
{

class LibraryFacade
{
 public:
  using LibraryContextPtr = CppAppTemplate012::LibraryContextPtr;

  virtual ~LibraryFacade() = default;
  LibraryFacade() = default;

  inline static std::unique_ptr<
      testing::MockFunction<ILibPtr(LibraryContextPtr ctx)>>
      create_library_mock;
  inline static std::unique_ptr<testing::MockFunction<LibraryContextPtr()>>
      create_library_context_mock;
  inline static std::unique_ptr<testing::MockFunction<ILibPtr()>>
      create_default_lib_mock;
  inline static std::unique_ptr<
      testing::MockFunction<void(const logger::ILoggerPtr& appLogger)>>
      init_logger_mock;

  inline static void resetMocks()
  {
    create_library_mock = std::make_unique<
        testing::MockFunction<ILibPtr(LibraryContextPtr ctx)>>();
    create_library_context_mock =
        std::make_unique<testing::MockFunction<LibraryContextPtr()>>();
    create_default_lib_mock =
        std::make_unique<testing::MockFunction<ILibPtr()>>();
    init_logger_mock = std::make_unique<
        testing::MockFunction<void(const logger::ILoggerPtr& appLogger)>>();
  }

  inline static ILibPtr create_library(LibraryContextPtr ctx)
  {
    EXPECT_NE(create_library_mock, nullptr);
    return create_library_mock->AsStdFunction()(ctx);
  }
  inline static LibraryContextPtr create_library_context()
  {
    EXPECT_NE(create_library_context_mock, nullptr);
    return create_library_context_mock->AsStdFunction()();
  }
  inline static ILibPtr create_default_lib()
  {
    EXPECT_NE(create_default_lib_mock, nullptr);
    return create_default_lib_mock->AsStdFunction()();
  }
  // The logger adoption is an infrastructure call which every application run
  // performs, so it stays silent for the tests which set no expectation on it.
  inline static void init_logger(const logger::ILoggerPtr& appLogger)
  {
    if (init_logger_mock == nullptr) {
      return;
    }

    init_logger_mock->AsStdFunction()(appLogger);
  }
};

}  // namespace CppAppTemplate012

#endif  // CPP_APP_TEMPLATE_012_LIBRARYFACADE_CLASS_H
