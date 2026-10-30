cmake_minimum_required(VERSION 3.13)

# WinUI 3 (Windows App SDK) + Direct3D 11 GPU rendering canvas. Only added on
# Windows (guarded by the parent CMakeLists), so it always links winui3::sdk;
# d3d11/dxgi are the Windows SDK Direct3D import libraries.
add_library(
  ${WINUI3_OBJECT_NAME}GLArea OBJECT
  GLTriangleArea.cpp
  RenderState.cpp
)

target_include_directories(
  ${WINUI3_OBJECT_NAME}GLArea
  PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  ${WINUI3_OBJECT_NAME}GLArea
  PUBLIC
    winui3::sdk
    d3d11
    dxgi
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE ${WINUI3_OBJECT_NAME}GLArea
)
