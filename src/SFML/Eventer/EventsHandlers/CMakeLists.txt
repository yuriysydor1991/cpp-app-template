cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateSFMLEventsHandlersObj OBJECT
  EventClosedHandler.cpp
  EventsHandlersFactory.cpp
)

target_include_directories(
  TemplateSFMLEventsHandlersObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateSFMLEventsHandlersObj
  PRIVATE
  sfml-graphics
  sfml-window
  sfml-system
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateSFMLEventsHandlersObj
)
