UTEST_ApplicationHelpPrinter_files = files(
  'UTEST_ApplicationHelpPrinter.cpp',
  join_paths(project_include_root, 'src', 'app', 'ApplicationHelpPrinter.cpp'),
  join_paths(app_mocks_root_str, 'ApplicationContext', 'src', 'app', 'ApplicationContext.cpp')
)

UTEST_ApplicationHelpPrinter = executable(
  'UTEST_ApplicationHelpPrinter', 
  UTEST_ApplicationHelpPrinter_files, 
  dependencies: gtest_deps,
  include_directories: [
    MOCK_ApplicationContext,
    configuration_inc
  ],
  cpp_args: ['-DNDEBUG=1']
)

test('gtest', UTEST_ApplicationHelpPrinter)
