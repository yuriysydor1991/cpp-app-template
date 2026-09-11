signals_handlers_posix_sources = files(
  'ContinueSignalsHandler.cpp',
  'IgnoredSignalsHandler.cpp',
  'PauseSignalsHandler.cpp',
  'PosixSignalsHandler.cpp',
  'ReloadSignalsHandler.cpp',
  'StopSignalsHandler.cpp',
  'UserSignalsHandler.cpp'
)

if get_option('ENABLE_UNIT_TESTS') or get_option('ENABLE_COMPONENT_TESTS')
  # Declared before the tests are entered because the SignalsHandler unit
  # test consumes these mocks.
  subdir('tests/mocks')
endif
