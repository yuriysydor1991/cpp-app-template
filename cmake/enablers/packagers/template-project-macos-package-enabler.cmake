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

# the CPUs the bundle is built for (arm64-x86_64 for a universal one), the host
# one by default
if(CMAKE_OSX_ARCHITECTURES)
  string(REPLACE ";" "-" macosArchitecture "${CMAKE_OSX_ARCHITECTURES}")
else()
  set(macosArchitecture ${CMAKE_SYSTEM_PROCESSOR})
endif()

# the oldest macOS release the bundle runs on (the deployment target, else the
# build host release), so the packages of the different releases differ in name
if(CMAKE_OSX_DEPLOYMENT_TARGET)
  set(macosVersion ${CMAKE_OSX_DEPLOYMENT_TARGET})
else()
  execute_process(
    COMMAND sw_vers -productVersion
    OUTPUT_VARIABLE macosVersion
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  string(REGEX MATCH "^[0-9]+(\\.[0-9]+)?" macosVersion "${macosVersion}")
endif()

set(
  TEMPLATE_PROJECT_PACKAGE_OS
  macos-${macosVersion}
  CACHE STRING
  "The destination OS of the package file names (e.g. macos-15.1)"
)

# the CPACK_SYSTEM_NAME of the default file name names the system alone, so the
# destination CPU and OS take its place
set(
  CPACK_PACKAGE_FILE_NAME
  ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${macosArchitecture}-${TEMPLATE_PROJECT_PACKAGE_OS}
)

include(CPack)
