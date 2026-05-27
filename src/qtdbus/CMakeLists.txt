cmake_minimum_required(VERSION 3.16)

add_library(
  TemplateProjectQtDBusControllerObj OBJECT
  QtDBusController.cpp
  SystemInformation.cpp
)

target_include_directories(
  TemplateProjectQtDBusControllerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectQtDBusControllerObj
  PUBLIC
    Qt6::Core
    Qt6::DBus
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PUBLIC
    TemplateProjectQtDBusControllerObj
)

add_subdirectory(query-handlers)
add_subdirectory(tests)
