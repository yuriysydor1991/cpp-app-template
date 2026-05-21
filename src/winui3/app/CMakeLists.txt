cmake_minimum_required(VERSION 3.13)

# The WinUI 3 application object defines the run_winui_application() launch seam.
# On Windows (with the Windows App SDK available through winui3::sdk) it is the
# real C++/WinRT application; on every other platform it is a small stub so the
# executable still links and runs.
if(WIN32 AND TARGET winui3::sdk)
  add_library(${WINUI3_OBJECT_NAME}App OBJECT WinUI3App.cpp)
  target_link_libraries(${WINUI3_OBJECT_NAME}App PUBLIC winui3::sdk)
else()
  add_library(${WINUI3_OBJECT_NAME}App OBJECT WinUI3AppStub.cpp)
endif()

target_include_directories(
  ${WINUI3_OBJECT_NAME}App
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  ${WINUI3_OBJECT_NAME}App
)
