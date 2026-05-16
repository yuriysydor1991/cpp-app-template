cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_GTKMM3
  "Enables the gtkmm3 for the project (no FetchContent available)"
  ON
)

if(NOT ENABLE_GTKMM3)
  return()
endif()

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0 REQUIRED IMPORTED_TARGET gtkmm-3.0)

string(REPLACE  "." "/" GTKMM_APP_RESOURCES_PREFIX_COMPUTED "/${PROJECT_URI}")

set(
  GTKMM_APP_RESOURCES_PREFIX
  "${GTKMM_APP_RESOURCES_PREFIX_COMPUTED}"
  CACHE STRING 
  "The project's GTKmm resources root path"
)

add_compile_definitions(GTKMM_APP_RESOURCES_PREFIX=\"${GTKMM_APP_RESOURCES_PREFIX}\")
