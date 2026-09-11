subdir('applications')
subdir('signals-handlers')

applib = static_library(
  'applib',
  [
    'CommandLineParser.cpp',
    'ApplicationFactory.cpp',
    'ApplicationContext.cpp',
    applications_sources,
    signals_handlers_sources
  ],
  include_directories: configuration_inc,
  dependencies: template_project_extra_deps,
  cpp_args: template_project_extra_cpp_args
)

if get_option('ENABLE_UNIT_TESTS') or get_option('ENABLE_COMPONENT_TESTS')
  subdir('tests')
  subdir('applications/tests')
  subdir('signals-handlers/tests')
  subdir('signals-handlers/handlers/tests')
  subdir('signals-handlers/handlers/posix/tests')
endif
