cmake_minimum_required(VERSION 3.13)

add_library(${QT6_OBJECT_NAME}main STATIC)

qt_add_qml_module(
  ${QT6_OBJECT_NAME}main
  VERSION ${CMAKE_PROJECT_VERSION} 
  NO_PLUGIN
  URI main
  RESOURCE_PREFIX /${PROJECT_URI}
  OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/main
  QML_FILES
      main.qml
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PUBLIC
    ${QT6_OBJECT_NAME}main
)

add_subdirectory(components)
