cmake_minimum_required(VERSION 3.13)

# The MediaPipe is a hard requirement of this branch rather than an optional
# integration, since the whole src/MediaPipe example is built around it.
if (NOT ENABLE_MEDIAPIPE)
  message(
    FATAL_ERROR
    "The src/MediaPipe sources estimate the poses with the MediaPipe library which is turned off by "
    "the ENABLE_MEDIAPIPE=OFF parameter. Drop the add_subdirectory(MediaPipe) call from the "
    "src/CMakeLists.txt file together with the whole src/MediaPipe subdirectory and provide "
    "another mocap::IPoseEstimator::create implementation to build the project without it."
  )
endif()

find_package(OpenCV REQUIRED COMPONENTS core imgproc)

add_library(
  TemplateProjectMediaPipeObj OBJECT
  LandmarksDecoder.cpp
  MediaPipeController.cpp
)

target_include_directories(
  TemplateProjectMediaPipeObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

# The MediaPipe itself is made available by it's enabler. The PUBLIC keyword
# hands it's headers over to the sources above and it's library over to the
# executable which links this object library.
target_link_libraries(
  TemplateProjectMediaPipeObj
  PUBLIC MediaPipe::mediapipe ${OpenCV_LIBS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectMediaPipeObj
)

# The MediaPipe library and it's license files go into the private library
# directory of the project, which the installed executable finds the library
# in by it's RPATH.
set(mediapipeLibDir "${CMAKE_INSTALL_LIBDIR}/${PROJECT_BINARY_NAME}")
get_target_property(mediapipeLibrary MediaPipe::mediapipe IMPORTED_LOCATION)
file(GLOB mediapipeLicenses "${mediapipe_wheel_SOURCE_DIR}/*.dist-info/licenses/*")

install(FILES ${mediapipeLibrary} ${mediapipeLicenses} DESTINATION ${mediapipeLibDir})

get_filename_component(binDir "${PROJECT_BINARY_INSTALLATION_DIR}" ABSOLUTE BASE_DIR "${CMAKE_INSTALL_PREFIX}")
get_filename_component(libDir "${mediapipeLibDir}" ABSOLUTE BASE_DIR "${CMAKE_INSTALL_PREFIX}")
file(RELATIVE_PATH binToLibDir "${binDir}" "${libDir}")

set_target_properties(
  ${PROJECT_BINARY_NAME}
  PROPERTIES INSTALL_RPATH "$ORIGIN/${binToLibDir}"
)

add_subdirectory(tests)
