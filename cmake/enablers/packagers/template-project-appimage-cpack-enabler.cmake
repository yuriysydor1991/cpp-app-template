# The CPack AppImage generator is available since the CMake 4.2, so the
# template-project-feature-enabler includes this file on the user demand alone.
cmake_minimum_required(VERSION 4.2)

include(InstallRequiredSystemLibraries)

set(
  TEMPLATE_PROJECT_APPIMAGE_CATEGORIES
  "Utility;"
  CACHE STRING
  "Semicolon terminated list of the desktop entry categories of the AppImage"
)

set(
  TEMPLATE_PROJECT_APPIMAGE_TERMINAL
  "true"
  CACHE STRING
  "Set to false when the packaged binary is a windowed application which needs no terminal"
)

set(
  APPIMAGE_ICON_SRC
  ${CMAKE_SOURCE_DIR}/misc/packagers/appimage.icon.svg.in
  CACHE STRING "The AppImage SVG icon source file cmake configured"
)

set(appimageDesktopDst ${CMAKE_BINARY_DIR}/${PROJECT_BINARY_NAME}.desktop)
set(appimageIconDst ${CMAKE_BINARY_DIR}/${PROJECT_BINARY_NAME}.svg)

string(SUBSTRING ${CMAKE_PROJECT_NAME} 0 1 APPIMAGE_ICON_LETTER)

configure_file(${CMAKE_SOURCE_DIR}/misc/packagers/appimage.desktop.in ${appimageDesktopDst})
configure_file(${APPIMAGE_ICON_SRC} ${appimageIconDst})

# the generator demands the desktop entry and the icon it names inside the
# install tree, at the locations of the freedesktop.org specification
install(FILES ${appimageDesktopDst} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
install(FILES ${appimageIconDst} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps)

set(CPACK_GENERATOR "AppImage")
set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT ${PROJECT_MAINTAINER_EMAIL})
set(CPACK_PACKAGE_VENDOR "${PROJECT_MAINTAINER}")
set(CPACK_PACKAGE_DESCRIPTION ${CMAKE_PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${CMAKE_PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_ICON ${PROJECT_BINARY_NAME}.svg)

set(CPACK_APPIMAGE_DESKTOP_FILE ${PROJECT_BINARY_NAME}.desktop)

include(CPack)
