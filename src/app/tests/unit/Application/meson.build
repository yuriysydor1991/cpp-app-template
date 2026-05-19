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
    APP_MOCK_ApplicationContext2LibraryContext,
    APP_MOCK_LibraryFacade,
    APP_MOCK_LibMain,
    MOCK_LibraryContext,
    MOCK_log,
    configuration_inc,
    lib_public_includes,
  ],
  cpp_args: ['-DNDEBUG=1']
)

test(
  'gtest',
  UTEST_Application,
  suite: 'UTEST_Application'
)
