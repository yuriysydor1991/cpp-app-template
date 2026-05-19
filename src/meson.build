configuration_inc = [
  configuration_inc,
  include_directories('.')
]

if get_option('ENABLE_UNIT_TESTS') or get_option('ENABLE_COMPONENT_TESTS')
  gtest_dep = dependency('gtest', required: true)
  gmock_dep = dependency('gmock', required: true)
  gtest_main_dep = dependency('gtest_main', required: true)

  gtest_deps = [gtest_dep, gmock_dep, gtest_main_dep]
endif

if get_option('ENABLE_UNIT_TESTS')
  subdir('tests/mocks')
endif

subdir('log')
subdir('lib')
subdir('app')
subdir('converters')

template_project_main_binary = executable(
  meson.project_name(),
  ['main.cpp'],
  include_directories: [configuration_inc, lib_public_includes],
  link_whole: [applib, converters_lib],
  link_with: [template_project_main_library],
  dependencies: template_project_extra_deps,
  cpp_args: template_project_extra_cpp_args,
  link_args: template_project_extra_link_args,
  install: true,
  install_dir: 'bin'
)

if get_option('ENABLE_VALGRIND')
  valgrind_exec = find_program('valgrind', required: true)
  custom_target(
    'valgrind',
    command: [
      valgrind_exec,
      '--leak-check=full',
      '--error-exitcode=1',
      '--show-leak-kinds=all',
      template_project_main_binary
    ],
    depends: [template_project_main_binary],
    output: 'valgrind-output-stub.txt',
    build_always_stale: true,
    console: true
  )
endif

if get_option('ENABLE_CALLGRIND')
  callgrind_exec = find_program('valgrind', required: true)
  custom_target(
    'callgrind',
    command: [
      callgrind_exec,
      '--tool=callgrind',
      template_project_main_binary
    ],
    depends: [template_project_main_binary],
    output: 'callgrind-output-stub.txt',
    build_always_stale: true,
    console: true
  )
endif

if get_option('ENABLE_GPROF')
  gprof_exec = find_program('gprof', required: true)
  custom_target(
    'gprof-analyze',
    command: [
      'sh', '-c',
      template_project_main_binary.full_path() + ' && ' +
      gprof_exec.full_path() + ' ' + template_project_main_binary.full_path() +
      ' ' + join_paths(meson.current_build_dir(), 'gmon.out') +
      ' > ' + join_paths(meson.current_build_dir(), 'gprof-analyze.txt')
    ],
    depends: [template_project_main_binary],
    output: 'gprof-analyze.txt',
    build_always_stale: true,
    console: true
  )
endif
