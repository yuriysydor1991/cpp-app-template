CTEST_app_files = files(
  'CTEST_app.cpp',
  join_paths(project_include_root, 'src', 'app', 'applications', 'Application.cpp'),
  join_paths(project_include_root, 'src', 'app', 'ApplicationContext.cpp'),
  join_paths(project_include_root, 'src', 'app', 'ApplicationFactory.cpp'),
  join_paths(project_include_root, 'src', 'app', 'applications', 'ApplicationHelpPrinter.cpp'),
  join_paths(project_include_root, 'src', 'app', 'CommandLineParser.cpp'),
  join_paths(project_include_root, 'src', 'app', 'applications', 'ApplicationVersionPrinter.cpp'),
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'SignalsHandler.cpp'),
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'handlers', 'ASignalsHandler.cpp'),
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'handlers', 'posix', 'ContinueSignalsHandler.cpp'),
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'handlers', 'posix', 'IgnoredSignalsHandler.cpp'),
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'handlers', 'posix', 'PauseSignalsHandler.cpp'),
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'handlers', 'posix', 'PosixSignalsHandler.cpp'),
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'handlers', 'posix', 'ReloadSignalsHandler.cpp'),
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'handlers', 'posix', 'StopSignalsHandler.cpp'),
  join_paths(project_include_root, 'src', 'app', 'signals-handlers', 'handlers', 'posix', 'UserSignalsHandler.cpp'),
  join_paths(project_include_root, 'src', 'log', 'default-logger', 'DefaultLogger.cpp'),
  join_paths(project_include_root, 'src', 'log', 'default-logger', 'real-default-logger', 'RealDefaultLogger.cpp'),
)

CTEST_app = executable(
  'CTEST_app',
  CTEST_app_files,
  dependencies: gtest_deps,
  # The real logger, so the log file effects of the command line are covered too.
  include_directories: [
    configuration_inc
  ]
)

test(
  'gtest',
  CTEST_app,
  suite: 'CTEST_app'
)
