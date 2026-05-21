cmake_minimum_required(VERSION 3.13)

# WinUI 3 (Windows App SDK) dependent main window object. Only added on Windows
# (guarded by the parent CMakeLists), so it always links against winui3::sdk.
add_library(
  ${WINUI3_OBJECT_NAME}MainWindow OBJECT
  WinUI3MainWindow.cpp
)

target_include_directories(
  ${WINUI3_OBJECT_NAME}MainWindow
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${WINUI3_OBJECT_NAME}MainWindow
  PUBLIC winui3::sdk
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  ${WINUI3_OBJECT_NAME}MainWindow
)
