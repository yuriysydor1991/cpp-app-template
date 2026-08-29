cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_library(
  ${PROJECT_LIBRARY_NAME}
  SHARED
)

# The public headers are written by hand and used as they are. The logging
# interface the public LibraryFacade.h accepts is one of them, so the single
# facade/public directory is the whole installable surface.
target_include_directories(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/facade/public>
    # Both the plain include root and the versioned sub-directory are exported,
    # so a consumer may write either
    #   #include <CppAppTemplate-0.12/LibraryFacade.h>  (recommended)
    # or the short
    #   #include <LibraryFacade.h>
    # The prefixed form is the safe one: every library derived from this
    # template installs a LibraryFacade.h of its own, and names like ILib.h are
    # generic enough to collide in a busy include path.
    $<INSTALL_INTERFACE:include>
    $<INSTALL_INTERFACE:include/${PROJECT_LIBRARY_NAME}>
)

# The whole logging implementation is a part of the library itself. Without it
# the installed library carries unresolved default logger symbols and can not
# be linked by the application which uses it. The objects are taken directly
# instead of being linked, so the internal logger targets stay out of the
# installed library export set.
target_sources(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE
    $<TARGET_OBJECTS:TemplateProjectDefaultLoggerObj>
    $<TARGET_OBJECTS:TemplateProjectRealDefaultLoggerObj>
)

set_target_properties(
  ${PROJECT_LIBRARY_NAME}
  PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  # Only the TEMPLATE_LIB_API marked interface of facade/public leaves the
  # shared object. That is a correctness requirement and not a size
  # optimisation: every library derived from this template carries the very
  # same lib0impl, default_logger and project_decls names, and an application
  # which loads two of them would otherwise let the dynamic linker bind the
  # calls of one library into the definitions of the other.
  CXX_VISIBILITY_PRESET hidden
)

# Turns the TEMPLATE_LIB_API macro of the public headers into the export half
# of the __declspec pair while the library itself is being compiled. Nothing
# outside of this build ever defines it, so a consumer of the installed headers
# gets the import half.
target_compile_definitions(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE TEMPLATE_LIB_BUILDING=1
)

if(LIB_INSTALL_DEV_FILES)
  install(
    TARGETS ${PROJECT_LIBRARY_NAME}
    LIBRARY
      DESTINATION lib
      COMPONENT Runtime
      NAMELINK_COMPONENT Development
  )
else()
  # NAMELINK_SKIP drops the unversioned lib<name>.so symlink, which only a
  # linker looking for -l<name> needs. The versioned SONAME file the loader
  # resolves at run time is still installed.
  install(
    TARGETS ${PROJECT_LIBRARY_NAME}
    LIBRARY
      DESTINATION lib
      COMPONENT Runtime
      NAMELINK_SKIP
  )
endif()

add_subdirectory(facade)
add_subdirectory(libmain)
add_subdirectory(tests)

# Generates and installs the CMake package integration files, so it is a
# development files producer as a whole. The library binary itself is installed
# by the rule above and stays unaffected.
if(LIB_INSTALL_DEV_FILES)
  include(lib-cmake-module-gen)
endif()

