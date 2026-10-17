cmake_minimum_required(VERSION 3.13)

# The OpenCV is found here and not by the enabler, which is processed after
# the src directory, since the tests below link it too.
set(
  TEMPLATE_APP_OPENCV_COMPONENTS
  "core;objdetect;imgcodecs;imgproc"
  CACHE STRING
  "Semicolon-separated list of OpenCV components required by the project"
)

find_package(OpenCV REQUIRED COMPONENTS ${TEMPLATE_APP_OPENCV_COMPONENTS})

message(STATUS "OpenCV ${OpenCV_VERSION} found at ${OpenCV_INCLUDE_DIRS}")

add_library(
  TemplateProjectOpenCVControllerObj OBJECT
  OpenCVController.cpp
)

target_include_directories(
  TemplateProjectOpenCVControllerObj
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectOpenCVControllerObj
  PUBLIC ${OpenCV_LIBS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectOpenCVControllerObj
)

add_subdirectory(tests)
