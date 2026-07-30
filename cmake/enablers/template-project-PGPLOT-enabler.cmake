cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_PGPLOT
  "Set to ON to enable the PGPLOT integration (system wide installation only)"
  ON
)

if (NOT ENABLE_PGPLOT)
  return()
endif()

# The PGPLOT library is built by it's own makemake driven Fortran/C build
# system and provides neither a CMake package config nor a CMake buildable
# source tree, so there is nothing to make available through the Internet by
# the template_project_default_3rdparty_enabler and the library is probed from
# the system exclusively. Install the pgplot5-dev (Debian/Ubuntu),
# pgplot-devel (Fedora/openSUSE) package with the original PGPLOT library or
# the giza-dev (Debian/Ubuntu), giza-devel (Fedora) one with it's free
# drop-in cpgplot/PGPLOT replacement. Consult the
# doc/sections/en_US/3-requirements/3-11-required-pgplot-packages.md file for
# the details.

set(
  TEMPLATE_APP_PGPLOT_ROOT
  ""
  CACHE PATH
  "An optional PGPLOT (or giza) installation prefix to probe before the system wide directories"
)

find_path(
  PGPLOT_INCLUDE_DIR
  NAMES cpgplot.h
  HINTS ${TEMPLATE_APP_PGPLOT_ROOT}
  PATH_SUFFIXES include include/pgplot include/giza
)

# the C (cpgplot) binding of the library which is the one used by the
# src/pgplot/PGPLOTController.cpp implementation
find_library(
  PGPLOT_CPGPLOT_LIBRARY
  NAMES cpgplot
  HINTS ${TEMPLATE_APP_PGPLOT_ROOT}
  PATH_SUFFIXES lib lib64 lib/${CMAKE_LIBRARY_ARCHITECTURE}
)

# the underlying (Fortran) PGPLOT library itself, required explicitly by the
# static builds of the C binding above
find_library(
  PGPLOT_LIBRARY
  NAMES pgplot
  HINTS ${TEMPLATE_APP_PGPLOT_ROOT}
  PATH_SUFFIXES lib lib64 lib/${CMAKE_LIBRARY_ARCHITECTURE}
)

mark_as_advanced(PGPLOT_INCLUDE_DIR PGPLOT_CPGPLOT_LIBRARY PGPLOT_LIBRARY)

if (NOT PGPLOT_INCLUDE_DIR OR NOT PGPLOT_CPGPLOT_LIBRARY)
  message(
    FATAL_ERROR
    "No PGPLOT development files (the cpgplot.h header and the cpgplot library) "
    "found in the system. Install the pgplot5-dev or the giza-dev package, "
    "point the TEMPLATE_APP_PGPLOT_ROOT variable to a custom PGPLOT installation "
    "prefix or reconfigure with the -DENABLE_PGPLOT=OFF to disable the integration."
  )
endif()

set(PGPLOT_LIBRARIES ${PGPLOT_CPGPLOT_LIBRARY})

if (PGPLOT_LIBRARY)
  list(APPEND PGPLOT_LIBRARIES ${PGPLOT_LIBRARY})
endif()

message(STATUS "PGPLOT include directory: ${PGPLOT_INCLUDE_DIR}")
message(STATUS "PGPLOT libraries: ${PGPLOT_LIBRARIES}")

# Link the following PGPLOT target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries), just like
# the src/pgplot/CMakeLists.txt does:
#   target_link_libraries(${PROJECT_BINARY_NAME} PGPLOT::cpgplot)
if (NOT TARGET PGPLOT::cpgplot)
  add_library(PGPLOT::cpgplot INTERFACE IMPORTED GLOBAL)

  set_target_properties(
    PGPLOT::cpgplot PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${PGPLOT_INCLUDE_DIR}"
    INTERFACE_LINK_LIBRARIES "${PGPLOT_LIBRARIES}"
  )
endif()
