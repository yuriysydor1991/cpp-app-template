#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LLAMACPPCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LLAMACPPCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace llamacppi
{

class LlamaCPPController
{
 public:
  using result = std::optional<std::string>;
  using piece_handler = std::function<bool(const std::string& piece)>;
  using LlamaCPPControllerPtr = std::shared_ptr<LlamaCPPController>;

  virtual ~LlamaCPPController() = default;

  LlamaCPPController()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, init(_)).WillByDefault(Return(true));
    ON_CALL(*this, ask(_, _)).WillByDefault(Return(result{""}));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  /// @brief Hand a test own expectations over, so they live and get verified
  /// within that very test.
  inline static std::function<void(LlamaCPPController&)> onMockCreate;

  MOCK_METHOD(bool, init, (const std::string& modelPath));
  MOCK_METHOD(result, ask,
              (const std::string& question, const piece_handler& onPiece));

  inline static LlamaCPPControllerPtr create()
  {
    return std::make_shared<::testing::NiceMock<LlamaCPPController>>();
  }
};

using LlamaCPPControllerPtr = LlamaCPPController::LlamaCPPControllerPtr;

}  // namespace llamacppi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LLAMACPPCONTROLLER_CLASS_H
