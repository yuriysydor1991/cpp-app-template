cmake_minimum_required(VERSION 3.16)

add_library(
  TemplateProjectGDBusQueryHandlersObj OBJECT
  Hostname1QueryHandler.cpp
  DBusQueryHandlerFactory.cpp
)

target_include_directories(
  TemplateProjectGDBusQueryHandlersObj
  SYSTEM PUBLIC
    ${GTKMM_INCLUDE_DIRS}
)

target_include_directories(
  TemplateProjectGDBusQueryHandlersObj
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_directories(
  TemplateProjectGDBusQueryHandlersObj
  PUBLIC ${GTKMM_LIBRARY_DIRS}
)

target_link_libraries(
  TemplateProjectGDBusQueryHandlersObj
  PUBLIC ${GTKMM_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectGDBusQueryHandlersObj
)

add_subdirectory(tests)
