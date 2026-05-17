cmake_minimum_required(VERSION 3.13)

if(NOT DEFINED TEMPLATE_APP_OPENCV_COMPONENTS)
  set(TEMPLATE_APP_OPENCV_COMPONENTS "core;objdetect;imgcodecs;imgproc")
endif()

find_package(OpenCV REQUIRED COMPONENTS ${TEMPLATE_APP_OPENCV_COMPONENTS})

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
  ${PROJECT_BINARY_NAME}
  TemplateProjectOpenCVControllerObj
)

add_subdirectory(tests)
