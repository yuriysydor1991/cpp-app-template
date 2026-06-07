cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_VULKAN
  "Enables the Vulkan API for the project (system loader, no FetchContent available)"
  ON
)

if(NOT ENABLE_VULKAN)
  return()
endif()

# The Vulkan loader (libvulkan) and headers are a system component shipped with
# the platform Vulkan SDK / runtime. CMake provides a canonical FindVulkan
# module that exposes the Vulkan::Vulkan imported target carrying both the
# include directories and the loader link library as usage requirements.
find_package(Vulkan REQUIRED)

set(
  VULKAN_LINK_TARGET
  Vulkan::Vulkan
  CACHE STRING
  "The CMake imported target used to link against the Vulkan loader"
)
