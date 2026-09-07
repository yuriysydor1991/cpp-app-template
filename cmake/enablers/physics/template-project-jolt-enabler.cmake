cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_JOLT
    "Enables the Jolt Physics (3D rigid body physics simulation) library for the project usage through system installed one or FetchContent by internet"
    OFF
)

if (NOT ENABLE_JOLT)
    return()
endif()

set(TEMPLATE_APP_JOLT_GIT "https://github.com/jrouwe/JoltPhysics.git" CACHE STRING "The Jolt Physics library git source repository")
set(TEMPLATE_APP_JOLT_GIT_TAG "v5.6.0" CACHE STRING "The Jolt Physics project git repository tag of interest")

# Jolt defaults that break a plain consumer build: the link time optimization
# makes the Jolt objects unlinkable unless the whole project enables LTO too,
# the warnings option treats the Jolt warnings as errors and the Vulkan compute
# backend demands the Vulkan SDK shader compiler the runtime does not ship.
set(INTERPROCEDURAL_OPTIMIZATION OFF CACHE BOOL "Build Jolt with the link time optimizations")
set(ENABLE_ALL_WARNINGS OFF CACHE BOOL "Build Jolt with all the warnings treated as errors")
set(JPH_USE_VK OFF CACHE BOOL "Build the Jolt Vulkan compute backend")

# the Jolt CMake project resides in the repository Build subdirectory
template_project_default_3rdparty_enabler(
  NAME Jolt
  GIT_REPOSITORY ${TEMPLATE_APP_JOLT_GIT}
  GIT_TAG ${TEMPLATE_APP_JOLT_GIT_TAG}
  SOURCE_SUBDIR Build
)

# Link the following Jolt target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   - system install, via find_package(Jolt): Jolt::Jolt
#   - FetchContent source build:              Jolt::Jolt
# For example:
#   target_link_libraries(${PROJECT_BINARY_NAME} Jolt::Jolt)
