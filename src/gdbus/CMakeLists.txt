cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectGDBusControllerObj OBJECT
  GDBusController.cpp
)

target_include_directories(
  TemplateProjectGDBusControllerObj
  SYSTEM PUBLIC
    ${GTKMM_INCLUDE_DIRS}
)

target_include_directories(
  TemplateProjectGDBusControllerObj
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_directories(
  TemplateProjectGDBusControllerObj
  PUBLIC ${GTKMM_LIBRARY_DIRS}
)

target_link_libraries(
  TemplateProjectGDBusControllerObj
  PUBLIC ${GTKMM_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectGDBusControllerObj
)

add_subdirectory(query-handlers)
add_subdirectory(tests)
