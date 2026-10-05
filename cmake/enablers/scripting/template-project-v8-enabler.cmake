cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_V8
    "Enables the V8 JavaScript engine for the project usage through the system installed one (the libnode-dev package) or an own V8 build"
    ON
)

if (NOT ENABLE_V8)
    return()
endif()

# The V8 builds with the Google gn/ninja toolchain of its own only, which takes
# hours and tens of gigabytes, so no FetchContent fallback is offered. The
# Debian based distributions ship the V8 inside the Node.js shared library: the
# libnode-dev package puts the V8 headers into the include/node directory and
# names the libnode.so one as the libv8.so and the libv8_libplatform.so too.
# Preset the V8_INCLUDE_DIR and the V8_LIBRARY cache variables to point at an
# own V8 build (e.g. the v8_monolith one) instead.
find_path(V8_INCLUDE_DIR v8.h PATH_SUFFIXES node v8)
find_library(V8_LIBRARY NAMES v8 v8_monolith node)
find_library(V8_LIBPLATFORM_LIBRARY NAMES v8_libplatform)

if (NOT V8_INCLUDE_DIR OR NOT V8_LIBRARY)
    message(FATAL_ERROR "No V8 JavaScript engine found: install the libnode-dev package or set the V8_INCLUDE_DIR and the V8_LIBRARY variables")
endif()

# The V8 headers must see the very same pointer compression and sandbox
# definitions the V8 binary was built with. The libnode builds need none, while
# an own build with the default gn args needs V8_COMPRESS_POINTERS and
# V8_ENABLE_SANDBOX ones.
set(TEMPLATE_APP_V8_COMPILE_DEFINITIONS "" CACHE STRING "The compile definitions matching the build of the linked V8")

find_package(Threads REQUIRED)

# The imported target headers are the system ones, so the V8 headers raise no
# warnings of the strict project compile options.
add_library(V8::V8 INTERFACE IMPORTED)

target_include_directories(V8::V8 INTERFACE ${V8_INCLUDE_DIR})
target_compile_definitions(V8::V8 INTERFACE ${TEMPLATE_APP_V8_COMPILE_DEFINITIONS})
target_link_libraries(V8::V8 INTERFACE ${V8_LIBRARY} Threads::Threads ${CMAKE_DL_LIBS})

# The V8 headers since the 13.x (e.g. the libnode-dev of the Node.js 24) demand
# the C++20, so the targets linking the V8::V8 are raised above the project
# C++ standard while the rest of the project keeps it.
target_compile_features(V8::V8 INTERFACE cxx_std_20)

# The V8 is built without the RTTI, so the vptr sanitizer of the sanitizers
# build finds no type information of the V8 classes to check against.
target_compile_options(V8::V8 INTERFACE $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-fno-sanitize=vptr>)

# A monolithic V8 build carries the platform library inside.
if (V8_LIBPLATFORM_LIBRARY)
    target_link_libraries(V8::V8 INTERFACE ${V8_LIBPLATFORM_LIBRARY})
endif()

message(STATUS "The V8 headers: ${V8_INCLUDE_DIR}")
message(STATUS "The V8 library: ${V8_LIBRARY}")

# Link the V8::V8 target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} V8::V8)
