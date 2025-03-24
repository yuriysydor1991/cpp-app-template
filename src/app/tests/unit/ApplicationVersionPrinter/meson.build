UTEST_ApplicationVersionPrinter_files = files(
  'UTEST_ApplicationVersionPrinter.cpp',
  join_paths(project_include_root, 'src', 'app', 'ApplicationVersionPrinter.cpp'),
  join_paths(app_mocks_root_str, 'ApplicationContext', 'src', 'app', 'ApplicationContext.cpp')
)

UTEST_ApplicationVersionPrinter = executable(
  'UTEST_ApplicationVersionPrinter', 
  UTEST_ApplicationVersionPrinter_files, 
  dependencies: gtest_deps,
  include_directories: [
    MOCK_ApplicationContext,
    configuration_inc
  ],
  cpp_args: ['-DNDEBUG=1']
)

test('gtest', UTEST_ApplicationVersionPrinter)
