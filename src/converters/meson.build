converters_lib = static_library(
  'converters',
  ['ApplicationContext2LibraryContext.cpp'],
  include_directories: [configuration_inc, lib_public_includes],
  dependencies: template_project_extra_deps,
  cpp_args: template_project_extra_cpp_args,
)

if get_option('ENABLE_UNIT_TESTS')
  subdir('tests')
endif
