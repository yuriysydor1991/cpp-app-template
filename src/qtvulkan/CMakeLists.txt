cmake_minimum_required(VERSION 3.16)

add_library(
  TemplateProjectQtVulkanControllerObj OBJECT
  QtVulkanController.cpp
)

target_include_directories(
  TemplateProjectQtVulkanControllerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectQtVulkanControllerObj
  PUBLIC
    Qt6::Core
    Qt6::Gui
    ${VULKAN_LINK_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PUBLIC
    TemplateProjectQtVulkanControllerObj
)

add_subdirectory(device-info)
add_subdirectory(tests)
