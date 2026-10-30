cmake_minimum_required(VERSION 3.13)

if(NOT TARGET wx::core OR NOT TARGET wx::base)
  message(
    FATAL_ERROR
    "The wxWidgets GUI of the project needs the wx::core and wx::base targets: "
    "keep the ENABLE_WXWIDGETS option ON"
  )
endif()

# The wxWidgets initialization/orchestration object. It is wxWidgets free (it
# only talks to the run_wx_application() seam), the actual wxWidgets dependent
# code lives in the app and main-window subdirectories.
add_library(
  ${WXWIDGETS_OBJECT_NAME} OBJECT
  WxWidgetsController.cpp
)

target_include_directories(
  ${WXWIDGETS_OBJECT_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE ${WXWIDGETS_OBJECT_NAME}
)

add_subdirectory(helpers)
add_subdirectory(app)
add_subdirectory(main-window)
add_subdirectory(tests)
