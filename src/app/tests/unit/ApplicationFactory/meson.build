UTEST_ApplicationFactory_files = files(
  'UTEST_ApplicationFactory.cpp',
  join_paths(project_include_root, 'src', 'app', 'ApplicationFactory.cpp'),
  join_paths(app_mocks_root_str, 'ApplicationContext', 'src', 'app', 'ApplicationContext.cpp')
)

UTEST_ApplicationFactory = executable(
  'UTEST_ApplicationFactory', 
  UTEST_ApplicationFactory_files, 
  dependencies: gtest_deps,
  include_directories: [
    MOCK_ApplicationContext,
    MOCK_Application,
    MOCK_ApplicationHelpPrinter,
    MOCK_ApplicationVersionPrinter,
    MOCK_CommandLineParser,
    MOCK_project_global_decls,
    configuration_inc
  ],
  cpp_args: ['-DNDEBUG=1']
)

test('gtest', UTEST_ApplicationFactory)
