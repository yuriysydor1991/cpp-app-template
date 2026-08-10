cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectOAIControllerObj OBJECT
  OAIController.cpp
)

target_include_directories(
  TemplateProjectOAIControllerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectOAIControllerObj
  PRIVATE oai::oai
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectOAIControllerObj
  oai::oai
)
