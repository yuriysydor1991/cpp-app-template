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
  LzmaController() = default;

  MOCK_METHOD(buffer, compress, (const buffer& input));
  MOCK_METHOD(buffer, uncompress, (const buffer& input));

  inline static LzmaControllerPtr create()
  {
    return std::make_shared<LzmaController>();
  }
};

using LzmaControllerPtr = LzmaController::LzmaControllerPtr;

}  // namespace lzmai

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_LZMACONTROLLER_CLASS_H
