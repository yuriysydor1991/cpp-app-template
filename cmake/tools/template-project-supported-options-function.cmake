cmake_minimum_required(VERSION 3.13)

include(CheckCXXSourceCompiles)

# The hardening options are the compiler, the linker and the target CPU
# specific ones, so every of them is probed before the use and the unsupported
# ones are dropped instead of breaking the build.

# The standard header inclusion lets the C library report its own complains
# (the _FORTIFY_SOURCE level support among them) during the probe.
set(
  TEMPLATE_PROJECT_OPTIONS_PROBE_SOURCE
  "#include <cstring>\nint main() { char buffer[4] = {}; return static_cast<int>(std::strlen(buffer)); }"
)

# The compilers report an unsupported option as a warning quite often, so the
# probe turns any warning into an error to get such an option rejected.
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(TEMPLATE_PROJECT_OPTIONS_PROBE_STRICT /WX)
else()
  set(TEMPLATE_PROJECT_OPTIONS_PROBE_STRICT -Werror)
endif()

# Sets the RESULT_VAR to TRUE when the toolchain accepts all the given options.
# The probe both compiles and links, so the linker ones are checkable too. The
# options are probed together, which the dependent ones (the -D_FORTIFY_SOURCE
# with the optimization level it requires) rely on.
function(template_project_check_supported_options RESULT_VAR)
  string(REPLACE ";" " " PROBE_OPTIONS "${ARGN}")
  string(MAKE_C_IDENTIFIER "TEMPLATE_PROJECT_ACCEPTS_${PROBE_OPTIONS}" PROBE_VAR)

  set(CMAKE_REQUIRED_FLAGS "${TEMPLATE_PROJECT_OPTIONS_PROBE_STRICT} ${PROBE_OPTIONS}")

  check_cxx_source_compiles(
    "${TEMPLATE_PROJECT_OPTIONS_PROBE_SOURCE}"
    ${PROBE_VAR}
    FAIL_REGEX "D9002" "LNK4044"
  )

  set(${RESULT_VAR} ${${PROBE_VAR}} PARENT_SCOPE)
endfunction()

# Appends the option to the LIST_VAR list when the toolchain accepts it.
function(template_project_append_supported_option LIST_VAR OPTION)
  template_project_check_supported_options(IS_SUPPORTED ${OPTION})

  if (IS_SUPPORTED)
    set(${LIST_VAR} ${${LIST_VAR}} ${OPTION} PARENT_SCOPE)
  endif()
endfunction()
