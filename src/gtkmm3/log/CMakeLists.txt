cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateGtkmm3LogObj OBJECT
  GtkLogBridge.cpp
)

target_include_directories(
  TemplateGtkmm3LogObj
  PUBLIC
    ${GTKMM_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_directories(
  TemplateGtkmm3LogObj
  PUBLIC ${GTKMM_LIBRARY_DIRS}
)

target_link_libraries(
  TemplateGtkmm3LogObj
  PUBLIC ${GTKMM_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateGtkmm3LogObj
)

add_subdirectory(tests)
