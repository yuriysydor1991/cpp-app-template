cmake_minimum_required(VERSION 3.13)

# The option itself is declared by the enabler only after the src directory.
if (DEFINED ENABLE_OPENCV AND NOT ENABLE_OPENCV)
  message(
    FATAL_ERROR
    "The src/opencv sources require the OpenCV library which is turned off by "
    "the ENABLE_OPENCV=OFF parameter. Drop the add_subdirectory(opencv) call "
    "from the src/CMakeLists.txt file together with the whole src/opencv "
    "subdirectory and the OpenCV example of the "
    "src/app/applications/Application.cpp file to build the project without "
    "the OpenCV library."
  )
endif()

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
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectOpenCVControllerObj
  PUBLIC ${OpenCV_LIBS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectOpenCVControllerObj
)

add_subdirectory(tests)
