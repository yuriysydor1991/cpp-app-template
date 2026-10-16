CTEST_DefaultLogger_sources = files(
  'CTEST_DefaultLogger.cpp',
  join_paths(project_include_root, 'src', 'log', 'default-logger', 'DefaultLogger.cpp'),
  join_paths(project_include_root, 'src', 'log', 'default-logger', 'real-default-logger', 'RealDefaultLogger.cpp'),
)

CTEST_DefaultLogger = executable(
  'CTEST_DefaultLogger',
  CTEST_DefaultLogger_sources,
  dependencies: gtest_deps,
  include_directories: [configuration_inc],
  cpp_args: [
    '-DCTEST_DefaultLogger_DATA_DIR="' + meson.current_build_dir() + '"',
  ],
)

test(
  'gtest',
  CTEST_DefaultLogger,
  suite: 'CTEST_DefaultLogger',
)
