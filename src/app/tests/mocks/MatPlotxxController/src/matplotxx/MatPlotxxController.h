#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_MATPLOTXXCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_MATPLOTXXCONTROLLER_CLASS_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/app/ApplicationContext.h"

namespace matplotxxi
{

class MatPlotxxController
{
 public:
  using MatPlotxxControllerPtr = std::shared_ptr<MatPlotxxController>;

  virtual ~MatPlotxxController() = default;
  MatPlotxxController() = default;

  MOCK_METHOD(bool, run, (std::shared_ptr<app::ApplicationContext> ctx));

  using createMockType = testing::MockFunction<MatPlotxxControllerPtr()>;
  inline static std::shared_ptr<createMockType> mock_create;

  inline static MatPlotxxControllerPtr create()
  {
    return mock_create != nullptr ? mock_create->AsStdFunction()()
                                  : MatPlotxxControllerPtr{};
  }
};

using MatPlotxxControllerPtr = MatPlotxxController::MatPlotxxControllerPtr;

}  // namespace matplotxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_MATPLOTXXCONTROLLER_CLASS_H
