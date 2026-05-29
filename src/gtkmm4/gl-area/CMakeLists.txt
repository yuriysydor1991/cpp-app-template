cmake_minimum_required(VERSION 3.13)

# Gtk::GLArea draws with raw OpenGL calls dispatched through libepoxy
# (the same GL loader GTK itself uses).
find_package(PkgConfig REQUIRED)
pkg_check_modules(EPOXY REQUIRED epoxy)

add_library(
  TemplateGtkmm4GLAreaObj OBJECT
  GLTriangleArea.cpp
)

target_include_directories(
  TemplateGtkmm4GLAreaObj
  PUBLIC
    ${GTKMM_INCLUDE_DIRS}
    ${EPOXY_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_directories(
  TemplateGtkmm4GLAreaObj
  PUBLIC
    ${GTKMM_LIBRARY_DIRS}
    ${EPOXY_LIBRARY_DIRS}
)

target_link_libraries(
  TemplateGtkmm4GLAreaObj
  PUBLIC
    ${GTKMM_LIBRARIES}
    ${EPOXY_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateGtkmm4GLAreaObj
)
