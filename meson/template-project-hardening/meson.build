cpp = meson.get_compiler('cpp')

if cpp.get_argument_syntax() == 'msvc'
  template_project_hardening_cpp_args = [
    '/GS',
    '/guard:cf',
    '/Qspectre',
  ]

  template_project_hardening_link_args = [
    '/GUARD:CF',
    '/DYNAMICBASE',
    '/NXCOMPAT',
    '/HIGHENTROPYVA',
    '/CETCOMPAT',
  ]
else
  template_project_hardening_cpp_args = [
    '-fstack-protector-all',
    '-fno-common',
    '-fno-strict-overflow',
    '-fno-delete-null-pointer-checks',
    '-fstrict-flex-arrays=3',
    '-fzero-call-used-regs=used-gpr',
    '-mbranch-protection=standard',
    '-fcf-protection=full',
    '-fstack-clash-protection',
    '-D_GLIBCXX_ASSERTIONS',
  ]

  template_project_hardening_link_args = [
    '-Wl,-z,relro',
    '-Wl,-z,now',
    '-Wl,-z,noexecstack',
    '-Wl,-z,separate-code',
  ]

  # The _FORTIFY_SOURCE is ignored by the C library without an optimization and
  # the automatic variables initialization hides the uninitialized reads from
  # the valgrind and the sanitizers the debug build runs, so both of them stay
  # with the optimized builds only. The level 3 needs the dynamic object size
  # builtins of the GCC 12 / clang 9, so an older compiler gets the level 2 one.
  if get_option('optimization') in ['1', '2', '3', 's']
    fortify_source_level = cpp.compiles(
      '#include <cstring>\nint main() { char buffer[4] = {}; return int(std::strlen(buffer)); }',
      args: ['-O2', '-Werror', '-U_FORTIFY_SOURCE', '-D_FORTIFY_SOURCE=3'],
      name: 'the _FORTIFY_SOURCE level 3'
    ) ? '3' : '2'

    template_project_hardening_cpp_args += [
      '-U_FORTIFY_SOURCE',
      '-D_FORTIFY_SOURCE=' + fortify_source_level,
      '-ftrivial-auto-var-init=zero',
    ]
  endif
endif

# The hardening options are the compiler, the linker and the target CPU
# specific ones, so the unsupported ones are dropped instead of breaking the
# build. The position independent executable comes from the b_pie option of
# the project() call, which gives the -fPIE and the -pie to the executables
# and keeps the -fPIC of the libraries.
add_project_arguments(
  cpp.get_supported_arguments(template_project_hardening_cpp_args),
  language: 'cpp'
)

add_project_link_arguments(
  cpp.get_supported_link_arguments(template_project_hardening_link_args),
  language: 'cpp'
)
