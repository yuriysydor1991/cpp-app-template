cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_LIBADWAITA
  "Enables the libadwaita for the project (no FetchContent available)"
  ON
)

if(NOT ENABLE_LIBADWAITA)
  return()
endif()

find_package(PkgConfig)

# libadwaita is a GTK4 C library without an official C++ binding, so it is
# consumed through its C API next to the gtkmm-4.0 one. Both wrap the very same
# GObject instances, which is what makes Glib::wrap usable on the widgets the
# AdwaitaWindow creates.
pkg_check_modules(ADWAITA libadwaita-1 REQUIRED)
