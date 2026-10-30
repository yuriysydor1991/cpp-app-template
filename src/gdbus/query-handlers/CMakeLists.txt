cmake_minimum_required(VERSION 3.13)

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
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
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
  PRIVATE TemplateProjectGDBusQueryHandlersObj
)

add_subdirectory(tests)
