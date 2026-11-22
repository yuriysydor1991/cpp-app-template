cmake_minimum_required(VERSION 3.13)

# The engine neutral body motion capture sources: the frame source, the pose
# estimator interface and the motion capture of the two. The engine sources of
# the flavor implement the estimator on top. The option itself is declared by
# the enabler only after the src directory.
if (DEFINED ENABLE_OPENCV AND NOT ENABLE_OPENCV)
  message(
    FATAL_ERROR
    "The src/MoCap sources read the frames through the OpenCV library which is turned off by "
    "the ENABLE_OPENCV=OFF parameter. Drop the add_subdirectory(MoCap) call from the "
    "src/CMakeLists.txt file together with the whole src/MoCap subdirectory, the engine "
    "sources and their usage of the src/app/applications/Application.cpp file to build "
    "the project without it."
  )
endif()

# The OpenCV is found here and not by the enabler, which is processed after
# the src directory, since the tests below link it too.
find_package(OpenCV REQUIRED COMPONENTS core videoio)

message(STATUS "OpenCV ${OpenCV_VERSION} found at ${OpenCV_INCLUDE_DIRS}")

add_library(
  TemplateProjectMoCapObj OBJECT
  FrameSource.cpp
  MotionCapture.cpp
)

target_include_directories(
  TemplateProjectMoCapObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectMoCapObj
  PUBLIC ${OpenCV_LIBS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectMoCapObj
)

add_subdirectory(tests)
