cmake_minimum_required(VERSION 3.13)

# The RTMPose family pose estimation is a hard requirement of this branch
# rather than an optional integration, since the whole src/RTMPose example is
# built around it.
if (NOT ENABLE_RTMPOSE)
  message(
    FATAL_ERROR
    "The src/RTMPose sources estimate the poses with the RTMPose family models which are turned off by "
    "the ENABLE_RTMPOSE=OFF parameter. Drop the add_subdirectory(RTMPose) call from the "
    "src/CMakeLists.txt file together with the whole src/RTMPose subdirectory and provide "
    "another mocap::IPoseEstimator::create implementation to build the project without it."
  )
endif()

find_package(OpenCV REQUIRED COMPONENTS core imgproc)

add_library(
  TemplateProjectRTMPoseObj OBJECT
  PersonDetector.cpp
  PoseCrop.cpp
  PoseModel.cpp
  RTMPoseController.cpp
  SimCCDecoder.cpp
)

target_include_directories(
  TemplateProjectRTMPoseObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectRTMPoseObj
  PUBLIC onnxruntime::onnxruntime ${OpenCV_LIBS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectRTMPoseObj
)

add_subdirectory(tests)
