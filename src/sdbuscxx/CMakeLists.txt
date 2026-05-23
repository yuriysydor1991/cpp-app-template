cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectSDBusCxxControllerObj OBJECT
  SDBusCxxController.cpp
)

target_include_directories(
  TemplateProjectSDBusCxxControllerObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectSDBusCxxControllerObj
  ${SDBUSCPP_LINK_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectSDBusCxxControllerObj
)

add_subdirectory(server-objects)
add_subdirectory(tests)
