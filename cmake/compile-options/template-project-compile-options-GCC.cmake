cmake_minimum_required(VERSION 3.13)

set(EXTRA_COMPILE_OPTIONS
  ${EXTRA_COMPILE_OPTIONS}
  -Wall
  -Wextra
  -Wpedantic
  -Wshadow
  -Wnon-virtual-dtor
  -Wold-style-cast
  -Wcast-align
  -Wunused
  -Woverloaded-virtual
  -Wconversion
  -Wsign-conversion
  -Wnull-dereference
  -Wdouble-promotion
  -Wformat=2
  -Wimplicit-fallthrough
  -Wmisleading-indentation
  -Wzero-as-null-pointer-constant
)

# The clang (the emcc of the WebAssembly builds among them) knows none of these.
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(EXTRA_COMPILE_OPTIONS
    ${EXTRA_COMPILE_OPTIONS}
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wuseless-cast
  )
endif()

if (COMPILE_WARNINGS_AS_ERRORS)
  set(EXTRA_COMPILE_OPTIONS ${EXTRA_COMPILE_OPTIONS} -Werror)
endif()

if (ENABLE_COMPILER_CODE_ANALYZER)
  set(EXTRA_COMPILE_OPTIONS ${EXTRA_COMPILE_OPTIONS} -fanalyzer)
endif()
