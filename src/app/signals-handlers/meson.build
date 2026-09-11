subdir('handlers')

signals_handlers_sources = files(
  'SignalsHandler.cpp'
) + signals_handlers_handlers_sources

if get_option('ENABLE_UNIT_TESTS') or get_option('ENABLE_COMPONENT_TESTS')
  # Declared before the src/app tests are entered because the parent
  # component's ApplicationFactory unit test consumes this mock.
  subdir('tests/mocks')
endif
