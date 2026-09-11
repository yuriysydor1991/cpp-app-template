UTEST_UserSignalsHandler_files = files(
  'UTEST_UserSignalsHandler.cpp',
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'handlers', 'posix', 'UserSignalsHandler.cpp'),
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'handlers', 'posix', 'PosixSignalsHandler.cpp'),
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'handlers', 'ASignalsHandler.cpp'),
  join_paths(app_mocks_root_str, 'ApplicationContext', 'src', 'app', 'ApplicationContext.cpp')
)

UTEST_UserSignalsHandler = executable(
  'UTEST_UserSignalsHandler',
  UTEST_UserSignalsHandler_files,
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
  UTEST_UserSignalsHandler,
  suite: 'UTEST_UserSignalsHandler'
)
