subdir('real-default-logger')

loglib = static_library(
  'TemplateProjectDefaultLoggerObj',
  ['DefaultLogger.cpp'] + real_default_logger_sources,
  include_directories: configuration_inc,
  dependencies: template_project_extra_deps,
  cpp_args: template_project_extra_cpp_args,
)

if get_option('ENABLE_COMPONENT_TESTS')
  subdir('tests/component/DefaultLogger')
endif
