cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateGtkmm4MainWindowObj OBJECT
  GtkmmWindow.cpp
)

target_include_directories(
  TemplateGtkmm4MainWindowObj 
  PUBLIC 
    ${GTKMM_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateGtkmm4MainWindowObj 
  PUBLIC ${GTKMM_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateGtkmm4MainWindowObj
)
