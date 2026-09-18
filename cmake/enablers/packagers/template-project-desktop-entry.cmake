cmake_minimum_required(VERSION 3.13)

# The freedesktop.org desktop entry and icon of the application, named after
# its reverse DNS id as the flatpak export demands. Every package of a windowed
# application carries them, the AppImage of a console one as well.

if(NOT UNIX OR APPLE)
  return()
endif()

set(
  TEMPLATE_PROJECT_DESKTOP_CATEGORIES
  "Utility;"
  CACHE STRING
  "Semicolon terminated list of the desktop entry categories of the application"
)

set(
  DESKTOP_ICON_SRC
  ${CMAKE_SOURCE_DIR}/misc/packagers/desktop/desktop.icon.svg.in
  CACHE STRING "The SVG icon source file of the application cmake configured"
)

# the desktop starts a console application inside a terminal
if(ENABLE_DESKTOP_APPLICATION)
  set(DESKTOP_ENTRY_TERMINAL false)
else()
  set(DESKTOP_ENTRY_TERMINAL true)
endif()

string(SUBSTRING ${CMAKE_PROJECT_NAME} 0 1 DESKTOP_ICON_LETTER)

set(DESKTOP_ENTRY_FILE ${CMAKE_BINARY_DIR}/${FLATPAK_PROJECT_URL}.desktop)
set(DESKTOP_ICON_FILE ${CMAKE_BINARY_DIR}/${FLATPAK_PROJECT_URL}.svg)

configure_file(${CMAKE_SOURCE_DIR}/misc/packagers/desktop/desktop.entry.in ${DESKTOP_ENTRY_FILE})
configure_file(${DESKTOP_ICON_SRC} ${DESKTOP_ICON_FILE})

if(ENABLE_DESKTOP_APPLICATION OR ENABLE_APPIMAGE OR ENABLE_APPIMAGE_CPACK)
  install(FILES ${DESKTOP_ENTRY_FILE} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
  install(FILES ${DESKTOP_ICON_FILE} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps)
endif()
