cmake_minimum_required(VERSION 3.13)

include(template-project-supported-options-function)

# The _FORTIFY_SOURCE is ignored by the C library without an optimization and
# the automatic variables initialization hides the uninitialized reads from the
# valgrind and the sanitizers the debug build runs, so both of them stay with
# the optimized configurations only.
set(
  OPTIMIZED_CONFIG
  "$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>,$<CONFIG:MinSizeRel>>"
)

set(
  HARDENING_COMPILE_OPTIONS
  -fstack-protector-all
  -fno-common
  -fno-strict-overflow
  -fno-delete-null-pointer-checks
  -fstrict-flex-arrays=3
  -fzero-call-used-regs=used-gpr
  -mbranch-protection=standard
)

# The sanitizers module lowers the control flow protection and turns the stack
# clash one off on purpose, so its build keeps its own code generation.
if (NOT (ENABLE_SANITIZERS OR ENABLE_SANITIZERS_THREADS))
  set(
    HARDENING_COMPILE_OPTIONS
    ${HARDENING_COMPILE_OPTIONS}
    -fcf-protection=full
    -fstack-clash-protection
  )
endif()

foreach(HARDENING_COMPILE_OPTION IN LISTS HARDENING_COMPILE_OPTIONS)
  template_project_append_supported_option(
    EXTRA_COMPILE_OPTIONS ${HARDENING_COMPILE_OPTION}
  )
endforeach()

# The level 3 needs the dynamic object size builtins of the GCC 12 / clang 9,
# so an older compiler gets the level 2 one. The undefinition goes first: the
# distributions which fortify by default report a redefinition otherwise.
template_project_check_supported_options(
  SUPPORTS_FORTIFY_SOURCE_3 -O2 -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3
)

if (SUPPORTS_FORTIFY_SOURCE_3)
  set(FORTIFY_SOURCE_LEVEL 3)
else()
  set(FORTIFY_SOURCE_LEVEL 2)
endif()

set(
  EXTRA_COMPILE_OPTIONS
  ${EXTRA_COMPILE_OPTIONS}
  -D_GLIBCXX_ASSERTIONS
  $<${OPTIMIZED_CONFIG}:-U_FORTIFY_SOURCE>
  $<${OPTIMIZED_CONFIG}:-D_FORTIFY_SOURCE=${FORTIFY_SOURCE_LEVEL}>
)

template_project_check_supported_options(
  SUPPORTS_AUTO_VAR_INIT -ftrivial-auto-var-init=zero
)

if (SUPPORTS_AUTO_VAR_INIT)
  set(
    EXTRA_COMPILE_OPTIONS
    ${EXTRA_COMPILE_OPTIONS}
    $<${OPTIMIZED_CONFIG}:-ftrivial-auto-var-init=zero>
  )
endif()

# The hardening options below are given to the linker and not to the compiler,
# which silently drops them from a compile only invocation, so they are
# collected into the EXTRA_LINK_OPTIONS which the src/CMakeLists.txt hands over
# to the add_link_options command.
set(
  HARDENING_LINK_OPTIONS
  -Wl,-z,relro
  -Wl,-z,now
  -Wl,-z,noexecstack
  -Wl,-z,separate-code
)

foreach(HARDENING_LINK_OPTION IN LISTS HARDENING_LINK_OPTIONS)
  template_project_append_supported_option(
    EXTRA_LINK_OPTIONS ${HARDENING_LINK_OPTION}
  )
endforeach()

# The -pie one is applied to the executables only, because the linker rejects
# it together with the -shared of a shared library. Its -fPIE compile time
# counterpart comes from the CMAKE_POSITION_INDEPENDENT_CODE, see the
# template-project-compile-options module.
template_project_check_supported_options(SUPPORTS_PIE -pie)

if (SUPPORTS_PIE)
  set(
    EXTRA_LINK_OPTIONS
    ${EXTRA_LINK_OPTIONS}
    $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:-pie>
  )
endif()
