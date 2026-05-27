cmake_minimum_required(VERSION 3.16)

add_library(
  TemplateProjectQtDBusQueryHandlersObj OBJECT
  Hostname1QueryHandler.cpp
  DBusQueryHandlerFactory.cpp
)

target_include_directories(
  TemplateProjectQtDBusQueryHandlersObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectQtDBusQueryHandlersObj
  PUBLIC
    Qt6::Core
    Qt6::DBus
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PUBLIC
    TemplateProjectQtDBusQueryHandlersObj
)

add_subdirectory(tests)
