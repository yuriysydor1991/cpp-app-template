cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_GTKMM4
  "Enables the gtkmm4 for the project (no FetchContent available)"
  ON
)

if(NOT ENABLE_GTKMM4)
  return()
endif()

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-4.0 REQUIRED)

string(REPLACE  "." "/" GTKMM_APP_RESOURCES_PREFIX_COMPUTED "/${PROJECT_REVERSE_URL}")

set(
  GTKMM_APP_RESOURCES_PREFIX
  "${GTKMM_APP_RESOURCES_PREFIX_COMPUTED}"
  CACHE STRING 
  "The project's GTKmm4 resources root path"
)

add_compile_definitions(GTKMM_APP_RESOURCES_PREFIX=\"${GTKMM_APP_RESOURCES_PREFIX}\")
