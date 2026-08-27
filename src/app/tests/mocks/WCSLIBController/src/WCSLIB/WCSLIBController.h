#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WCSLIBCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WCSLIBCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace wcslibi
{

class WCSLIBController
{
 public:
  using coordinates = std::vector<double>;
  using WCSLIBControllerPtr = std::shared_ptr<WCSLIBController>;

  virtual ~WCSLIBController() = default;

  WCSLIBController()
  {
    using ::testing::_;
    using ::testing::Return;

    ON_CALL(*this, parse(_)).WillByDefault(Return(true));
    ON_CALL(*this, select(_)).WillByDefault(Return(true));
    ON_CALL(*this, is_ready()).WillByDefault(Return(true));
    ON_CALL(*this, get_axes_count())
        .WillByDefault(Return(static_cast<int>(CELESTIAL_AXES)));
    ON_CALL(*this, get_axis_type(_))
        .WillByDefault(Return(std::string{AXIS_TYPE}));
    ON_CALL(*this, to_world(_))
        .WillByDefault(Return(coordinates(CELESTIAL_AXES)));
    ON_CALL(*this, to_pixel(_))
        .WillByDefault(Return(coordinates(CELESTIAL_AXES)));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(WCSLIBController&)> onMockCreate;

  MOCK_METHOD(bool, parse, (const std::string& header));
  MOCK_METHOD(bool, select, (int index));
  MOCK_METHOD(void, release, ());
  MOCK_METHOD(bool, is_ready, (), (const));
  MOCK_METHOD(int, get_representations_count, (), (const));
  MOCK_METHOD(int, get_axes_count, (), (const));
  // No const qualifier here, unlike the mocked class: the cppcheck parser
  // trips over a MOCK_METHOD carrying both the parameters and that qualifier.
  MOCK_METHOD(std::string, get_axis_type, (int axis));
  MOCK_METHOD(coordinates, to_world, (const coordinates& pixel));
  MOCK_METHOD(coordinates, to_pixel, (const coordinates& world));
  MOCK_METHOD(int, get_rejected_count, (), (const));
  MOCK_METHOD(int, last_status, (), (const));
  MOCK_METHOD(std::string, last_error, (), (const));

  inline static WCSLIBControllerPtr create()
  {
    return std::make_shared<WCSLIBController>();
  }

 private:
  /// @brief Any non empty axis type does, so the mocked representation reads
  /// like a celestial one by default.
  inline static constexpr const char* AXIS_TYPE = "RA---TAN";

  /// @brief The mocked conversions answer with a coordinate of the two
  /// celestial axes, just as the image the Application reads holds.
  inline static constexpr const coordinates::size_type CELESTIAL_AXES = 2U;
};

using WCSLIBControllerPtr = WCSLIBController::WCSLIBControllerPtr;

}  // namespace wcslibi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WCSLIBCONTROLLER_CLASS_H
