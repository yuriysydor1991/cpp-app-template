cmake_minimum_required(VERSION 3.13)

# The src/opencv/CMakeLists.txt file finds and links the OpenCV components of
# the TEMPLATE_APP_OPENCV_COMPONENTS cache variable, since its tests link them
# too while this enabler is processed after the src directory.
option(
  ENABLE_OPENCV
  "Set to ON to enable the OpenCV integration (probe the system installation)"
  ON
)
