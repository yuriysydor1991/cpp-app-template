cmake_minimum_required(VERSION 3.13)

# Vulkan is the very purpose of this branch (src/qtvulkan always builds), so
# there is no option to turn it off.
#
# The Vulkan headers and loader are a system component shipped with the platform
# Vulkan SDK / runtime. This branch reaches Vulkan through the native Qt6
# QVulkanInstance / QVulkanFunctions wrappers (Qt6::Gui), but the project sources
# still reference the core Vulkan types (VkInstance, VkPhysicalDevice, ...), so
# the headers have to be on the include path. CMake's canonical FindVulkan
# module exposes the Vulkan::Vulkan imported target carrying the include
# directories (and the loader link library) as usage requirements.
find_package(Vulkan REQUIRED)

set(
  VULKAN_LINK_TARGET
  Vulkan::Vulkan
  CACHE STRING
  "The CMake imported target used to bring in the Vulkan headers and loader"
)
