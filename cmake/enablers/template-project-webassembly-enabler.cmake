cmake_minimum_required(VERSION 3.13)

# The Emscripten toolchain configure (the emcmake cmake ... one) compiles the
# project into the WebAssembly, so the binary is turned into a browser page.
if (NOT EMSCRIPTEN OR NOT TARGET "${PROJECT_BINARY_NAME}")
  return()
endif()

# The .html suffix makes the emcc generate the page next to the .js loader and
# the .wasm module. The --emrun passes the page URL query to the main function
# as the command line arguments and exits the runtime the way a native binary
# exits: with the return code and the static destructors. The page minifier is
# off, since the Debian and the Ubuntu emscripten packages lack it.
set_target_properties(${PROJECT_BINARY_NAME} PROPERTIES SUFFIX ".html")

target_link_options(
  ${PROJECT_BINARY_NAME}
  PRIVATE --emrun -sALLOW_MEMORY_GROWTH=1 -sMINIFY_HTML=0
)

install(
  FILES
    $<TARGET_FILE_DIR:${PROJECT_BINARY_NAME}>/${PROJECT_BINARY_NAME}.js
    $<TARGET_FILE_DIR:${PROJECT_BINARY_NAME}>/${PROJECT_BINARY_NAME}.wasm
  DESTINATION ${PROJECT_BINARY_INSTALLATION_DIR}
)

message(STATUS "WebAssembly page: ${PROJECT_BINARY_NAME}.html")
