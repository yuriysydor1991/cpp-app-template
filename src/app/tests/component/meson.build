CTEST_app_files = files(
  'CTEST_app.cpp',
  join_paths(project_include_root, 'src', 'app', 'Application.cpp'),
  join_paths(project_include_root, 'src', 'app', 'ApplicationContext.cpp'),
  join_paths(project_include_root, 'src', 'app', 'ApplicationFactory.cpp'),
  join_paths(project_include_root, 'src', 'app', 'ApplicationHelpPrinter.cpp'),
  join_paths(project_include_root, 'src', 'app', 'CommandLineParser.cpp'),
  join_paths(project_include_root, 'src', 'app', 'ApplicationVersionPrinter.cpp')
)

CTEST_app = executable(
  'CTEST_app',
  CTEST_app_files,
  dependencies: gtest_deps,
  include_directories: [
    MOCK_log,
    APP_MOCK_LibraryFacade,
    APP_MOCK_LibMain,
    APP_MOCK_ApplicationContext2LibraryContext,
    configuration_inc,
    lib_public_includes,
  ],
  cpp_args: ['-DNDEBUG=1']
)

test(
  'gtest',
  CTEST_app,
  suite: 'CTEST_app'
)
