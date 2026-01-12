cmake_minimum_required(VERSION 3.16)

add_library(${QT6_OBJECT_NAME}components STATIC)

qt_add_qml_module(
  ${QT6_OBJECT_NAME}components
  VERSION ${CMAKE_PROJECT_VERSION} 
  NO_PLUGIN
  URI components
  RESOURCE_PREFIX /${PROJECT_URI}
  QML_FILES
      DefaultWelcome.qml
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PUBLIC
    ${QT6_OBJECT_NAME}components
)
