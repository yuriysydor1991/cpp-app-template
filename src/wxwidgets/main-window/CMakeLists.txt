cmake_minimum_required(VERSION 3.13)

# wxWidgets dependent main window object.
add_library(
  ${WXWIDGETS_OBJECT_NAME}MainWindow OBJECT
  WxMainFrame.cpp
)

target_include_directories(
  ${WXWIDGETS_OBJECT_NAME}MainWindow
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${WXWIDGETS_OBJECT_NAME}MainWindow
  PUBLIC wx::core wx::base
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  ${WXWIDGETS_OBJECT_NAME}MainWindow
)
