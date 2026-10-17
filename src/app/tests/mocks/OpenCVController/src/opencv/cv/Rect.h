#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_MOCK_CV_RECT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_MOCK_CV_RECT_CLASS_H

namespace cv
{

/// @brief The stand-in of the OpenCV rectangle the controller mock returns,
/// so the mocked tests need no OpenCV headers at all.
struct Rect
{
  int x{0};
  int y{0};
  int width{0};
  int height{0};
};

}  // namespace cv

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_OPENCVCONTROLLER_MOCK_CV_RECT_CLASS_H
