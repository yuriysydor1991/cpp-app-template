cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_PLPLOT
  "Set to ON to enable the PLplot integration (by using system wide available or through the Internet)"
  ON
)

if (NOT ENABLE_PLPLOT)
  return()
endif()

set(TEMPLATE_APP_PLPLOT_GIT "https://git.code.sf.net/p/plplot/plplot" CACHE STRING "The PLplot library git source repository")
set(TEMPLATE_APP_PLPLOT_GIT_TAG "master" CACHE STRING "The PLplot project git repository tag of interest")

# The PLplot modules resolve their own sources through the ${CMAKE_SOURCE_DIR}
# so the library is built standalone instead of being added as a subdirectory.
# The gnu17 C dialect keeps its pre-C23 configuration checks compilable and the
# PLPLOT_USE_QT5 keeps the installed plplotConfig.cmake valid when no Qt device
# is built. Only the C++ and the Qt bindings are required, the last one for the
# qtwidget device and it is dropped by the PLplot itself when no Qt5 is found.
# The installed plplotConfig.cmake forwards the plplot_FIND_QUIETLY and the
# plplot_FIND_REQUIRED values into its own find_package() calls, so no flag is
# passed to the search of it.
template_project_default_3rdparty_enabler(
  NAME plplot
  NO_FIND_PACKAGE_FLAGS
  GIT_REPOSITORY ${TEMPLATE_APP_PLPLOT_GIT}
  GIT_TAG ${TEMPLATE_APP_PLPLOT_GIT_TAG}
  COMPONENTS CXX
  STANDALONE_BUILD
  CMAKE_ARGS
    -DCMAKE_C_FLAGS=-std=gnu17
    -DPLPLOT_USE_QT5=ON
    -DDEFAULT_NO_BINDINGS=ON
    -DENABLE_cxx=ON
    -DENABLE_qt=ON
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PLPLOT::plplot
  PLPLOT::plplotcxx
)

# The controller compiles the PLplot headers itself while the enablers are
# included after the src subdirectory targets are declared.
target_link_libraries(
  TemplateProjectPLPlotControllerObj
  PLPLOT::plplotcxx
)

# A system wide installed PLplot exports no include directory and is reached
# through the default /usr/include one, while the standalone built library
# exports its own headers directory whose parent provides the plplot/ prefix.
get_target_property(PLPLOT_INCLUDE_DIR PLPLOT::plplotcxx INTERFACE_INCLUDE_DIRECTORIES)

if (PLPLOT_INCLUDE_DIR)
  get_filename_component(PLPLOT_INCLUDE_ROOT ${PLPLOT_INCLUDE_DIR} DIRECTORY)

  target_include_directories(
    TemplateProjectPLPlotControllerObj
    PUBLIC ${PLPLOT_INCLUDE_ROOT}
  )
endif()
