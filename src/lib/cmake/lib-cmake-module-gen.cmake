include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# The library target joins the export set in its own install rule, see the
# src/lib/CMakeLists.txt. Every file below is a development one.
set(LIB_CMAKE_PACKAGE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_LIBRARY_NAME})
set(PROJECT_MODULE_TARGETS_FILE "${PROJECT_LIBRARY_NAME}Targets.cmake")

install(
  EXPORT ${PROJECT_LIBRARY_NAME}
  FILE ${PROJECT_MODULE_TARGETS_FILE}
  NAMESPACE ${PROJECT_LIBRARY_NAME}::
  DESTINATION ${LIB_CMAKE_PACKAGE_DIR}
  COMPONENT Development
)

# The find_package looks for the <name>ConfigVersion.cmake beside the
# <name>Config.cmake. The public namespace carries the major and the minor
# version (CppAppTemplate012), so only the same minor version is compatible.
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIBRARY_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMinorVersion
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/TemplateLibraryConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIBRARY_NAME}Config.cmake"
  INSTALL_DESTINATION ${LIB_CMAKE_PACKAGE_DIR}
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIBRARY_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_LIBRARY_NAME}ConfigVersion.cmake"
  DESTINATION ${LIB_CMAKE_PACKAGE_DIR}
  COMPONENT Development
)
