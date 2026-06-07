#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_ZLIBCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_ZLIBCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <memory>
#include <string>
#include <vector>

namespace zlibi
{

class ZlibController
{
 public:
  using buffer = std::vector<unsigned char>;
  using ZlibControllerPtr = std::shared_ptr<ZlibController>;

  virtual ~ZlibController() = default;
  ZlibController() = default;

  MOCK_METHOD(buffer, compress, (const buffer& input));
  MOCK_METHOD(buffer, uncompress, (const buffer& input));
  MOCK_METHOD(bool, compress_to_file,
              (const std::string& path, const buffer& input));
  MOCK_METHOD(buffer, uncompress_from_file, (const std::string& path));

  inline static ZlibControllerPtr create()
  {
    return std::make_shared<ZlibController>();
  }
};

using ZlibControllerPtr = ZlibController::ZlibControllerPtr;

}  // namespace zlibi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_ZLIBCONTROLLER_CLASS_H
