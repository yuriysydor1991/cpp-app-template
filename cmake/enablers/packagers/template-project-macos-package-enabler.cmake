cmake_minimum_required(VERSION 3.13)

# macOS redistribution packaging via CPack: a drag-to-Applications disk image
# (DragNDrop / .dmg) and a guided installer (productbuild / .pkg). The main
# executable is produced as a .app bundle (set in src/CMakeLists.txt on Apple).

option(
  ENABLE_MACOS_PACKAGE
  "Set to ON to enable the macOS .dmg (DragNDrop) and .pkg (productbuild) package generation"
  OFF
)

if(NOT ENABLE_MACOS_PACKAGE)
  return()
endif()

if(NOT APPLE)
  message(STATUS "macOS packaging (DragNDrop/.dmg, productbuild/.pkg) is only available on macOS")
  return()
endif()

include(InstallRequiredSystemLibraries)

set(
  TEMPLATE_PROJECT_MACOS_BUNDLE_IDENTIFIER
  "ua.org.kytok.template.${PROJECT_BINARY_NAME_lower}"
  CACHE STRING
  "Reverse-DNS bundle identifier used by the macOS .app and the .pkg installer"
)

set(CPACK_GENERATOR "DragNDrop;productbuild")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR "${PROJECT_MAINTAINER}")
set(CPACK_PACKAGE_CONTACT ${PROJECT_MAINTAINER_EMAIL})
set(CPACK_PACKAGE_DESCRIPTION ${CMAKE_PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${CMAKE_PROJECT_DESCRIPTION})

# DragNDrop (.dmg)
set(CPACK_DMG_VOLUME_NAME "${PROJECT_NAME}")

# productbuild (.pkg) - set a "Developer ID Installer" identity to sign the
# package for distribution outside the Mac App Store.
set(CPACK_PRODUCTBUILD_IDENTIFIER "${TEMPLATE_PROJECT_MACOS_BUNDLE_IDENTIFIER}")
set(
  TEMPLATE_PROJECT_PRODUCTBUILD_IDENTITY
  ""
  CACHE STRING
  "Optional 'Developer ID Installer' identity used to sign the .pkg (empty = unsigned)"
)
if(TEMPLATE_PROJECT_PRODUCTBUILD_IDENTITY)
  set(CPACK_PRODUCTBUILD_IDENTITY_NAME "${TEMPLATE_PROJECT_PRODUCTBUILD_IDENTITY}")
endif()

include(CPack)
