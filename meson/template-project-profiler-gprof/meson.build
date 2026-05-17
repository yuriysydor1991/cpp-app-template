if get_option('buildtype') != 'debug'
  error('Profiling with gprof is only supported on the Debug builds. Configure with --buildtype=debug.')
endif

find_program('gprof', required: true)

template_project_extra_cpp_args += ['-pg', '-fprofile-generate']
template_project_extra_link_args += ['-pg', '-fprofile-generate']

message('gprof profiling instrumentation enabled')
