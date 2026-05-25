#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_PLOTGETCPPCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_PLOTGETCPPCONTROLLER_CLASS_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "src/app/ApplicationContext.h"

namespace plotgencppi
{

/**
 * @brief gmock stand-in for the real PlotGenCppController, used by the app
 * component tests so that the Application logic can be exercised without
 * pulling in the PlotGenCpp/SFML libraries or opening an on-screen window.
 *
 * The static create() factory is redirected to the mock_create MockFunction so
 * a test can decide which instance (or none) the Application receives and set
 * the run() expectations on it beforehand.
 */
class PlotGenCppController
{
 public:
  using PlotGenCppControllerPtr = std::shared_ptr<PlotGenCppController>;

  virtual ~PlotGenCppController() = default;
  PlotGenCppController() = default;

  MOCK_METHOD(bool, run, (std::shared_ptr<app::ApplicationContext> ctx));

  using createMockType = testing::MockFunction<PlotGenCppControllerPtr()>;
  inline static std::shared_ptr<createMockType> mock_create;

  inline static PlotGenCppControllerPtr create()
  {
    return mock_create != nullptr ? mock_create->AsStdFunction()()
                                  : PlotGenCppControllerPtr{};
  }
};

using PlotGenCppControllerPtr = PlotGenCppController::PlotGenCppControllerPtr;

}  // namespace plotgencppi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_PLOTGETCPPCONTROLLER_CLASS_H
