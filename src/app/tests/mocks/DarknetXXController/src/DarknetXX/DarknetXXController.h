#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_DARKNETXXCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_DARKNETXXCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "src/DarknetXX/Detection.h"
#include "src/DarknetXX/weights/NetworkWeights.h"

namespace darknetxxi
{

class DarknetXXController
{
 public:
  using detections = std::optional<std::vector<Detection>>;
  using DarknetXXControllerPtr = std::shared_ptr<DarknetXXController>;

  virtual ~DarknetXXController() = default;

  DarknetXXController()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, init(_, _, _)).WillByDefault(Return(true));
    ON_CALL(*this, detect(_))
        .WillByDefault(Return(detections{std::vector<Detection>{}}));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  /// @brief Hand a test own expectations over, so they live and get verified
  /// within that very test.
  inline static std::function<void(DarknetXXController&)> onMockCreate;

  MOCK_METHOD(bool, init,
              (const std::string& cfg, const NetworkWeights& weights,
               const std::string& names));
  MOCK_METHOD(detections, detect, (const std::string& image));

  inline static DarknetXXControllerPtr create()
  {
    return std::make_shared<::testing::NiceMock<DarknetXXController>>();
  }
};

using DarknetXXControllerPtr = DarknetXXController::DarknetXXControllerPtr;

}  // namespace darknetxxi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_DARKNETXXCONTROLLER_CLASS_H
