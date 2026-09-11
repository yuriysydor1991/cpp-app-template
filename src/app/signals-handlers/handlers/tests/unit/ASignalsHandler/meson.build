UTEST_ASignalsHandler_files = files(
  'UTEST_ASignalsHandler.cpp',
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'handlers', 'ASignalsHandler.cpp'),
  join_paths(app_mocks_root_str, 'ApplicationContext', 'src', 'app', 'ApplicationContext.cpp')
)

UTEST_ASignalsHandler = executable(
  'UTEST_ASignalsHandler',
  UTEST_ASignalsHandler_files,
  dependencies: gtest_deps,
  include_directories: [
    MOCK_ApplicationContext,
    MOCK_log,
    configuration_inc
  ],
  cpp_args: ['-DNDEBUG=1']
)

test(
  'gtest',
  UTEST_ASignalsHandler,
  suite: 'UTEST_ASignalsHandler'
)
