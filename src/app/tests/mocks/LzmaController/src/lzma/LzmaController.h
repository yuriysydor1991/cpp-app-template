#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_LZMACONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_LZMACONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <memory>
#include <vector>

namespace lzmai
{

class LzmaController
{
 public:
  using buffer = std::vector<unsigned char>;
  using LzmaControllerPtr = std::shared_ptr<LzmaController>;

  virtual ~LzmaController() = default;

  // Round trips by default, so a run with no expectation set succeeds.
  LzmaController()
  {
    ON_CALL(*this, compress).WillByDefault(testing::ReturnArg<0>());
    ON_CALL(*this, uncompress).WillByDefault(testing::ReturnArg<0>());
  }

  MOCK_METHOD(buffer, compress, (const buffer& input));
  MOCK_METHOD(buffer, uncompress, (const buffer& input));

  /// @brief The instance the create() hands out instead of a fresh one.
  inline static LzmaControllerPtr instance;

  inline static LzmaControllerPtr create()
  {
    return instance != nullptr
               ? instance
               : std::make_shared<testing::NiceMock<LzmaController>>();
  }
};

using LzmaControllerPtr = LzmaController::LzmaControllerPtr;

}  // namespace lzmai

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LZMACONTROLLER_CLASS_H
