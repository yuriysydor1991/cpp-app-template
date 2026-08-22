applications_sources = files(
  'Application.cpp',
  'ApplicationHelpPrinter.cpp',
  'ApplicationVersionPrinter.cpp'
)

if get_option('ENABLE_UNIT_TESTS') or get_option('ENABLE_COMPONENT_TESTS')
  # Declared before the src/app tests are entered because the parent
  # component's ApplicationFactory unit test consumes these mocks.
  subdir('tests/mocks')
endif
