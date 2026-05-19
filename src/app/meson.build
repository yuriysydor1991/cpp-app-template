applib = static_library(
  'applib',
  [
    'CommandLineParser.cpp',
    'ApplicationVersionPrinter.cpp',
    'ApplicationFactory.cpp',
    'ApplicationHelpPrinter.cpp',
    'Application.cpp',
    'ApplicationContext.cpp'
  ],
  include_directories: [configuration_inc, lib_public_includes],
  dependencies: template_project_extra_deps,
  cpp_args: template_project_extra_cpp_args
)

if get_option('ENABLE_UNIT_TESTS') or get_option('ENABLE_COMPONENT_TESTS')
  subdir('tests')
endif
