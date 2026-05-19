loglib = static_library(
  'TemplateProjectSimpleLoggerObj',
  ['SimpleLogger.cpp'],
  include_directories: configuration_inc,
  pic: true,
)

if get_option('ENABLE_COMPONENT_TESTS')
  subdir('tests')
endif
