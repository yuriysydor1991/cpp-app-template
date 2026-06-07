cmake_minimum_required(VERSION 3.16)

add_library(
  TemplateProjectQtVulkanWindowObj OBJECT
  BlankVulkanWindow.cpp
  BlankVulkanRenderer.cpp
)

target_include_directories(
  TemplateProjectQtVulkanWindowObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectQtVulkanWindowObj
  PUBLIC
    Qt6::Core
    Qt6::Gui
    ${VULKAN_LINK_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PUBLIC
    TemplateProjectQtVulkanWindowObj
)
