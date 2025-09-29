cmake_minimum_required(VERSION 3.13)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0 REQUIRED)

set(
  GTKMM_APP_RESOURCES_PREFIX 
  "/ua/org/kytok/template/gtkmm3/glade"
  CACHE STRING 
  "The project's GTKmm resources root path"
)

add_compile_definitions(GTKMM_APP_RESOURCES_PREFIX=\"${GTKMM_APP_RESOURCES_PREFIX}\")

add_library(
  ${GTKMM_OBJECT_NAME} OBJECT
  GtkmmIniter.cpp
)

target_include_directories(
  ${GTKMM_OBJECT_NAME}
  PUBLIC 
    ${GTKMM_INCLUDE_DIRS}
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
  ${GTKMM_OBJECT_NAME}
)

add_subdirectory(ui)
add_subdirectory(main-window)
