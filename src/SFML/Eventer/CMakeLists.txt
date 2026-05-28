cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateSFMLEventsObj OBJECT
  EventsController.cpp
)

target_include_directories(
  TemplateSFMLEventsObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateSFMLEventsObj
  PRIVATE
  sfml-graphics
  sfml-window
  sfml-system
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateSFMLEventsObj
)

add_subdirectory(EventsHandlers)
