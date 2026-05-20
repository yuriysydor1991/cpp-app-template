cmake_minimum_required(VERSION 3.13)

# The wxWidgets initialization/orchestration object. It is wxWidgets free (it
# only talks to the run_wx_application() seam), the actual wxWidgets dependent
# code lives in the app and main-window subdirectories.
add_library(
  ${WXWIDGETS_OBJECT_NAME} OBJECT
  WxWidgetsIniter.cpp
)

target_include_directories(
  ${WXWIDGETS_OBJECT_NAME}
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  ${WXWIDGETS_OBJECT_NAME}
)

add_subdirectory(helpers)
add_subdirectory(app)
add_subdirectory(main-window)
add_subdirectory(tests)
