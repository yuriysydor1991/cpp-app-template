cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_SNAP
  "Set to ON to enable the snap package creation from the project build artifacts"
  OFF
)

if(NOT ENABLE_SNAP)
    return()
endif()

set(TEMPLATE_PROJECT_SNAP_GRADE "devel" CACHE STRING "The snap package grade")
set(TEMPLATE_PROJECT_SNAP_CONFINEMENT "strict" CACHE STRING "The snap package confinement")

# snapcraft installs the part with the DESTDIR set to the part install root, so
# the binary lands under the install prefix of the snap and the command path is
# relative to the snap root
if(IS_ABSOLUTE "${PROJECT_BINARY_INSTALLATION_DIR}")
  set(snapBinaryDir "${PROJECT_BINARY_INSTALLATION_DIR}")
else()
  set(snapBinaryDir "${CMAKE_INSTALL_PREFIX}/${PROJECT_BINARY_INSTALLATION_DIR}")
endif()

file(RELATIVE_PATH SNAP_APP_COMMAND / "${snapBinaryDir}/${PROJECT_BINARY_NAME}")

# a windowed application: its desktop entry and the interfaces of a window
if(ENABLE_DESKTOP_APPLICATION)
  file(
    RELATIVE_PATH snapDesktopFile /
    ${CMAKE_INSTALL_FULL_DATAROOTDIR}/applications/${FLATPAK_PROJECT_URL}.desktop
  )

  set(SNAP_APP_DESKTOP "\n    desktop: ${snapDesktopFile}")
  set(SNAP_APP_DESKTOP_PLUGS "\n      - desktop\n      - desktop-legacy\n      - wayland\n      - x11\n      - opengl")
endif()

configure_file(
  ${PROJECT_SOURCE_DIR}/misc/packagers/snapcraft/snapcraft.yaml.in
  ${CMAKE_CURRENT_BINARY_DIR}/snap/snapcraft.yaml
)

find_program(SNAPCRAFT_EXEC snapcraft)

add_custom_target(
  snap
  COMMAND ${SNAPCRAFT_EXEC} pack
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Packing project with help of the snapcraft"
)
