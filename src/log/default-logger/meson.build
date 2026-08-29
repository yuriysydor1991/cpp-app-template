subdir('real-default-logger')

# The objects end up inside the project shared library, so they must be
# relocatable and they must follow its hidden visibility: the logger is an
# implementation detail and its symbols would otherwise clash with the
# identically named ones of any other library derived from this template.
loglib = static_library(
  'TemplateProjectDefaultLoggerObj',
  ['DefaultLogger.cpp'] + real_default_logger_sources,
  include_directories: configuration_inc,
  pic: true,
  gnu_symbol_visibility: 'hidden',
)

if get_option('ENABLE_COMPONENT_TESTS')
  subdir('tests')
endif
