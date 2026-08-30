cmake_minimum_required(VERSION 3.13)

set(FLATPAK_PROJECT_URL ua.org.kytok.template.claude.${PROJECT_BINARY_NAME})

option(
  ENABLE_FLATPAK_METAINFO
  "Set to ON to install the AppStream metainfo file: the flatpak-builder build does it"
  OFF
)

if(ENABLE_FLATPAK_METAINFO)
  set(flatpakMetainfoDst ${CMAKE_BINARY_DIR}/${FLATPAK_PROJECT_URL}.metainfo.xml)

  configure_file(${CMAKE_SOURCE_DIR}/misc/packagers/flatpak.metainfo.xml.in ${flatpakMetainfoDst})

  install(FILES ${flatpakMetainfoDst} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/metainfo)
endif()

option(
  ENABLE_FLATPAK
  "Set to ON to enable the flatpak package creation from the project build artifacts"
  OFF
)

if(NOT ENABLE_FLATPAK)
  return()
endif()

find_program(FLATPAKB_EXEC flatpak-builder REQUIRED)
find_program(FLATPAK_EXEC flatpak REQUIRED)

set(FLATPAK_REPO ${PROJECT_BINARY_NAME}-repo)
set(FLATPAK_DST_NAME ${PROJECT_BINARY_NAME}-${CMAKE_PROJECT_VERSION}.flatpak)
set(flatpakConfDst ${CMAKE_BINARY_DIR}/flatpak.conf.json)
set(FLATPAK_DEPS_REMOTE flathub)
set(FLATPAK_DEPS_REMOTE_URL https://dl.flathub.org/repo/flathub.flatpakrepo)
set(
  FLATPAK_CONF_SRC 
  ${CMAKE_SOURCE_DIR}/misc/packagers/flatpak.conf.json.in 
  CACHE STRING "The flatpak json conf source file cmake configured"
)

configure_file(${FLATPAK_CONF_SRC} ${flatpakConfDst})

message(STATUS "flatpak-builder: ${FLATPAKB_EXEC}")
message(STATUS "flatpak: ${FLATPAK_EXEC}")
message(STATUS "flatpak json conf src: ${FLATPAK_CONF_SRC}")

add_custom_target(
  flatpak
  COMMAND 
    ${FLATPAK_EXEC} remote-add --user --if-not-exists ${FLATPAK_DEPS_REMOTE} ${FLATPAK_DEPS_REMOTE_URL} &&
    ${FLATPAKB_EXEC} --user --install-deps-from=${FLATPAK_DEPS_REMOTE} --assumeyes
      --repo=${FLATPAK_REPO} "${CMAKE_BINARY_DIR}/flatpak-build" ${flatpakConfDst} &&
    ${FLATPAK_EXEC} build-bundle ${FLATPAK_REPO} ${FLATPAK_DST_NAME} ${FLATPAK_PROJECT_URL}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Executing the flatpak-builder command to generate the ${FLATPAK_DST_NAME} flatpak package."
)
