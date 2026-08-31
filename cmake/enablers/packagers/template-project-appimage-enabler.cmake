cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_APPIMAGE
  "Set to ON to enable the AppImage package creation from the project build artifacts"
  OFF
)

if(NOT ENABLE_APPIMAGE)
  return()
endif()

find_program(APPIMAGETOOL_EXEC appimagetool REQUIRED)

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

set(APPIMAGE_TARGET_ARCH ${CMAKE_SYSTEM_PROCESSOR})
set(APPIMAGE_APPDIR ${CMAKE_BINARY_DIR}/AppDir)
set(APPIMAGE_DST_NAME ${PROJECT_BINARY_NAME}-${CMAKE_PROJECT_VERSION}-${APPIMAGE_TARGET_ARCH}.AppImage)

string(SUBSTRING ${CMAKE_PROJECT_NAME} 0 1 APPIMAGE_ICON_LETTER)

configure_file(
  ${CMAKE_SOURCE_DIR}/misc/packagers/appimage.desktop.in
  ${APPIMAGE_APPDIR}/${PROJECT_BINARY_NAME}.desktop
)

configure_file(${APPIMAGE_ICON_SRC} ${APPIMAGE_APPDIR}/${PROJECT_BINARY_NAME}.svg)

configure_file(${CMAKE_SOURCE_DIR}/misc/packagers/appimage.AppRun.in ${CMAKE_BINARY_DIR}/AppRun)

# the AppImage runtime executes the AppRun, which the configure_file leaves
# without the execution permission
file(
  COPY ${CMAKE_BINARY_DIR}/AppRun
  DESTINATION ${APPIMAGE_APPDIR}
  FILE_PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
)

message(STATUS "appimagetool: ${APPIMAGETOOL_EXEC}")
message(STATUS "AppImage icon src: ${APPIMAGE_ICON_SRC}")

add_custom_target(
  appimage
  COMMAND
    ${CMAKE_COMMAND} -E env DESTDIR=${APPIMAGE_APPDIR}
      ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install
  COMMAND
    ${CMAKE_COMMAND} -E env ARCH=${APPIMAGE_TARGET_ARCH}
      ${APPIMAGETOOL_EXEC} ${APPIMAGE_APPDIR} ${APPIMAGE_DST_NAME}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Executing the appimagetool command to generate the ${APPIMAGE_DST_NAME} AppImage package."
)
