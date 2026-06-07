cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectVulkanDmabufObj OBJECT
  VulkanDmabufRenderer.cpp
)

target_include_directories(
  TemplateProjectVulkanDmabufObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectVulkanDmabufObj
  PUBLIC ${VULKAN_LINK_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectVulkanDmabufObj
)
