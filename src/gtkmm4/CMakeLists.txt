cmake_minimum_required(VERSION 3.13)

add_library(
  ${GTKMM_OBJECT_NAME} OBJECT
  Gtkmm4Controller.cpp
)

target_include_directories(
  ${GTKMM_OBJECT_NAME}
  SYSTEM PUBLIC
    ${GTKMM_INCLUDE_DIRS}
)

target_include_directories(
  ${GTKMM_OBJECT_NAME}
  PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_directories(
  ${GTKMM_OBJECT_NAME}
  PUBLIC ${GTKMM_LIBRARY_DIRS}
)

target_link_libraries(
  ${GTKMM_OBJECT_NAME}
  PUBLIC ${GTKMM_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE ${GTKMM_OBJECT_NAME}
)

add_subdirectory(log)
