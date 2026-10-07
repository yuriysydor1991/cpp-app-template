cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_DARKNETXX
  "Enables the darknetxx (the C++ port of the Darknet neural network) object detection core for the project usage, fetched by internet"
  ON
)

if (NOT ENABLE_DARKNETXX)
  return()
endif()

set(TEMPLATE_APP_DARKNETXX_GIT "https://github.com/yuriysydor1991/darknetxx.git" CACHE STRING "The darknetxx project git source repository")
set(TEMPLATE_APP_DARKNETXX_GIT_TAG "f37cf3175d112008a6f44589552d22668629cd09" CACHE STRING "The darknetxx project git repository commit (or branch) of interest")

# The darknetxx core is the original Darknet C code computing with the C++
# network infrastructure of the darknetxx, which needs the very libraries the
# darknetxx application does.
enable_language(C)

find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs highgui videoio)
find_package(ZLIB REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenMP COMPONENTS C CXX)

template_project_default_3rdparty_enabler(
  NAME nlohmann_json
  GIT_REPOSITORY "https://github.com/nlohmann/json.git"
  GIT_TAG "v3.12.0"
)

# The darknetxx shared library exports it's facade alone, which saves the
# detected objects into the files rather than hands them over, while it's CMake
# project installs the library beside the project one. So the sources are
# fetched alone (no subdirectory of them holds the CMakeLists.txt) and the
# darknetxx network core gets built out of them right here.
include(FetchContent)

FetchContent_Declare(
  darknetxx
  GIT_REPOSITORY ${TEMPLATE_APP_DARKNETXX_GIT}
  GIT_TAG ${TEMPLATE_APP_DARKNETXX_GIT_TAG}
  SOURCE_SUBDIR the-sources-only
)

FetchContent_MakeAvailable(darknetxx)

set(MOD_DARKNET_SRC_ROOT "${darknetxx_SOURCE_DIR}/src/lib/darknet-adaptor/adaptors/detector-cmake-adaptor/darknet")

# The original Darknet sources the darknetxx compiles, which also configures
# the Darknet version.h into the build directory.
include("${MOD_DARKNET_SRC_ROOT}/../darknetxx-darknet-orig-sources.cmake")

file(
  GLOB_RECURSE darknetxxCxxSources
  "${darknetxx_SOURCE_DIR}/src/lib/darknet-adaptor/*.cpp"
  "${darknetxx_SOURCE_DIR}/src/lib/helpers/*.cpp"
  "${darknetxx_SOURCE_DIR}/src/lib/zlib/*.cpp"
)

list(FILTER darknetxxCxxSources EXCLUDE REGEX "/tests/|/detector-cmake-adaptor/")

# The core passes the library context classes of the facade around, while
# the logger implementation is left out: the project provides the one, which
# forwards the darknetxx log messages into the project log (see the
# src/DarknetXX/log directory).
add_library(
  darknetxx STATIC
  ${DARKNET_ORIG_C_SOURCES}
  ${DARKNET_ORIG_CXX_SOURCES}
  ${darknetxxCxxSources}
  "${darknetxx_SOURCE_DIR}/src/lib/facade/LibraryContext.cpp"
  "${darknetxx_SOURCE_DIR}/src/lib/facade/TrainingProgress.cpp"
  "${darknetxx_SOURCE_DIR}/src/log/cpplog4c.cpp"
)

# The darknetxx is made of this very template project, so it's sources take
# the headers of the same paths (src/log/log.h and the like) and declare the
# classes of the same names. The sources compiling with the darknetxx headers
# take the darknetxx include directories before any other one, while the
# DARKNETXX_COMPILE_DEFINITIONS rename it's logger namespace, so the project
# and the darknetxx loggers live together in the very same executable.
set(
  DARKNETXX_INCLUDE_DIRS
  "${darknetxx_SOURCE_DIR}"
  "${MOD_DARKNET_SRC_ROOT}"
  "${MOD_DARKNET_SRC_ROOT}/src"
  "${MOD_DARKNET_SRC_ROOT}/3rdparty/stb/include"
  "${CMAKE_BINARY_DIR}"
)

set(
  DARKNETXX_COMPILE_DEFINITIONS
  default_logger=darknetxx_default_logger
  OPENCV=1
  MAX_LOG_LEVEL=${MAX_LOG_LEVEL}
)

# the facade sources include their headers by the file names
target_include_directories(
  darknetxx PRIVATE
  ${DARKNETXX_INCLUDE_DIRS}
  "${darknetxx_SOURCE_DIR}/src/lib/facade/public"
)

target_compile_definitions(darknetxx PRIVATE ${DARKNETXX_COMPILE_DEFINITIONS})
set_target_properties(darknetxx PROPERTIES POSITION_INDEPENDENT_CODE ON)

# GCC 14+ turned several legacy C diagnostics into errors, which the original
# Darknet C sources still trip, so they stay the warnings (the darknetxx keeps
# them the same way).
include(CheckCCompilerFlag)

foreach(demotedError IN ITEMS incompatible-pointer-types int-conversion implicit-int return-mismatch)
  string(MAKE_C_IDENTIFIER "C_HAS_WNO_ERROR_${demotedError}" demotedErrorVar)
  check_c_compiler_flag("-Wno-error=${demotedError}" ${demotedErrorVar})

  if (${demotedErrorVar})
    target_compile_options(darknetxx PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wno-error=${demotedError}>)
  endif()
endforeach()

# The AVX/FMA code paths of the Darknet kernels run several times faster, while
# the binary needs the AVX2 capable CPU then. The packages for the other
# machines (the flatpak, the snap) turn them off.
if (CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|amd64)$" AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  set(darknetxxAvxDefault ON)
else()
  set(darknetxxAvxDefault OFF)
endif()

option(
  ENABLE_DARKNETXX_AVX
  "Set to ON to compile the AVX/FMA kernels of the Darknet C core in the non Debug builds (the binary needs the AVX2 capable CPU then)"
  ${darknetxxAvxDefault}
)

if (ENABLE_DARKNETXX_AVX)
  target_compile_options(
    darknetxx PRIVATE
    "$<$<AND:$<COMPILE_LANGUAGE:C>,$<NOT:$<CONFIG:Debug>>>:-ffp-contract=fast;-mavx;-mavx2;-mfma;-msse3;-msse4.1;-msse4.2>"
  )
endif()

target_link_libraries(
  darknetxx
  PUBLIC
    ${OpenCV_LIBS}
    ZLIB::ZLIB
    Threads::Threads
    nlohmann_json::nlohmann_json
)

# The OpenMP runs the Darknet kernels on all of the CPU cores.
if (OpenMP_C_FOUND AND OpenMP_CXX_FOUND)
  target_link_libraries(darknetxx PUBLIC OpenMP::OpenMP_C OpenMP::OpenMP_CXX)
endif()

# The application detects the objects with the YOLOv4-tiny network trained on
# the COCO data set by default: the network cfg file, the class names and a
# sample image come with the darknetxx sources, while the weights file gets
# downloaded into the build directory.
set(TEMPLATE_APP_DARKNETXX_WEIGHTS_URL "https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v4_pre/yolov4-tiny.weights" CACHE STRING "The network weights file to download for the PROJECT_DARKNETXX_CFG_PATH network")
set(TEMPLATE_APP_DARKNETXX_WEIGHTS_SHA256 "cf9fbfd0f6d4869b35762f56100f50ed05268084078805f0e7989efe5bb8ca87" CACHE STRING "The SHA256 hash of the TEMPLATE_APP_DARKNETXX_WEIGHTS_URL file, empty to skip the check")

option(
  ENABLE_DARKNETXX_WEIGHTS_DOWNLOAD
  "Downloads the TEMPLATE_APP_DARKNETXX_WEIGHTS_URL weights file into the build directory while configuring"
  ON
)

set(PROJECT_DARKNETXX_CFG_PATH "" CACHE STRING "The network cfg file the application loads while neither the --cfg nor the --dxxwjz2 parameter is given, the darknetxx yolov4-tiny.cfg one if empty")
set(PROJECT_DARKNETXX_WEIGHTS_PATH "" CACHE STRING "The network weights file the application loads while no --weights, --dxxwjz1 or --dxxwjz2 parameter is given, the downloaded TEMPLATE_APP_DARKNETXX_WEIGHTS_URL one if empty")
set(PROJECT_DARKNETXX_NAMES_PATH "" CACHE STRING "The class names file the application labels the objects with while neither the --names nor the --dxxwjz2 parameter is given, the darknetxx coco.names one if empty")
set(PROJECT_DARKNETXX_IMAGE_PATH "" CACHE STRING "The image the application detects the objects of while no --image parameter is given, the darknetxx dog.jpg one if empty")

if (NOT PROJECT_DARKNETXX_CFG_PATH)
  set(PROJECT_DARKNETXX_CFG_PATH "${darknetxx_SOURCE_DIR}/misc/examples/cfg/yolov4-tiny.cfg")
endif()

if (NOT PROJECT_DARKNETXX_NAMES_PATH)
  set(PROJECT_DARKNETXX_NAMES_PATH "${darknetxx_SOURCE_DIR}/misc/examples/cfg/coco.names")
endif()

if (NOT PROJECT_DARKNETXX_IMAGE_PATH)
  set(PROJECT_DARKNETXX_IMAGE_PATH "${darknetxx_SOURCE_DIR}/misc/data/dog.jpg")
endif()

if (NOT PROJECT_DARKNETXX_WEIGHTS_PATH)
  get_filename_component(weightsName "${TEMPLATE_APP_DARKNETXX_WEIGHTS_URL}" NAME)
  set(PROJECT_DARKNETXX_WEIGHTS_PATH "${CMAKE_BINARY_DIR}/models/${weightsName}")

  if (ENABLE_DARKNETXX_WEIGHTS_DOWNLOAD AND NOT EXISTS "${PROJECT_DARKNETXX_WEIGHTS_PATH}")
    message(STATUS "Downloading the ${TEMPLATE_APP_DARKNETXX_WEIGHTS_URL} weights file")

    if (TEMPLATE_APP_DARKNETXX_WEIGHTS_SHA256)
      set(weightsHash EXPECTED_HASH SHA256=${TEMPLATE_APP_DARKNETXX_WEIGHTS_SHA256})
    endif()

    file(
      DOWNLOAD "${TEMPLATE_APP_DARKNETXX_WEIGHTS_URL}" "${PROJECT_DARKNETXX_WEIGHTS_PATH}"
      ${weightsHash}
      TLS_VERIFY ON
      STATUS weightsStatus
    )

    list(GET weightsStatus 0 weightsCode)

    # A failed download leaves a broken file behind, which would be taken for
    # the downloaded one next time.
    if (NOT weightsCode EQUAL 0)
      file(REMOVE "${PROJECT_DARKNETXX_WEIGHTS_PATH}")
      message(WARNING "Fail to download the ${TEMPLATE_APP_DARKNETXX_WEIGHTS_URL} weights file (${weightsStatus}), so the application needs the --weights, the --dxxwjz1 or the --dxxwjz2 parameter")
    endif()
  endif()
endif()

message(STATUS "The darknetxx network: ${PROJECT_DARKNETXX_CFG_PATH} with ${PROJECT_DARKNETXX_WEIGHTS_PATH}")

# Link the darknetxx target to your target(s) of interest. Compile the
# sources including the darknetxx headers with the darknetxx include
# directories and definitions (see the src/DarknetXX/CMakeLists.txt):
#   target_include_directories(<target> PRIVATE ${DARKNETXX_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
#   target_compile_definitions(<target> PRIVATE ${DARKNETXX_COMPILE_DEFINITIONS})
#   target_link_libraries(<target> PUBLIC darknetxx)
