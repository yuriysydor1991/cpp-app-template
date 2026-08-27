#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace cfitsioi
{

class CFITSIOController
{
 public:
  using pixels_buffer = std::vector<double>;
  using image_size = std::tuple<long, long>;
  using CFITSIOControllerPtr = std::shared_ptr<CFITSIOController>;

  virtual ~CFITSIOController() = default;

  CFITSIOController()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, open(_, _)).WillByDefault(Return(true));
    ON_CALL(*this, create_image(_, _)).WillByDefault(Return(true));
    ON_CALL(*this, close()).WillByDefault(Return(true));
    ON_CALL(*this, write(_)).WillByDefault(Return(true));
    ON_CALL(*this, write_keyword(_, ::testing::An<const std::string&>(), _))
        .WillByDefault(Return(true));
    ON_CALL(*this, write_keyword(_, ::testing::An<double>(), _))
        .WillByDefault(Return(true));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(CFITSIOController&)> onMockCreate;

  MOCK_METHOD(bool, open, (const std::string& path, bool writable));
  MOCK_METHOD(bool, create_image,
              (const std::string& path, const image_size& size));
  MOCK_METHOD(bool, close, ());
  MOCK_METHOD(bool, is_open, (), (const));
  MOCK_METHOD(image_size, get_image_size, ());
  MOCK_METHOD(int, get_hdu_count, ());
  MOCK_METHOD(pixels_buffer, read, ());
  MOCK_METHOD(bool, write, (const pixels_buffer& pixels));
  MOCK_METHOD(std::string, read_keyword, (const std::string& name));
  MOCK_METHOD(bool, write_keyword,
              (const std::string& name, const std::string& value,
               const std::string& comment));
  MOCK_METHOD(bool, write_keyword,
              (const std::string& name, double value,
               const std::string& comment));
  MOCK_METHOD(std::string, read_header, ());
  MOCK_METHOD(pixels_buffer, get, ());
  MOCK_METHOD(int, last_status, (), (const));
  MOCK_METHOD(std::string, last_error, (), (const));

  // The mocked methods above carry no default arguments, so the defaults of
  // the mocked class are reproduced by the two overloads below.
  bool open(const std::string& path) { return this->open(path, false); }

  bool write_keyword(const std::string& name, const std::string& value)
  {
    return this->write_keyword(name, value, {});
  }

  // The overload it forwards to hides behind the MOCK_METHOD macro, which the
  // cppcheck parser skips over, so it takes this one for a static method.
  // cppcheck-suppress functionStatic
  bool write_keyword(const std::string& name, const double value)
  {
    return this->write_keyword(name, value, {});
  }

  inline static CFITSIOControllerPtr create()
  {
    return std::make_shared<CFITSIOController>();
  }
};

using CFITSIOControllerPtr = CFITSIOController::CFITSIOControllerPtr;

}  // namespace cfitsioi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CFITSIOCONTROLLER_CLASS_H
