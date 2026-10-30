cmake_minimum_required(VERSION 3.13)

# The Emscripten toolchain configure (the emcmake cmake ... one) compiles the
# project into the WebAssembly, so the binary is turned into a browser page.
if (NOT EMSCRIPTEN OR NOT TARGET "${PROJECT_BINARY_NAME}")
  return()
endif()

# The SINGLE_FILE embeds the .wasm module into the .js loader, so the page runs
# when opened from the disk as well, while the EXIT_RUNTIME exits the binary
# the way a native one exits: with the return code and the static destructors.
target_link_options(
  ${PROJECT_BINARY_NAME}
  PRIVATE -sSINGLE_FILE=1 -sEXIT_RUNTIME=1 -sALLOW_MEMORY_GROWTH=1
)

get_target_property(WEBASSEMBLY_PAGE_DIR ${PROJECT_BINARY_NAME} BINARY_DIR)

set(WEBASSEMBLY_PAGE "${WEBASSEMBLY_PAGE_DIR}/${PROJECT_BINARY_NAME}.html")

configure_file(
  ${CMAKE_SOURCE_DIR}/misc/webassembly/webassembly.html.in
  ${WEBASSEMBLY_PAGE}
  @ONLY
)

install(
  FILES ${WEBASSEMBLY_PAGE}
  DESTINATION ${PROJECT_BINARY_INSTALLATION_DIR}
)

message(STATUS "WebAssembly page: ${WEBASSEMBLY_PAGE}")
