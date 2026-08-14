cmake_minimum_required(VERSION 3.13)

# -D_FORTIFY_SOURCE=2 (needs OPT); 

set(EXTRA_COMPILE_OPTIONS 
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
  -Wduplicated-cond
  -Wduplicated-branches
  -Wlogical-op
  -Wuseless-cast
  -Wmisleading-indentation
  -Wzero-as-null-pointer-constant
  -fstack-protector-all
  -fno-common
  -fstrict-overflow
)

# The hardening options below are given to the linker and not to the compiler,
# which silently drops them from a compile only invocation, so they are
# collected into the EXTRA_LINK_OPTIONS which the src/CMakeLists.txt hands over
# to the add_link_options command.
#
# The -pie one is applied to the executables only, because the linker rejects
# it together with the -shared of a shared library. Its -fPIE compile time
# counterpart comes from the CMAKE_POSITION_INDEPENDENT_CODE, see the
# template-project-compile-options module.
set(EXTRA_LINK_OPTIONS
  ${EXTRA_LINK_OPTIONS}
  -Wl,-z,relro
  -Wl,-z,now
  $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:-pie>
)

if (COMPILE_WARNINGS_AS_ERRORS)
  set(EXTRA_COMPILE_OPTIONS ${EXTRA_COMPILE_OPTIONS} -Werror)
endif()

if (ENABLE_COMPILER_CODE_ANALYZER)
  set(EXTRA_COMPILE_OPTIONS ${EXTRA_COMPILE_OPTIONS} -fanalyzer)
endif()
