cmake_minimum_required(VERSION 3.13)

# wxWidgets dependent application object (defines the wxApp and the wxEntry
# based run_wx_application() launch seam).
add_library(
  ${WXWIDGETS_OBJECT_NAME}App OBJECT
  WxApp.cpp
  StopFlagWatcher.cpp
)

target_include_directories(
  ${WXWIDGETS_OBJECT_NAME}App
  PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  ${WXWIDGETS_OBJECT_NAME}App
  PUBLIC wx::core wx::base
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE ${WXWIDGETS_OBJECT_NAME}App
)
