UTEST_Application_files = files(
  'UTEST_Application.cpp',
  join_paths(project_include_root, 'src', 'app', 'Application.cpp'),
  join_paths(app_mocks_root_str, 'ApplicationContext', 'src', 'app', 'ApplicationContext.cpp')
)

UTEST_Application = executable(
  'UTEST_Application', 
  UTEST_Application_files, 
  dependencies: gtest_deps,
  include_directories: [
    MOCK_ApplicationContext,
    configuration_inc
  ],
  cpp_args: ['-DNDEBUG=1']
)

test(
  'gtest', 
  UTEST_Application,
  suite: 'UTEST_Application'
)
