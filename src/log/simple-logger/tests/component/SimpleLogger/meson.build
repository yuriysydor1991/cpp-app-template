CTEST_SimpleLogger_sources = files(
  'CTEST_SimpleLogger.cpp',
  join_paths(project_include_root, 'src', 'log', 'simple-logger', 'SimpleLogger.cpp'),
)

CTEST_SimpleLogger = executable(
  'CTEST_SimpleLogger',
  CTEST_SimpleLogger_sources,
  dependencies: gtest_deps,
  include_directories: [configuration_inc],
  cpp_args: [
    '-DCTEST_SimpleLogger_DATA_DIR="' + meson.current_build_dir() + '"',
  ],
)

test(
  'gtest',
  CTEST_SimpleLogger,
  suite: 'CTEST_SimpleLogger',
)
