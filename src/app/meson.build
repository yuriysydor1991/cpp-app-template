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
  include_directories: configuration_inc
)

if get_option('ENABLE_UNIT_TESTS')
  subdir('tests')
endif
