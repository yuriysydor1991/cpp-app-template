cmake_minimum_required(VERSION 3.13)

# The src/MoCap/CMakeLists.txt and the engine CMakeLists.txt files find and
# link the OpenCV components they use, since their tests link them too while
# this enabler is processed after the src directory.
option(
  ENABLE_OPENCV
  "Set to ON to enable the OpenCV integration (probe the system installation)"
  ON
)
