subdir('real-default-logger')

loglib = static_library(
  'TemplateProjectDefaultLoggerObj',
  ['DefaultLogger.cpp'] + real_default_logger_sources,
  include_directories: configuration_inc,
  pic: true,
)

if get_option('ENABLE_COMPONENT_TESTS')
  subdir('tests')
endif
