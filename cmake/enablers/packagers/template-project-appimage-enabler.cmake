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
  TEMPLATE_PROJECT_APPIMAGE_ARCHITECTURE
  ${CMAKE_SYSTEM_PROCESSOR}
  CACHE STRING
  "The destination CPU architecture of the AppImage package (e.g. x86_64, aarch64, armhf, i686)"
)

set(APPIMAGE_APPDIR ${CMAKE_BINARY_DIR}/AppDir)
set(APPIMAGE_DST_NAME ${PROJECT_BINARY_NAME}-${CMAKE_PROJECT_VERSION}-${TEMPLATE_PROJECT_APPIMAGE_ARCHITECTURE}.AppImage)

# the AppImage format demands the desktop entry and the icon it names on the
# AppDir root, next to the ones the install step places
file(COPY ${DESKTOP_ENTRY_FILE} ${DESKTOP_ICON_FILE} DESTINATION ${APPIMAGE_APPDIR})

configure_file(${CMAKE_SOURCE_DIR}/misc/packagers/appimage/appimage.AppRun.in ${CMAKE_BINARY_DIR}/AppRun)

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

add_custom_target(
  appimage
  COMMAND
    ${CMAKE_COMMAND} -E env DESTDIR=${APPIMAGE_APPDIR}
      ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install
  COMMAND
    ${CMAKE_COMMAND} -E env ARCH=${TEMPLATE_PROJECT_APPIMAGE_ARCHITECTURE}
      ${APPIMAGETOOL_EXEC} ${APPIMAGE_APPDIR} ${APPIMAGE_DST_NAME}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Executing the appimagetool command to generate the ${APPIMAGE_DST_NAME} AppImage package."
)
