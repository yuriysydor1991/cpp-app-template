cmake_minimum_required(VERSION 3.13)

# The OpenPose is a hard requirement of this branch rather than an optional
# integration, since the whole src/OpenPose example is built around it.
if (NOT ENABLE_OPENPOSE)
  message(
    FATAL_ERROR
    "The src/OpenPose sources estimate the poses with the OpenPose model which is turned off by "
    "the ENABLE_OPENPOSE=OFF parameter. Drop the add_subdirectory(OpenPose) call from the "
    "src/CMakeLists.txt file together with the whole src/OpenPose subdirectory and provide "
    "another mocap::IPoseEstimator::create implementation to build the project without it."
  )
endif()

find_package(OpenCV REQUIRED COMPONENTS core dnn)

add_library(
  TemplateProjectOpenPoseObj OBJECT
  HeatmapDecoder.cpp
  OpenPoseController.cpp
)

target_include_directories(
  TemplateProjectOpenPoseObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectOpenPoseObj
  PUBLIC ${OpenCV_LIBS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectOpenPoseObj
)

add_subdirectory(tests)
