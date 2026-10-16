# Top-level log facade component test. It exercises the public log.h facilities
# only, so the CTEST_log.cpp source is reusable as-is on the branches that swap
# the underlying logger; only the implementation sources listed below change
# per branch (here it is the default logger).
CTEST_log_sources = files(
  'CTEST_log.cpp',
  join_paths(project_include_root, 'src', 'log', 'default-logger', 'DefaultLogger.cpp'),
  join_paths(project_include_root, 'src', 'log', 'default-logger', 'real-default-logger', 'RealDefaultLogger.cpp'),
)

CTEST_log = executable(
  'CTEST_log',
  CTEST_log_sources,
  dependencies: gtest_deps,
  include_directories: [configuration_inc],
  cpp_args: [
    '-DCTEST_log_DATA_DIR="' + meson.current_build_dir() + '"',
  ],
)

test(
  'gtest',
  CTEST_log,
  suite: 'CTEST_log',
)
