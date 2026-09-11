UTEST_SignalsHandler_files = files(
  'UTEST_SignalsHandler.cpp',
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'SignalsHandler.cpp'),
  join_paths(app_mocks_root_str, 'ApplicationContext', 'src', 'app', 'ApplicationContext.cpp')
)

UTEST_SignalsHandler = executable(
  'UTEST_SignalsHandler',
  UTEST_SignalsHandler_files,
  dependencies: gtest_deps,
  include_directories: [
    MOCK_ApplicationContext,
    MOCK_ContinueSignalsHandler,
    MOCK_IgnoredSignalsHandler,
    MOCK_PauseSignalsHandler,
    MOCK_ReloadSignalsHandler,
    MOCK_StopSignalsHandler,
    MOCK_UserSignalsHandler,
    MOCK_log,
    configuration_inc
  ],
  cpp_args: ['-DNDEBUG=1']
)

test(
  'gtest',
  UTEST_SignalsHandler,
  suite: 'UTEST_SignalsHandler'
)
