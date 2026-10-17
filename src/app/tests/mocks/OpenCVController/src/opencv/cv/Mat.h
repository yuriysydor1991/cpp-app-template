#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_MOCK_CV_MAT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_MOCK_CV_MAT_CLASS_H

namespace cv
{

/// @brief The stand-in of the OpenCV image the controller mock takes, which
/// is always empty.
class Mat
{
 public:
  static bool empty() { return true; }
};

}  // namespace cv

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_MOCK_CV_MAT_CLASS_H
