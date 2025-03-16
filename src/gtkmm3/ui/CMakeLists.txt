cmake_minimum_required(VERSION 3.13)

include(template-project-load-file-into-h)

load_file_data(
  ${CMAKE_CURRENT_SOURCE_DIR}/GtkmmWindow.glade
  MAINWINDOW_GLADE_DATA_SIZE 
  MAINWINDOW_GLADE_DATA
  true
)

configure_file(
  GtkmmWindow_glade.h.in
  ${CMAKE_BINARY_DIR}/GtkmmWindow_glade.h
)

add_subdirectory(resources)
