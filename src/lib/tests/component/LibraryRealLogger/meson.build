# The library is expected to log into the real logger instance handed over by
# its user, so the whole library implementation is compiled together with the
# real log.h facilities instead of a log mock and is driven through the public
# LibraryFacade only. The asserts are disabled to let the library error paths
# be reachable.
CTEST_LibraryRealLogger_sources = files(
  'CTEST_LibraryRealLogger.cpp',
  join_paths(project_include_root, 'src', 'lib', 'facade', 'LibraryFacade.cpp'),
  join_paths(project_include_root, 'src', 'lib', 'libmain', 'LibFactory.cpp'),
  join_paths(project_include_root, 'src', 'lib', 'libmain', 'LibMain.cpp'),
  join_paths(project_include_root, 'src', 'log', 'default-logger', 'DefaultLogger.cpp'),
  join_paths(project_include_root, 'src', 'log', 'default-logger', 'real-default-logger', 'RealDefaultLogger.cpp'),
)

CTEST_LibraryRealLogger = executable(
  'CTEST_LibraryRealLogger',
  CTEST_LibraryRealLogger_sources,
  dependencies: gtest_deps,
  include_directories: [configuration_inc, lib_public_includes],
  cpp_args: [
    '-DNDEBUG=1',
    '-DCTEST_LibraryRealLogger_DATA_DIR="' + meson.current_build_dir() + '"',
  ],
)

test(
  'gtest',
  CTEST_LibraryRealLogger,
  suite: 'CTEST_LibraryRealLogger',
)
