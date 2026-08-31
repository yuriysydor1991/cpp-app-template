cmake_minimum_required(VERSION 3.13)

# Picks the AppImage packager implementation the CMake at hand is capable of:
# the CPack AppImage generator arrived with the version below, so an older
# CMake keeps the custom target enabler, which drives the appimagetool on its
# own, and never parses the CPack enabler file. The ENABLE_APPIMAGE_CPACK of a
# user demands the CPack one regardless of the ENABLE_APPIMAGE.

set(APPIMAGE_CPACK_CMAKE_VERSION 4.2)

option(
  ENABLE_APPIMAGE_CPACK
  "Set to ON to enable the AppImage package creation with the CPack generator (demands the CMake ${APPIMAGE_CPACK_CMAKE_VERSION})"
  OFF
)

if(ENABLE_APPIMAGE AND CMAKE_VERSION VERSION_GREATER_EQUAL ${APPIMAGE_CPACK_CMAKE_VERSION})
  set(ENABLE_APPIMAGE_CPACK ON)
endif()

if(ENABLE_APPIMAGE_CPACK)
  message(STATUS "AppImage packager: the CPack generator")
  include(template-project-appimage-cpack-enabler)
else()
  message(STATUS "AppImage packager: the appimagetool custom target")
  include(template-project-appimage-enabler)
endif()
