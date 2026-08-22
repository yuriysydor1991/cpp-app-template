cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_library(
  ${PROJECT_LIBRARY_NAME}
  SHARED
)

# The public headers carry the project unique library namespace, so they are
# generated into the PROJECT_LIB_PUBLIC_INCLUDE_DIR declared by the
# template-project-misc-variables-declare module instead of being used as is.
# See the facade subdirectory.
target_include_directories(
  ${PROJECT_LIBRARY_NAME}
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
  PRIVATE ${PROJECT_LIB_PUBLIC_INCLUDE_DIR}/${PROJECT_LIBRARY_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_LIB_PUBLIC_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
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

