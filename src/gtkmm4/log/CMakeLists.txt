cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateGtkmm4LogObj OBJECT
  GtkLogBridge.cpp
)

target_include_directories(
  TemplateGtkmm4LogObj
  SYSTEM PUBLIC
    ${GTKMM_INCLUDE_DIRS}
)

target_include_directories(
  TemplateGtkmm4LogObj
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_directories(
  TemplateGtkmm4LogObj
  PUBLIC ${GTKMM_LIBRARY_DIRS}
)

target_link_libraries(
  TemplateGtkmm4LogObj
  PUBLIC ${GTKMM_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateGtkmm4LogObj
)

add_subdirectory(tests)
