cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateGtkmm3MainWindowObj OBJECT
  GtkmmWindow.cpp
)

target_include_directories(
  TemplateGtkmm3MainWindowObj 
  PUBLIC 
    ${GTKMM_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateGtkmm3MainWindowObj 
  PUBLIC ${GTKMM_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateGtkmm3MainWindowObj
)
