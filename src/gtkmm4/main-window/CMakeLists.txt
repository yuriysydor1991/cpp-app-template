cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateGtkmm4MainWindowObj OBJECT
  AdwaitaWindow.cpp
)

target_include_directories(
  TemplateGtkmm4MainWindowObj 
  PUBLIC 
    ${GTKMM_INCLUDE_DIRS}
    ${ADWAITA_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_directories(
  TemplateGtkmm4MainWindowObj
  PUBLIC ${ADWAITA_LIBRARY_DIRS}
)

target_link_libraries(
  TemplateGtkmm4MainWindowObj 
  PUBLIC ${GTKMM_LIBRARIES} ${ADWAITA_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateGtkmm4MainWindowObj
)

add_subdirectory(tests)
