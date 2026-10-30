cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectVulkanDeviceInfoObj OBJECT
  PhysicalDeviceInfoHandler.cpp
  DeviceInfoHandlerFactory.cpp
)

target_include_directories(
  TemplateProjectVulkanDeviceInfoObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectVulkanDeviceInfoObj
  PUBLIC ${VULKAN_LINK_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectVulkanDeviceInfoObj
)

add_subdirectory(tests)
