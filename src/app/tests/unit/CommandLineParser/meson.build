UTEST_CommandLineParser_files = files(
  'UTEST_CommandLineParser.cpp',
  join_paths(project_include_root, 'src', 'app', 'CommandLineParser.cpp'),
  join_paths(app_mocks_root_str, 'ApplicationContext', 'src', 'app', 'ApplicationContext.cpp')
)

UTEST_CommandLineParser = executable(
  'UTEST_CommandLineParser', 
  UTEST_CommandLineParser_files, 
  dependencies: gtest_deps,
  include_directories: [
    MOCK_ApplicationContext,
    configuration_inc
  ],
  cpp_args: ['-DNDEBUG=1']
)

test('gtest', UTEST_CommandLineParser)
