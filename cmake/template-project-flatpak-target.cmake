cmake_minimum_required(VERSION 3.13)

find_program(FLATPAKB_EXEC flatpak-builder REQUIRED)
find_program(FLATPAK_EXEC flatpak REQUIRED)

set(FLATPAK_PROJECT_URL ua.org.kytok.template.mysqlcppconn.${PROJECT_BINARY_NAME})
set(FLATPAK_REPO ${PROJECT_BINARY_NAME}-repo)
set(FLATPAK_DST_NAME ${PROJECT_BINARY_NAME}-${CMAKE_PROJECT_VERSION}.flatpak)
set(flatpakConfDst ${CMAKE_BINARY_DIR}/flatpak.conf.json)

configure_file(
  ${CMAKE_SOURCE_DIR}/misc/flatpak.conf.json.in
  ${flatpakConfDst}
)

message(STATUS "flatpak-builder: ${FLATPAKB_EXEC}")
message(STATUS "flatpak: ${FLATPAK_EXEC}")

add_custom_target(
  flatpak
  COMMAND 
    ${FLATPAKB_EXEC} --repo=${FLATPAK_REPO} "${CMAKE_BINARY_DIR}/flatpak-build" ${flatpakConfDst} &&
    ${FLATPAK_EXEC} build-bundle ${FLATPAK_REPO} ${FLATPAK_DST_NAME} ${FLATPAK_PROJECT_URL}
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "Executing the flatpak-builder command to generate the ${FLATPAK_DST_NAME} flatpak package."
)
