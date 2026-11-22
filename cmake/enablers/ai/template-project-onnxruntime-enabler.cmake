cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_ONNXRUNTIME
    "Enables the system ONNX Runtime library the pose estimation models run with"
    ON
)

if (NOT ENABLE_ONNXRUNTIME)
    return()
endif()

# The distributions package the ONNX Runtime together with it's CMake package
# configuration: the libonnxruntime-dev package of the Debian 13 and the Ubuntu
# 26.04, the onnxruntime-devel one of the Fedora, the misc/onnxruntime port of
# the FreeBSD and the onnxruntime formula of the Homebrew, while the
# onnxruntime_DIR variable points at a custom installation.
find_package(onnxruntime REQUIRED)

message(STATUS "The ONNX Runtime ${onnxruntime_VERSION} is found")

# Link the onnxruntime::onnxruntime target to your target(s) of interest (e.g.
# the ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} PRIVATE onnxruntime::onnxruntime)
