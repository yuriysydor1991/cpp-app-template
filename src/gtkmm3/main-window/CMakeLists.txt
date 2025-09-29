cmake_minimum_required(VERSION 3.13)

add_library(
  CppAppTemplateGTKmmMainWindowSubComponentObj OBJECT
  Loader.cpp
)

target_include_directories(
  CppAppTemplateGTKmmMainWindowSubComponentObj
  PUBLIC 
    ${GTKMM_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_directories(
  CppAppTemplateGTKmmMainWindowSubComponentObj
  PUBLIC ${GTKMM_LIBRARY_DIRS}
)

target_link_libraries(
  CppAppTemplateGTKmmMainWindowSubComponentObj
  PUBLIC ${GTKMM_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  CppAppTemplateGTKmmMainWindowSubComponentObj
)
