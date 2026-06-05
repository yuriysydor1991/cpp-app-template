cmake_minimum_required(VERSION 3.16)

add_library(
  TemplateProjectQtVulkanDeviceInfoObj OBJECT
  PhysicalDeviceInfoHandler.cpp
  DeviceInfoHandlerFactory.cpp
)

target_include_directories(
  TemplateProjectQtVulkanDeviceInfoObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectQtVulkanDeviceInfoObj
  PUBLIC
    Qt6::Core
    Qt6::Gui
    ${VULKAN_LINK_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PUBLIC
    TemplateProjectQtVulkanDeviceInfoObj
)

add_subdirectory(tests)
