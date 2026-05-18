#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_CLASS_H

#include <gmock/gmock.h>

#include <memory>
#include <string>
#include <vector>

#include "src/app/ApplicationContext.h"

namespace cv
{

struct Rect
{
  int x{0};
  int y{0};
  int width{0};
  int height{0};
};

class Mat
{
 public:
  bool empty() const { return true; }
};

}  // namespace cv

namespace opencvi
{

class OpenCVController
{
 public:
  using faces_buffer = std::vector<cv::Rect>;
  using OpenCVControllerPtr = std::shared_ptr<OpenCVController>;
  using appctx = std::shared_ptr<app::ApplicationContext>;

  virtual ~OpenCVController() = default;

  OpenCVController() : defaultCascadePath{"/usr/share/opencv4/haarcascades/"
                                          "haarcascade_frontalface_default.xml"}
  {
    using ::testing::_;
    using ::testing::Return;
    using ::testing::ReturnRef;

    ON_CALL(*this, load_cascade(_)).WillByDefault(Return(true));
    ON_CALL(*this, get_cascade_path())
        .WillByDefault(ReturnRef(defaultCascadePath));
    ON_CALL(*this, run(_)).WillByDefault(Return(true));
    ON_CALL(*this, face_recognition_example(_)).WillByDefault(Return(true));

    if (onMockCreate) {
      onMockCreate(*this);
    }
  }

  inline static std::function<void(OpenCVController&)> onMockCreate;

  std::string defaultCascadePath;

  MOCK_METHOD(bool, load_cascade, (const std::string& cascadePath));
  MOCK_METHOD(faces_buffer, detect, (const cv::Mat& image));
  MOCK_METHOD(faces_buffer, detect, (const std::string& imagePath));
  MOCK_METHOD(const std::string&, get_cascade_path, (), (const));
  MOCK_METHOD(bool, run, (appctx ctx));
  MOCK_METHOD(bool, face_recognition_example, (appctx ctx));

  inline static OpenCVControllerPtr create()
  {
    return std::make_shared<OpenCVController>();
  }
};

using OpenCVControllerPtr = OpenCVController::OpenCVControllerPtr;

}  // namespace opencvi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_CLASS_H
