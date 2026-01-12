cmake_minimum_required(VERSION 3.16)

add_library(${QT6_OBJECT_NAME}resources STATIC)

qt_add_qml_module(
  ${QT6_OBJECT_NAME}resources
  VERSION ${CMAKE_PROJECT_VERSION}
  NO_PLUGIN
  URI resources
  RESOURCE_PREFIX /${PROJECT_URI}
  RESOURCES
    images/kytok.org.ua-logo.png
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PUBLIC
    ${QT6_OBJECT_NAME}resources
)
