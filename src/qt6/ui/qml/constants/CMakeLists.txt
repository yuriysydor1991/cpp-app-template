cmake_minimum_required(VERSION 3.16)

add_library(${QT6_OBJECT_NAME}constants STATIC)

set_source_files_properties(Constants.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(
  ${QT6_OBJECT_NAME}constants
  VERSION ${CMAKE_PROJECT_VERSION} 
  NO_PLUGIN
  URI constants
  RESOURCE_PREFIX /${PROJECT_URI}
  QML_FILES
    Constants.qml
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PUBLIC
    ${QT6_OBJECT_NAME}constants
)
