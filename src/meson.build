configuration_inc = [
  configuration_inc,
  include_directories('.')
]

subdir('app')
subdir('log')

template_project_main_binary = executable(
  meson.project_name(),
  ['main.cpp'],
  include_directories: configuration_inc,
  link_whole: [applib, loglib],
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
