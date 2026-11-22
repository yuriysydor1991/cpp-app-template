cmake_minimum_required(VERSION 3.13)

# The MoveNet is a hard requirement of this branch rather than an optional
# integration, since the whole src/MoveNet example is built around it.
if (NOT ENABLE_MOVENET)
  message(
    FATAL_ERROR
    "The src/MoveNet sources estimate the poses with the MoveNet model which is turned off by "
    "the ENABLE_MOVENET=OFF parameter. Drop the add_subdirectory(MoveNet) call from the "
    "src/CMakeLists.txt file together with the whole src/MoveNet subdirectory and provide "
    "another mocap::IPoseEstimator::create implementation to build the project without it."
  )
endif()

find_package(OpenCV REQUIRED COMPONENTS core imgproc)

add_library(
  TemplateProjectMoveNetObj OBJECT
  MoveNetController.cpp
  MoveNetDecoder.cpp
)

target_include_directories(
  TemplateProjectMoveNetObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectMoveNetObj
  PUBLIC onnxruntime::onnxruntime ${OpenCV_LIBS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectMoveNetObj
)

add_subdirectory(tests)
