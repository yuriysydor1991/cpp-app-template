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
    configuration_inc
  ]
)

test(
  'gtest',
  CTEST_app,
  suite: 'CTEST_app'
)
