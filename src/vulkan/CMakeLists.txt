cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectVulkanControllerObj OBJECT
  VulkanController.cpp
)

target_include_directories(
  TemplateProjectVulkanControllerObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectVulkanControllerObj
  PUBLIC ${VULKAN_LINK_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectVulkanControllerObj
)

add_subdirectory(device-info)
add_subdirectory(dmabuf)
add_subdirectory(tests)
